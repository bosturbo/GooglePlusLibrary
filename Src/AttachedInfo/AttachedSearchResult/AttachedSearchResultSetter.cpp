#include <AttachedInfo/AttachedSearchResult/AttachedSearchResultSetter.hpp>

#include <Utility/Utility.hpp>
#include <Utility/LuaScript.hpp>
#include <Connection/Connection.hpp>
#include <Json/JsonObject.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

AttachedSearchResultSetter::AttachedSearchResultSetter()
{
}

AttachedSearchResultSetter AttachedSearchResultSetter::parse(JsonObject& json)
{
	LuaScript<AttachedSearchResultSetter(JsonObject*)> lua_script("LuaScript/ParseAttachedSearchResult.lua", "parseAttachedSearchResult", [](lua_State* lua_state)
	{
		Connection::bindToScript(lua_state);
		JsonObject::bindToScript(lua_state);
		bindToScript(lua_state);
	});

	return lua_script(&json);
}

AttachedSearchResultSetter AttachedSearchResultSetter::parse(luabind::object json)
{
	if (luabind::type(json) != LUA_TLIGHTUSERDATA)
	{
		return AttachedSearchResultSetter();
	}
	JsonObject* node_pointer = static_cast<JsonObject*>(lua_touserdata(json.interpreter(),1));
	return parse(*node_pointer);
}

string AttachedSearchResultSetter::getSearchKeyword()
{
	return Utility::convertUnicodeToUTF8(search_keyword_(attached_search_result_));
}

void AttachedSearchResultSetter::setSearchKeyword(const string& search_keyword)
{
	setSearchKeyword(Utility::convertUTF8ToUnicode(search_keyword));
}

void AttachedSearchResultSetter::setSearchKeyword(const wstring& search_keyword)
{
	search_keyword_(attached_search_result_) = search_keyword;
}

void AttachedSearchResultSetter::setSearchResultPageUrl(const string& search_result_page_url)
{
	setSearchResultPageUrl(Utility::convertUTF8ToUnicode(search_result_page_url));
}

void AttachedSearchResultSetter::setSearchResultPageUrl(const wstring& search_result_page_url)
{
	search_result_page_url_(attached_search_result_) = search_result_page_url;
}

AttachedSearchResult AttachedSearchResultSetter::toAttachedSearchResult()
{
	return attached_search_result_;
}

void AttachedSearchResultSetter::bindToScript(lua_State* lua_state)
{
	module(lua_state)
		[
			class_<AttachedSearchResultSetter>("AttachedSearchResultSetter")
			.def(constructor<>())
			.scope
				[
					def("parse", static_cast<AttachedSearchResultSetter(*)(JsonObject&)>(&AttachedSearchResultSetter::parse))
				]
			.scope
				[
					def("parse", static_cast<AttachedSearchResultSetter(*)(luabind::object)>(&AttachedSearchResultSetter::parse))
				]
			.def("getSearchKeyword", &AttachedSearchResultSetter::getSearchKeyword)
			.def("setSearchKeyword", static_cast<void(AttachedSearchResultSetter::*)(const string&)>(&AttachedSearchResultSetter::setSearchKeyword))
			.def("setSearchResultPageUrl", static_cast<void(AttachedSearchResultSetter::*)(const string&)>(&AttachedSearchResultSetter::setSearchResultPageUrl))
		];
}

AttachedSearchResultSetter::~AttachedSearchResultSetter()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite