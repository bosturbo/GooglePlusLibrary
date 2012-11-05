#include <Connection/Talkgadget/TalkgadgetConnection.hpp>

#include <Connection/Connection.hpp>
#include <Connection/Cookie/Cookie.hpp>
#include <Connection/HttpResponse.hpp>
#include <Utility/Utility.hpp>
#include <Information/InformationContainer.hpp>
#include <Stream/StreamConnection.hpp>
#include <Utility/LuaScript.hpp>

#include <luabind/luabind.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

talkgadgetConnection::talkgadgetConnection()
:connect_count_(0),
maximum_connect_count_(5),
is_canceled_(false)
{
}

void talkgadgetConnection::connect(const wstring& account_id, BOOST_SCOPED_ENUM(ConnectionMode) connection_mode)
{
	if(account_id.empty())
	{
		return;
	}
	connectAsync(account_id, connection_mode);
	waitConnectAsync();
}

void talkgadgetConnection::connectAsync(const wstring& account_id, BOOST_SCOPED_ENUM(ConnectionMode) connection_mode)
{
	if(account_id.empty())
	{
		return;
	}
	boost::thread connect_thread(boost::bind(&talkgadgetConnection::connectAsyncThreadMethod, this, account_id, connection_mode));
	connect_thread_ = boost::move(connect_thread);
}

void talkgadgetConnection::waitConnectAsync()
{
	connect_thread_.join();
}

void talkgadgetConnection::connectAsyncThreadMethod(const wstring& account_id, BOOST_SCOPED_ENUM(ConnectionMode) connection_mode)
{
	if(getConnectCount() > getMaximumConnectCount())
	{
		is_canceled_ = true;
		return;
	}

	LuaScript<bool(string, string)> lua_script("LuaScript/TalkgadgetConnect.lua", "talkgadgetConnect", [](lua_State* lua_state)
	{
		Connection::bindToScript(lua_state);
		HttpResponse::bindToScript(lua_state);
		Utility::bindToScript(lua_state);
		InformationContainer::bindToScript(lua_state);
	});

	lua_script.onLoadingScriptFailed.connect([&](string message)
	{
		cout << "TalkGadgetConnect.lua‚ðŽÀs‚Å‚«‚Ü‚¹‚ñ‚Å‚µ‚½\n" << endl;
		cout << "error : " << message << "\n" << endl;
		setConnectCount(getConnectCount() + 1);
		connectAsyncThreadMethod(account_id, connection_mode);
	});

	lua_script.onRunningScriptFailed.connect([&](string message)
	{
		cout << "error : " << message << "\n" << endl;
		setConnectCount(getConnectCount() + 1);
		connectAsyncThreadMethod(account_id, connection_mode);
	});

	string mode = "homepage";
	switch(connection_mode)
	{
	case ConnectionMode::Homepage:
		mode = "homepage";
		break;
	case ConnectionMode::Hangout:
		mode = "hangout";
		break;
	}

	auto result = lua_script(Utility::convertUnicodeToUTF8(account_id), mode);
	if(result == false)
	{
		// talkgadget connect failed
		setConnectCount(getConnectCount() + 1);
		connectAsyncThreadMethod(account_id, connection_mode);
	}

	if(!is_canceled_)
	{
		stream_connection_ = make_shared<StreamConnection>();
		stream_connection_->initialize(account_id);
	}
}

int talkgadgetConnection::getConnectCount() const
{
	return connect_count_;
}

void talkgadgetConnection::setConnectCount(int connect_count)
{
	connect_count_ = connect_count;
}

int talkgadgetConnection::getMaximumConnectCount() const
{
	return maximum_connect_count_;
}

void talkgadgetConnection::setMaximumConnectCount(int maximum_connect_count)
{
	maximum_connect_count_ = maximum_connect_count;
}

talkgadgetConnection::~talkgadgetConnection()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite