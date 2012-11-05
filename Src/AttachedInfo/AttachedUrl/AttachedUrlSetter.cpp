#include <AttachedInfo/AttachedUrl/AttachedUrlSetter.hpp>
#include <Utility/Utility.hpp>
#include <Utility/LuaScript.hpp>
#include <Json/JsonObject.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

AttachedUrlSetter::AttachedUrlSetter()
{
}

AttachedUrlSetter AttachedUrlSetter::parse(JsonObject& json)
{
	LuaScript<AttachedUrlSetter(JsonObject*)> lua_script("LuaScript/ParseAttachedUrl.lua", "parseAttachedUrl", [](lua_State* lua_state)
	{
		Utility::bindToScript(lua_state);
		JsonObject::bindToScript(lua_state);
		bindToScript(lua_state);
	});

	return lua_script(&json);
}

AttachedUrlSetter AttachedUrlSetter::parse(luabind::object json)
{
	if (luabind::type(json) != LUA_TLIGHTUSERDATA)
	{
		return AttachedUrlSetter();
	}
	JsonObject* node_pointer = static_cast<JsonObject*>(lua_touserdata(json.interpreter(),1));
	return parse(*node_pointer);
}

void AttachedUrlSetter::setPageTitle(const string& page_title)
{
	setPageTitle(Utility::convertUTF8ToUnicode(page_title));
}

void AttachedUrlSetter::setPageTitle(const wstring& page_title)
{
	page_title_(attached_url_) = page_title;
}

void AttachedUrlSetter::setPageDescription(const string& page_description)
{
	setPageDescription(Utility::convertUTF8ToUnicode(page_description));
}

void AttachedUrlSetter::setPageDescription(const wstring& page_description)
{
	page_description_(attached_url_) = page_description;
}

void AttachedUrlSetter::setPageFaviconUrl(const string& page_favicon_url)
{
	setPageFaviconUrl(Utility::convertUTF8ToUnicode(page_favicon_url));
}

void AttachedUrlSetter::setPageFaviconUrl(const wstring& page_favicon_url)
{
	page_favicon_url_(attached_url_) = page_favicon_url;
}

string AttachedUrlSetter::getPageUrl()
{
	return Utility::convertUnicodeToUTF8(page_url_(attached_url_));
}

void AttachedUrlSetter::setPageUrl(const string& page_url)
{
	setPageUrl(Utility::convertUTF8ToUnicode(page_url));
}

void AttachedUrlSetter::setPageUrl(const wstring& page_url)
{
	page_url_(attached_url_) = page_url;
}

void AttachedUrlSetter::setThumbnailUrl(const string& thumbnail_url)
{
	setThumbnailUrl(Utility::convertUTF8ToUnicode(thumbnail_url));
}

void AttachedUrlSetter::setThumbnailUrl(const wstring& thumbnail_url)
{
	thumbnail_url_(attached_url_) = thumbnail_url;
}

void AttachedUrlSetter::setThumbnailPosition(int thumbnail_position)
{
	thumbnail_position_(attached_url_) = thumbnail_position;
}

AttachedUrl AttachedUrlSetter::toAttachedUrl()
{
	return attached_url_;
}

void AttachedUrlSetter::bindToScript(lua_State* lua_state)
{
	module(lua_state)
		[
			class_<AttachedUrlSetter>("AttachedUrlSetter")
			.def(constructor<>())
			.scope
				[
					def("parse", static_cast<AttachedUrlSetter(*)(JsonObject&)>(&AttachedUrlSetter::parse))
				]
			.scope
				[
					def("parse", static_cast<AttachedUrlSetter(*)(luabind::object)>(&AttachedUrlSetter::parse))
				]
			.def("setPageTitle", static_cast<void(AttachedUrlSetter::*)(const string&)>(&AttachedUrlSetter::setPageTitle))
			.def("setPageDescription", static_cast<void(AttachedUrlSetter::*)(const string&)>(&AttachedUrlSetter::setPageDescription))
			.def("setPageFaviconUrl", static_cast<void(AttachedUrlSetter::*)(const string&)>(&AttachedUrlSetter::setPageFaviconUrl))
			.def("getPageUrl", &AttachedUrlSetter::getPageUrl)
			.def("setPageUrl", static_cast<void(AttachedUrlSetter::*)(const string&)>(&AttachedUrlSetter::setPageUrl))
			.def("setThumbnailUrl", static_cast<void(AttachedUrlSetter::*)(const string&)>(&AttachedUrlSetter::setThumbnailUrl))
			.def("setThumbnailPosition", &AttachedUrlSetter::setThumbnailPosition)
		];
}

AttachedUrlSetter::~AttachedUrlSetter()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite