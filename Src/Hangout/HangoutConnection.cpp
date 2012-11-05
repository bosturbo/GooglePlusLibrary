#include <Hangout/HangoutConnection.hpp>

#include <Connection/Connection.hpp>
#include <Connection/Cookie/Cookie.hpp>
#include <Connection/HttpResponse.hpp>
#include <Utility/Utility.hpp>
#include <Information/InformationContainer.hpp>
#include <Utility/LuaScript.hpp>
#include <Json/JsonObject.hpp>

#include <luabind/luabind.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

HangoutConnection::HangoutConnection()
:is_cancellation_pending_(false)
{
}

void HangoutConnection::initialize(const wstring& account_id)
{
	initializeAsync(account_id);
	waitInitializeAsync();
}

void HangoutConnection::initializeAsync(const wstring& account_id)
{
	boost::thread connect_thread(boost::bind(&HangoutConnection::initializeAsyncThreadMethod, this, account_id));
	initialize_thread_ = boost::move(connect_thread);
}

void HangoutConnection::waitInitializeAsync()
{
	initialize_thread_.join();
}

void HangoutConnection::initializeAsyncThreadMethod(const wstring& account_id)
{
	LuaScript<bool(string)> lua_script("LuaScript/CreateHangout.lua", "createHangout", [](lua_State* lua_state)
	{
		Utility::bindToScript(lua_state);
		Connection::bindToScript(lua_state);
		HttpResponse::bindToScript(lua_state);
		InformationContainer::bindToScript(lua_state);
		JsonObject::bindToScript(lua_state);
	});

	auto result = lua_script(Utility::convertUnicodeToUTF8(account_id));
	if(result == false)
	{
		return;
	}

	boost::thread update_thread(boost::bind(&HangoutConnection::update, this, account_id));
	update_thread_ = boost::move(update_thread);
}

void HangoutConnection::update(const wstring& account_id)
{
	LuaScript<bool(string)> lua_script("LuaScript/HangoutLoopUpdate.lua", "HangoutLoopUpdate", [](lua_State* lua_state)
	{
		Connection::bindToScript(lua_state);
		HttpResponse::bindToScript(lua_state);
		Utility::bindToScript(lua_state);
		InformationContainer::bindToScript(lua_state);
		JsonObject::bindToScript(lua_state);
		bindToScript(lua_state);
	});

	while(!is_cancellation_pending_)
	{
		auto result = lua_script(Utility::convertUnicodeToUTF8(account_id));
		if(result == false)
		{
			is_cancellation_pending_ = true;
			return;
		}
	}
}

void HangoutConnection::bindToScript(lua_State* lua_state)
{
	module(lua_state)
		[
			class_<HangoutConnection>("HangoutConnection")
			.def(constructor<>())
			.def("update", &HangoutConnection::update)
		];
}

HangoutConnection::~HangoutConnection()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite