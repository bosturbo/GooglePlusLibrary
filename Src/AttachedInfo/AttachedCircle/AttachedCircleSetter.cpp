#include <AttachedInfo/AttachedCircle/AttachedCircleSetter.hpp>

#include <Utility/LuaScript.hpp>
#include <Utility/Utility.hpp>

#include <Json/JsonObject.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

AttachedCircleSetter::AttachedCircleSetter()
{
}

AttachedCircleSetter AttachedCircleSetter::parse(JsonObject& json)
{
	LuaScript<AttachedCircleSetter(JsonObject*)> lua_script("LuaScript/ParseAttachedCircle.lua", "parseAttachedCircle", [](lua_State* lua_state)
	{
		Utility::bindToScript(lua_state);
		JsonObject::bindToScript(lua_state);
		bindToScript(lua_state);
	});

	return lua_script(&json);
}

AttachedCircleSetter AttachedCircleSetter::parse(luabind::object json)
{
	if (luabind::type(json) != LUA_TLIGHTUSERDATA)
	{
		return AttachedCircleSetter();
	}
	JsonObject* node_pointer = static_cast<JsonObject*>(lua_touserdata(json.interpreter(),1));
	return parse(*node_pointer);
}

void AttachedCircleSetter::addAccount(const wstring& account_id)
{
	//account_list_(attached_circle_)->add(account_id);
}

AttachedCircle AttachedCircleSetter::toAttachedCircle()
{
	return attached_circle_;
}

void AttachedCircleSetter::bindToScript(lua_State* lua_state)
{
	module(lua_state)
		[
			class_<AttachedCircleSetter>("AttachedCircleSetter")
			.def(constructor<>())
		];
}

AttachedCircleSetter::~AttachedCircleSetter()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite