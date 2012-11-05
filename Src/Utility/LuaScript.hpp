#ifndef BOOST_PP_IS_ITERATING

#ifndef GPLUSNASITE_LUA_SCRIPT_NVT_HPP_INCLUDED
#define GPLUSNASITE_LUA_SCRIPT_NVT_HPP_INCLUDED

#include <Utility/LuaData.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition.hpp>

#include <boost/signals2.hpp>
#include <boost/utility/value_init.hpp>

#include <lua.hpp>

#ifndef GPLUSNASITE_LUA_SCRIPT_MAX_ARITY
#define GPLUSNASITE_LUA_SCRIPT_MAX_ARITY 5
#endif

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

#define BOOST_PP_ITERATION_LIMITS (0, GPLUSNASITE_LUA_SCRIPT_MAX_ARITY - 1)
#define BOOST_PP_FILENAME_1 "LuaScript.hpp"
#include BOOST_PP_ITERATE()

}// namespace GooglePlusLibrary
}// namespace Gplusnasite

#endif // GPLUSNASITE_LUA_SCRIPT_HPP_INCLUDED

#else // BOOST_PP_IS_ITERATING

#define n BOOST_PP_ITERATION()

#define GPLUSNASITE_LUA_SCRIPT_pushData(z, m, text) \
LuaData::pushData<BOOST_PP_CAT(T, m)>(lua_state.get(), BOOST_PP_CAT(param, m));
	

template <typename Signature>
class LuaScript;

template <typename R BOOST_PP_ENUM_TRAILING_PARAMS(n, typename T)>
class LuaScript<R(BOOST_PP_ENUM_PARAMS(n, T))>
{
public:
	LuaScript(void){}

	LuaScript(const std::string& script_file_path, const std::string& function_name)
	:script_file_path_(script_file_path), function_name_(function_name)
	{
	}

	template<typename F>
	LuaScript(const std::string& script_file_path, const std::string& function_name, F f)
	:script_file_path_(script_file_path), function_name_(function_name)
	{
		func_list_.connect(f);
	}

public:
	template<typename F>
	void operator+=(F function)
	{
		func_list_.connect(function);
	}
	
	bool loadScript(lua_State* lua_state)
	{
		func_list_(lua_state);

		if(luaL_dofile(lua_state, getScriptFilePath().c_str()))
		{
			if(onLoadingScriptFailed.empty())
			{
				std::cout <<getScriptFileName() <<"‚ðŽÀs‚Å‚«‚Ü‚¹‚ñ‚Å‚µ‚½\n" <<std::endl;
				std::cout <<"error : " <<lua_tostring(lua_state, -1) <<"\n" <<std::endl;
			}
			else
			{
				onLoadingScriptFailed(lua_tostring(lua_state, -1));
			}
			return false;
		}

		lua_getglobal(lua_state, getFunctionName().c_str());

		return true;
	}

	boost::signals2::signal<void (std::string)> onLoadingScriptFailed;

	bool runScript(lua_State* lua_state, int arg_number, int returnNumber)
	{
		if(lua_pcall(lua_state, arg_number, returnNumber, 0))
		{
			if(onRunningScriptFailed.empty())
			{
				std::cout <<getScriptFileName() <<"“à" <<getFunctionName() <<"‚ÅƒGƒ‰[‚ª”­¶‚µ‚Ü‚µ‚½\n" <<std::endl;
				std::cout <<"error : " <<lua_tostring(lua_state, -1) <<"\n" <<std::endl;
			}
			else
			{
				onRunningScriptFailed(lua_tostring(lua_state, -1));
			}
			return false;
		}
		return true;
	}

	boost::signals2::signal<void (std::string)> onRunningScriptFailed;
	
	R operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, T, param))
	{
		std::shared_ptr<lua_State> lua_state(luaL_newstate(),[](lua_State* lua_state_ptr){lua_close(lua_state_ptr);});

		luaL_openlibs(lua_state.get());

		luabind::open(lua_state.get());

		if(!loadScript(lua_state.get()))
		{
			boost::value_initialized<R> result;
			return result;
		}

		BOOST_PP_REPEAT(n, GPLUSNASITE_LUA_SCRIPT_pushData, nil)

		if(!runScript(lua_state.get(), n, returnNumber()))
		{
			boost::value_initialized<R> result;
			return result;
		}

		if(boost::is_void<R>())
		{
			boost::value_initialized<R> result;
			return result;
		}
		else
		{
			return LuaData::getData<R>(lua_state.get());
		}
	}
	
	int returnNumber()
	{
		if(boost::is_void<R>())
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}

public:
	std::string getScriptFilePath()
	{
		return script_file_path_;
	}

	void setScriptFilePath(const std::string& script_file)
	{
		script_file_path_ = script_file;
	}

private:
	std::string script_file_path_;

public:
	std::string getScriptFileName()
	{
		if(getScriptFilePath().empty())
		{
			return "";
		}
		boost::filesystem::path path(script_file_path_);
		return path.filename().string();
	}

public:
	std::string getFunctionName()
	{
		return function_name_;
	}

	void setFunctionName(const std::string& function_name)
	{
		function_name_ = function_name;
	}

private:
	std::string function_name_;

public:
	virtual ~LuaScript(void){}

private:
	boost::signals2::signal<void (lua_State* lua_state)> func_list_;
};

#undef GPLUSNASITE_LUA_SCRIPT_pushData
#undef n

#endif // BOOST_PP_IS_ITERATING