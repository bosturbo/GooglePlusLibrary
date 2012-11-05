#include <Connection/Connection.hpp>
#include <Connection/HttpResponse.hpp>
#include <Connection/WebClient/WebClient.hpp>
#include <Connection/WebClient/WebClientCppNetlib.hpp>
#include <Connection/Cookie/CookieContainer.hpp>
#include <Connection/Cookie/Cookie.hpp>
#include <Utility/Utility.hpp>
#include <Utility/LuaScript.hpp>
#include <Json/JsonObject.hpp>
#include <Json/JsonParser.hpp>

#include <boost/regex.hpp>
#include <boost/format.hpp>

#include <luabind/luabind.hpp>
#include <utf8.h>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

Connection::Connection()
:user_agent_("Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.5 (KHTML, like Gecko) Chrome/19.0.1084.52 Safari/536.5"), 
time_out_(86400), 
current_mail_address_(""), 
current_account_id_("")
{
	/*!
	* @~english
	* @todo The library developer Try to update the value of the user_agent_ as quickly as possible if Google Chrome has been updated.
	* @~japanese
	* @todo ライブラリ開発者はGoogle Chromeが更新された場合、ライブラリ開発者は可能な限り迅速にuser_agent_の値を更新すること
	*/

	LuaScript<string()> lua_script("LuaScript/Constant.lua", "getUserAgent", [](lua_State* lua_state){});

	auto result = lua_script();
	if(!result.empty())
	{
		user_agent_ = result;
	}
}

void Connection::setCurrentMailAddress(const string& mail_address)
{
	current_mail_address_ = mail_address;
}

void Connection::setCurrentAccountID(const string& account_id)
{
	current_account_id_ = account_id;
	CookieContainer::setConnectID(current_mail_address_, account_id);
}

void Connection::setUserAgent(const string& user_agent)
{
	user_agent_ = user_agent;
}

string Connection::getUserAgent() const
{
	return user_agent_;
}

void Connection::setTimeOut(long time_seconds)
{
	time_out_ = time_seconds;
}

long Connection::getTimeOut() const
{
	return time_out_;
}

namespace
{
	void addResponseCookieByAccountID(const list<Cookie>& response_cookie, const string& account_id)
	{
		auto it = response_cookie.begin();
		while(it !=response_cookie.end())
		{
			CookieContainer::addCookieByAccountID(*it, account_id);
			++it;
		}
	}

	void addResponseCookieByMailAddress(const list<Cookie>& response_cookie, const string& mail_address)
	{
		auto it = response_cookie.begin();
		while(it !=response_cookie.end())
		{
			CookieContainer::addCookieByMailAddress(*it, mail_address);
			++it;
		}
	}
}

HttpResponse Connection::httpGet(const string& url, bool auto_redirect)
{
	string location = url;

	HttpResponse http_response;

	if(auto_redirect)
	{
		int a = 3;
	}

	static int redirect_count = 0;
	do 
	{
		WebClient client(location);
		client.setUserAgent(user_agent_);
		client.setCurrentMailAddress(current_mail_address_);
		client.setCurrentAccountID(current_account_id_);
		http_response = client.get();

		//cout << http_response.getResponseBody() << endl;
		//wcout << Utility::convertUTF8ToUnicode(http_response.getResponseBody()) << endl;
		
		location = http_response.getRedirectUrl();

		++redirect_count;
	}
	while ((auto_redirect == true) && (!location.empty()) && (redirect_count < 30));

	onResponseReceived(http_response);
	return http_response;
}

HttpResponse Connection::httpPost(const string& url, const map<string, string>& parameter_pairs)
{
	string parameter("");
	bool first = true;
	auto it = parameter_pairs.begin();
	while(it != parameter_pairs.end())
	{
		parameter += (it->first + "=" + it->second);

		if(first == true)
		{
			first = false;
		}
		else
		{
			parameter += "&";
		}

		++it;
	}
	return httpPost(url, parameter);
}

HttpResponse Connection::httpPost(const string& url, const string& parameter)
{
	WebClient client(url);
	client.setUserAgent(user_agent_);
	client.setCurrentMailAddress(current_mail_address_);
	client.setCurrentAccountID(current_account_id_);
	HttpResponse http_response = client.post(parameter);

	//cout << http_response.getResponseBody() << endl;
	//wcout << Utility::convertUTF8ToUnicode(http_response.getResponseBody()) << endl;
	
	onResponseReceived(http_response);
	return http_response;
}

HttpResponse Connection::httpPut(const string& url, ifstream& file_stream)
{
	WebClient client(url);
	client.setUserAgent(user_agent_);
	client.setCurrentMailAddress(current_mail_address_);
	client.setCurrentAccountID(current_account_id_);
	HttpResponse http_response = client.put(file_stream);
	onResponseReceived(http_response);
	return http_response;
}

JsonObject Connection::convertResponseToJson(const string& response)
{
	string::const_iterator end_it = utf8::find_invalid(response.cbegin(), response.cend());

	if (end_it != response.cend())
	{
		cout << "Invalid UTF-8 encoding detected\n";
		//cout << "This part is fine: " << string(response.cbegin(), end_it) << "\n";

		static int count = 1;
		wstringstream string_stream;
		string_stream << "InvalidUTF-8Response";
		string_stream << count;
		string_stream << ".txt";
		FILE* response_file;
		response_file = _wfopen(string_stream.str().c_str(), L"w, ccs=UTF-16LE");
		fwprintf(response_file, Utility::convertUTF8ToUnicode(string(response.cbegin(), end_it)).c_str());
		fclose(response_file);
		++count;
	}

	JsonParser parser;
	return parser.parse(Utility::convertUTF8ToUnicode(response));
}

JsonObject Connection::convertResponseToJson(const HttpResponse& response)
{
	HttpResponse http_response = response;
	return convertResponseToJson(http_response.getResponseBody());
}

string Connection::escapeString(string source_text)
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

void Connection::bindToScript(lua_State* lua_state)
{
	module(lua_state)
		[
			class_<Connection>("Connection")
			.def(constructor<>())
			.def("setCurrentAccountID", &Connection::setCurrentAccountID)
			.def("setCurrentMailAddress", &Connection::setCurrentMailAddress)
			.def("httpGet", static_cast<HttpResponse(Connection::*)(const string&, bool)>(&Connection::httpGet))
			.def("httpPost", static_cast<HttpResponse(Connection::*)(const string&, const map<string, string>&)>(&Connection::httpPost))
			.def("httpPost", static_cast<HttpResponse(Connection::*)(const string&, const string&)>(&Connection::httpPost))
			.def("httpPut", static_cast<HttpResponse(Connection::*)(const string&, ifstream&)>(&Connection::httpPut))
			.def("convertResponseToJson", static_cast<JsonObject(Connection::*)(const string&)>(&Connection::convertResponseToJson))
			.def("convertResponseToJson", static_cast<JsonObject(Connection::*)(const HttpResponse&)>(&Connection::convertResponseToJson))

			.scope
				[
					def("escapeString", &Connection::escapeString)
				]
		];
}

Connection::~Connection()
{

}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite