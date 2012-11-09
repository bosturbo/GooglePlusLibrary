#include <Connection/HttpResponse.hpp>
#include <Connection/Uri.hpp>
#include <Connection/Cookie/Cookie.hpp>
#include <Utility/Utility.hpp>

#include <boost/lexical_cast.hpp>
#include <luabind/luabind.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

HttpResponse::HttpResponse()
:url_(""),
status_code_(0),
response_body_(""), 
response_header_(), 
response_cookie_(),
redirect_url_("")
{
}

HttpResponse::HttpResponse(const string& url, int status_code,
const map<string, string>& response_header, 
const list<Cookie>& response_cookie, 
const string& response_body)
:url_(url),
status_code_(status_code),
response_body_(response_body), 
response_header_(response_header), 
response_cookie_(response_cookie)
{
	auto it = response_header.begin();
	while(it != response_header.end())
	{
		if(it->first == "Location")
		{
			redirect_url_ = it->second;

			string scheme = redirect_url_.substr(0, 4);
			if(scheme != "http")
			{
				Uri uri(url);
				string target = uri.getScheme() + "://" + uri.getHost();
				redirect_url_ = target + redirect_url_;
			}
		}
		//response_header_.insert(map<string, string>::value_type(it->first, it->second));
		++it;
	}
}

string HttpResponse::getUrl() const
{
	return url_;
}

int HttpResponse::getStatusCode()
{
	return status_code_;
}

void HttpResponse::setResponseBody(const string& response_body)
{
	response_body_ = response_body;
}

string HttpResponse::getResponseBody() const
{
	return response_body_;
}

void HttpResponse::showResponseCookies()
{
	auto it = response_cookie_.begin();
	while(it != response_cookie_.end())
	{
		++it;
	}
}

void HttpResponse::setResponseCookies(const list<Cookie>& cookies)
{
	response_cookie_ = cookies;
}

list<Cookie> HttpResponse::getResponseCookies() const
{
	return response_cookie_;
}

string HttpResponse::getResponseCookie(const string& name)
{
	auto it = response_cookie_.begin();
	while(it != response_cookie_.end())
	{
		if((*it).getName() == name)
		{
			return (*it).getValue();
		}

		++it;
	}
	return "";
}

void HttpResponse::setResponseHeader(map<string, string> headers)
{
	response_header_ = headers;
}

map<string, string> HttpResponse::getResponseHeaderValues() const
{
	return response_header_;
}

string HttpResponse::getResponseHeaderValue(const string& name) const
{
	map<string, string> headers(response_header_);
	auto map_iterator = headers.find(name);

	if(map_iterator != headers.end())
	{
		return map_iterator->second;
	}

	return "";
}

string HttpResponse::getRedirectUrl()
{
	return redirect_url_;
}

HttpResponse::~HttpResponse()
{
}

void HttpResponse::bindToScript(lua_State* lua_state)
{
	module(lua_state)
		[
			class_<HttpResponse>("HttpResponse")
			.def("getStatusCode", &HttpResponse::getStatusCode)
			.def("getResponseBody", &HttpResponse::getResponseBody)
			.def("getResponseHeaderValue", &HttpResponse::getResponseHeaderValue)
			.def("getResponseCookies", &HttpResponse::getResponseCookies)
			.def("showResponseCookies", &HttpResponse::showResponseCookies)
			.def("getResponseCookie", &HttpResponse::getResponseCookie)
		];
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
