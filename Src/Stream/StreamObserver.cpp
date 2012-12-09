#include <Stream/StreamObserver.hpp>
#include <Connection/Connection.hpp>
#include <Connection/Cookie/Cookie.hpp>
#include <Connection/HttpResponse.hpp>
#include <Information/InformationContainer.hpp>
#include <Stream/Post/PostParser/PostParser.hpp>
#include <Stream/Comment/CommentParser/CommentParser.hpp>
#include <Utility/LuaScript.hpp>
#include <Utility/Utility.hpp>
#include <Json/JsonObject.hpp>

#include <boost/asio.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

namespace qi = boost::spirit::qi;
namespace phoenix = boost::phoenix;

StreamObserver::StreamObserver()
{
}

HttpResponse StreamObserver::get(const string& account_id, const string& url)
{
	LuaScript<bool(string, string)> lua_script("LuaScript/streamObserver.lua", "streamObserverUpdate", [&](lua_State* lua_state)
	{
		Connection::bindToScript(lua_state);
		InformationContainer::bindToScript(lua_state);
		PostParser::bindToScript(lua_state);
		CommentParser::bindToScript(lua_state);
		JsonObject::bindToScript(lua_state);
		Utility::bindToScript(lua_state);
		bindToScript(lua_state);
	});

	Connection connection;
	connection.setCurrentAccountID(account_id);

	int chunked_json_size = 0;
	string chunked_json;

	connection.onChunkedContentReceived.connect([&](const std::string& content)
	{
		int position = content.find("\n");
		if(position > 0)
		{
			++position;

			string json_size_string = content.substr(0, position);

			int json_size = 0;

			if(qi::parse(json_size_string.cbegin(), json_size_string.cend(), qi::int_[phoenix::ref(json_size) = qi::_1] >> (qi::lit("\r\n") | qi::lit("\n"))))
			{
				if(json_size > 0)
				{
					chunked_json_size = json_size;
					chunked_json = content;
				}
			} 
			else if(chunked_json_size > 0)
			{
				chunked_json += content;
			}
		}
		else
		{
			if(chunked_json_size > 0)
			{
				chunked_json += content;
			}
		}

		if(chunked_json_size > 0)
		{
			int size = chunked_json.size();
			if(chunked_json_size <= size)
			{
				auto result = lua_script(account_id, chunked_json);
			}
		}

		
		//add(account_id, content);
	});
	return connection.httpGet(url, false);
}

void StreamObserver::scriptSleep(long milliseconds)
{
	boost::asio::io_service io_service;
	boost::asio::deadline_timer timer(io_service);

	timer.expires_from_now(boost::posix_time::milliseconds(milliseconds));
	timer.wait();
}

void StreamObserver::bindToScript(lua_State* lua_state)
{
	module(lua_state)
		[
			class_<StreamObserver>("StreamObserver")
			.def(constructor<>())
			.def("get", &StreamObserver::get)
			.def("scriptSleep", &StreamObserver::scriptSleep)
		];
}

StreamObserver::~StreamObserver()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite