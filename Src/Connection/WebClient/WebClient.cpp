#include <Connection/WebClient/WebClient.hpp>
#include <Connection/Uri.hpp>
#include <Connection/Cookie/Cookie.hpp>
#include <Connection/Cookie/CookieContainer.hpp>
#include <Connection/HttpResponse.hpp>

#include <boost/format.hpp>
#include <boost/bind.hpp>
#include <boost/regex.hpp>

#include <fstream>
#include <bitset>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace boost::asio::ssl;
using namespace boost::asio::ip;

WebClient::WebClient(const string& url)
:io_service_ptr_(make_shared<boost::asio::io_service>()),
io_service_(*io_service_ptr_),
ssl_context_(context::sslv3_client),
socket_(io_service_, ssl_context_),
resolver_(io_service_),
connect_timer_(io_service_),
heartbeat_timer_(io_service_),
time_out_(10),
method_("GET"),
response_body_(""),
url_(url),
path_(""),
request_stream_(),
response_(),
content_(""),
content_type_(""),
request_headers_(),
response_headers_(),
request_cookies_(),
response_cookies_(),
read_size_(0),
read_end_size_(0),
read_mode_(ReadChunkSize),
is_cancellation_pending_(false),
status_code_(0)
{
	Uri uri(url);
	
	string scheme = uri.getScheme();
	if(scheme.empty())
	{
		return;
	}

	string host = uri.getHost();
	if(host.empty())
	{
		return;
	}

	path_ = "/" + uri.getPath();
	string query = uri.getQuery();
	if(!query.empty())
	{
		path_ += "?" + query;
	}

	assert(request_headers_.size() == 0);
	assert(request_cookies_.size() == 0);
	assert(response_headers_.size() == 0);
	assert(response_cookies_.size() == 0);

	addHeader("Host", host);
	addHeader("Connection", "keep-alive");

	response_.consume(response_.size());

	tcp::resolver resolver(io_service_);
	tcp::resolver::query resolver_query(host, scheme);
	
	resolver_.async_resolve(resolver_query, 
		boost::bind(&WebClient::handleResolve, this, 
		boost::asio::placeholders::error, 
		boost::asio::placeholders::iterator));
	
	connect_timer_.async_wait(boost::bind(&WebClient::checkDeadLine, this));
}

void WebClient::setCurrentMailAddress(const string& mail_address)
{
	current_mail_address_ = mail_address;
}

void WebClient::setCurrentAccountID(const string& account_id)
{
	current_account_id_ = account_id;
	CookieContainer::setConnectID(current_mail_address_, account_id);
}

HttpResponse WebClient::get()
{
	setMethod("GET");
	setRequestCookies();
	sendRequest();
	setResponseCookies();
	HttpResponse httpResponse(url_, status_code_, response_headers_, response_cookies_, response_body_);
	return httpResponse;
}

HttpResponse WebClient::post(const string& parameter)
{
	setMethod("POST");
	setRequestCookies();
	setContent(parameter);
	setContentType("application/x-www-form-urlencoded");
	sendRequest();
	setResponseCookies();
	HttpResponse httpResponse(url_, status_code_, response_headers_, response_cookies_, response_body_);
	return httpResponse;
}

HttpResponse WebClient::put(ifstream& file_stream)
{
	setMethod("POST");
	setRequestCookies();
	setContent(file_stream);
	setContentType("application/x-www-form-urlencoded");
	sendRequest();
	setResponseCookies();
	HttpResponse httpResponse(url_, status_code_, response_headers_, response_cookies_, response_body_);
	return httpResponse;
}

void WebClient::setRequestCookies()
{
	list<Cookie> cookie_list;
	if(!current_account_id_.empty())
	{
		cookie_list = CookieContainer::getCookieByAccountID(current_account_id_);
	}
	else if(!current_mail_address_.empty())
	{
		cookie_list = CookieContainer::getCookieByMailAddress(current_mail_address_);
	}
	auto it = cookie_list.cbegin();
	while(it != cookie_list.cend())
	{
		request_cookies_.push_back(*it);
		++it;
	}
}

void WebClient::setResponseCookies()
{
	if(!current_account_id_.empty())
	{
		CookieContainer::addCookiesByAccountID(response_cookies_, current_account_id_);
	}
	else if(!current_mail_address_.empty())
	{
		CookieContainer::addCookiesByMailAddress(response_cookies_, current_mail_address_);
	}
}

void WebClient::checkDeadLine()
{
	if (is_cancellation_pending_)
	{
		return;
	}

	if (connect_timer_.expires_at() <= boost::asio::deadline_timer::traits_type::now())
	{
		socket_.lowest_layer().close();

		connect_timer_.expires_at(boost::posix_time::pos_infin);
	}

	connect_timer_.async_wait(boost::bind(&WebClient::checkDeadLine, this));
}

void WebClient::setUserAgent(const string& user_agent)
{
	addHeader("User-Agent", user_agent);
}

string WebClient::getUserAgent() const
{
	return getResponseHeaderValue("User-Agent");
}

int WebClient::getStatusCode()
{
	return status_code_;
}

map<string, string> WebClient::getResponseHeader() const
{
	return response_headers_;
}

string WebClient::getResponseHeaderValue(const string& name) const
{
	map<string, string> headers(response_headers_);
	auto map_iterator = headers.find(name);

	if(map_iterator != headers.end())
	{
		return map_iterator->second;
	}
	return "";
}

string WebClient::getResponseBody() const
{
	return response_body_;
}

void WebClient::setMethod(const string& method)
{
	method_ = method;
}

string WebClient::getMethod() const
{
	return method_;
}

void WebClient::setContentType(const string& content_type)
{
	if(content_type.empty())
	{
		return;
	}
	content_type_ = content_type;
}

string WebClient::getContentType() const
{
	return content_type_;
}

void WebClient::addHeader(const map<string, string> &name_value_pairs)
{
	auto it = name_value_pairs.begin();
	while(it != name_value_pairs.end())
	{
		addHeader((*it).first, (*it).second);
		++it;
	}
}

void WebClient::addHeader(const string& name, const string& value)
{
	request_headers_.insert(pair<string, string>(name, value));
}

string WebClient::escapeString(string source_text)
{
	string destination =  source_text;

	boost::regex  regex("[0-9a-zA-Z_ \\-\\.]");
	boost::smatch smatch;

	string result("");

	string::iterator string_it =  destination.begin();

	while(string_it != destination.end())
	{
		char character = (*string_it);
		const string character_wstring = boost::lexical_cast<string>(character);

		if(boost::regex_search(character_wstring, smatch, regex))
		{
			result += character_wstring;
		}
		else
		{
			bitset<8> bit(character);

			stringstream escaped_stringstream;
			escaped_stringstream << boost::format("%%%02X") % (unsigned long)(bit.to_ulong());
			result += escaped_stringstream.str();
		}
		++string_it;
	}

	return result;
}

string WebClient::escapeParameter(const map<string, string>& post_parameter)
{
	string result("");
	bool first = true;
	auto it = post_parameter.begin();
	while(it != post_parameter.end())
	{
		result += escapeString((*it).first) += "=" + escapeString((*it).second);

		if(first == true)
		{
			first = false;
		}
		else
		{
			result += "&";
		}

		++it;
	}
	return result;
}

void WebClient::addRequestCookie(const Cookie& cookie)
{
	request_cookies_.push_back(cookie);
}

void WebClient::setRequestCookies(const list<Cookie>& cookies)
{
	request_cookies_ = cookies;
}

list<Cookie> WebClient::getResponseCookies() const
{
	return response_cookies_;
}

void WebClient::setContent(const map<string, string> &parameter_pairs)
{
	content_ = escapeParameter(parameter_pairs);
}

void WebClient::setContent(const string& parameter)
{
	content_ = parameter;
}

void WebClient::setContent(ifstream& file_stream)
{
	stringstream request_stream;
	file_stream.seekg(0, ios::beg);

	char buffer[1024];
	while(!file_stream.eof())
	{
		file_stream.read(buffer, sizeof(buffer));
		request_stream.write(buffer, file_stream.gcount());
	}
	
	file_stream.close();
	content_ = request_stream.str();
}

void WebClient::setTimeOut(boost::posix_time::seconds time)
{
	time_out_ = time;
}

void WebClient::sendRequest()
{
	request_stream_ = setRequestStream();
	io_service_.run();
}

void WebClient::cancelConnect()
{
	is_cancellation_pending_ = true;

	response_.consume(response_.size());
	
	boost::system::error_code ignored_ec;
	socket_.lowest_layer().close(ignored_ec);
	connect_timer_.cancel();
	heartbeat_timer_.cancel();
	io_service_.stop();
}

WebClient::~WebClient()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite