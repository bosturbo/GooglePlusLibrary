#include <Notification/NotificationList.hpp>

#include <Utility/Utility.hpp>
#include <Connection/Connection.hpp>
#include <Connection/Cookie/Cookie.hpp>
#include <Connection/HttpResponse.hpp>
#include <Utility/LuaScript.hpp>
#include <Json/JsonObject.hpp>

#include <string>

#include <luabind/luabind.hpp>

using namespace std;
using namespace ::luabind;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

NotificationList::NotificationList()
{
}

void NotificationList::update()
{
	LuaScript<bool(string)> lua_script("LuaScript/UpdateNotificationList.lua", "updateNotificationList", [](lua_State* lua_state)
	{
		Utility::bindToScript(lua_state);
		Connection::bindToScript(lua_state);
		HttpResponse::bindToScript(lua_state);
		JsonObject::bindToScript(lua_state);
		bindToScript(lua_state);
	});

	//! @todo ちゃんとアカウントIDを設定したりするアクセサを実装しておくこと
	wstring account_id;

	lua_script(Utility::convertUnicodeToUTF8(account_id));
}

void NotificationList::bindToScript(lua_State* lua_state)
{

}

NotificationList::~NotificationList()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite