#pragma once

#include <boost/filesystem/path.hpp>

#include <luabind/luabind.hpp>

class LuaData
{
public:
	LuaData();

	template<typename T>
	static void pushData(lua_State* lua_state, T value, typename boost::enable_if<boost::is_void<T> >::type* = nullptr)
	{
	}

	template<typename T>
	static void pushData(lua_State* lua_state, T value, typename boost::disable_if<boost::is_void<T> >::type* = nullptr)
	{
		luabind::object luabind_object = luabind::object(lua_state, value);
		luabind_object.push(lua_state);
	}

	template<typename T>
	static T getData(lua_State* lua_state, typename boost::disable_if<boost::is_void<T> >::type* = nullptr)
	{
		luabind::object luabind_object = luabind::object(luabind::from_stack(lua_state, -1));
		return luabind::object_cast<T>(luabind_object);
	}

	
	template<typename T>
	static void getData(lua_State* lua_state, typename boost::enable_if<boost::is_void<T> >::type* = nullptr)
	{
	}
	
	virtual ~LuaData();
};
