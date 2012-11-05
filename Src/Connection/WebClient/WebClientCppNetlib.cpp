#include <Connection/WebClient/WebClientCppNetlib.hpp>
#include <Connection/Cookie/Cookie.hpp>
#include <Connection/Cookie/CookieContainer.hpp>
#include <Connection/HttpResponse.hpp>

#include <boost/network/protocol/http/client.hpp>
#include <fstream>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
namespace http = boost::network::http;

WebClientCppNetlib::WebClientCppNetlib()
:url_(""),
user_agent_(""),
request_headers_(),
request_cookies_(),
response_cookies_()
{
}

WebClientCppNetlib::WebClientCppNetlib(const string& url)
:url_(url),
user_agent_(""),
request_headers_(),
request_cookies_(),
response_cookies_()
{
}

void WebClientCppNetlib::setRequestSetting(http::client::request& request)
{
	request.add_header(pair<string, string>("User-Agent", user_agent_));
	request.add_header(pair<string, string>("Connection", "keep-alive"));
	//request.add_header(pair<string, string>("Accept-Encoding", "gzip, deflate"));

	string request_cookie_string("");

	auto request_cookie_it = request_cookies_.cbegin();
	while(request_cookie_it != request_cookies_.cend())
	{
		request_cookie_string += (request_cookie_it->getName() + "=" + request_cookie_it->getValue() + ";");
		++request_cookie_it;
	}
	if(!request_cookie_string.empty())
	{
		request.add_header(pair<string, string>("Cookie", request_cookie_string));
	}

	auto request_header_it = request_headers_.cbegin();
	while(request_header_it != request_headers_.cend())
	{
		request.add_header(pair<string, string>(request_header_it->first, request_header_it->second));
		++request_header_it;
	}
}

void WebClientCppNetlib::setCurrentMailAddress(const string& mail_address)
{
	current_mail_address_ = mail_address;
}

void WebClientCppNetlib::setCurrentAccountID(const string& account_id)
{
	current_account_id_ = account_id;
	CookieContainer::setConnectID(current_mail_address_, account_id);
}

/*
struct body_handler {
	explicit body_handler(string & body)
		: body(body) {}

	BOOST_NETWORK_HTTP_BODY_CALLBACK(operator(), range, error) {
		// in here, range is the Boost.Range iterator_range, and error is
		// the Boost.System error code.
		if (!error)
			body.append(boost::begin(range), boost::end(range));
	}

	string & body;
};
*/

struct body_handler
{
	explicit body_handler(string & body)
		: body(body) {}

	BOOST_NETWORK_HTTP_BODY_CALLBACK(operator(), range, error)
	{
		// in here, range is the Boost.Range iterator_range, and error is
		// the Boost.System error code.
		if (!error)
		{
			cout << "Received " << boost::distance(range) << "bytes.\r\n";
			body.append(boost::begin(range), boost::end(range));
		}
		else
		{
			cout << "Error: " << error.message() << endl;
		}
	}

	string & body;
};

void WebClientCppNetlib::function_name(boost::iterator_range<const char*> const & range_name, boost::system::error_code const & error_name)
{
	int distance = boost::distance(range_name);
	if(distance == 0)
	{
		int a = 3;
		return;
	}
	string response(boost::begin(range_name), boost::end(range_name));
	
	cout << "1----------------------------------------------------" << endl;
	
	if(response.size() > 2)
	{
		cout << response.substr(0, response.size() - 2) << endl;
	}
	else
	{
		cout << response << endl;
	}

	cout << "2----------------------------------------------------" << endl;
	
	int position = response.find("\"dsh\"");
	if(position >= 0)
	{
		int count = 3;
	}

	body_ += response;
}

HttpResponse WebClientCppNetlib::get()
{
	try
	{
		body_ = "";
		string response("");
		http::client client;
		http::client::request request(url_);
		setRequestCookies();
		setRequestSetting(request);
		
		cout << "Get Start" << endl;
		
		//HttpResponse http_response(url_, client.get(request));
		HttpResponse http_response(url_, client.get(request , http::_body_handler = boost::bind(&WebClientCppNetlib::function_name, this, _1, _2)));
		http_response.setResponseBody(body_);
		setResponseCookies();
		int position = http_response.getResponseBody().find("\"dsh\"");
		if(position >= 0)
		{
			int count = 3;
		}

		return http_response;
	}
	catch(exception)
	{
		return HttpResponse();
	}
}

HttpResponse WebClientCppNetlib::getStreaming()
{
	try
	{
		body_ = "";
		string response("");
		http::client client;
		http::client::request request(url_);
		setRequestSetting(request);
		cout << "Get Start" << endl;
		HttpResponse http_response(url_, client.get(request , http::_body_handler = boost::bind(&WebClientCppNetlib::function_name, this, _1, _2)));
		http_response.setResponseBody(body_);
		return http_response;
	}
	catch(exception)
	{
		return HttpResponse();
	}
}

HttpResponse WebClientCppNetlib::post(const string& parameter)
{
	try
	{
		http::client client;
		http::client::request request(url_);
		setRequestSetting(request);
		cout << "Post Start" << endl;
		HttpResponse http_response(url_, client.post(request, parameter));
		return http_response;
	}
	catch(exception)
	{
		return HttpResponse();
	}
}

HttpResponse WebClientCppNetlib::put(ifstream& file_stream)
{
	try
	{
		http::client client;
		http::client::request request(url_);
		setRequestSetting(request);

		stringstream request_stream;
		size_t filesize = (size_t)file_stream.seekg(0, ios::end).tellg();
		file_stream.seekg(0, ios::beg);

		char buffer[1024];

		while(!file_stream.eof())
		{
			file_stream.read(buffer, sizeof(buffer));
			request_stream.write(buffer, file_stream.gcount());
		}

		file_stream.close();
	
		HttpResponse http_response(url_, client.put(request, request_stream.str()));
		return http_response;
	}
	catch(exception)
	{
		return HttpResponse();
	}
}

void WebClientCppNetlib::setUserAgent(const string& user_agent)
{
	user_agent_ = user_agent;
}

void WebClientCppNetlib::addHeader(const map<string, string> &name_value_pairs)
{
	auto it = name_value_pairs.begin();
	while(it != name_value_pairs.end())
	{
		addHeader((*it).first, (*it).second);
		++it;
	}
}

void WebClientCppNetlib::addHeader(const string& name, const string& value)
{
	request_headers_.insert(pair<string, string>(name, value));
}

void WebClientCppNetlib::addRequestCookie(const Cookie& cookie)
{
	request_cookies_.push_back(cookie);
}

void WebClientCppNetlib::setRequestCookies()
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

void WebClientCppNetlib::setRequestCookies(const list<Cookie>& cookies)
{
	request_cookies_ = cookies;
}

void WebClientCppNetlib::setResponseCookies()
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

WebClientCppNetlib::~WebClientCppNetlib()
{
}


}// namespace GooglePlusLibrary
}// namespace Gplusnasite