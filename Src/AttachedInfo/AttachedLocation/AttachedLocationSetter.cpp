#include <AttachedInfo/AttachedLocation/AttachedLocationSetter.hpp>

#include <Utility/Utility.hpp>
#include <Utility/LuaScript.hpp>

#include <Json/JsonObject.hpp>

#include <boost/lexical_cast.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

AttachedLocationSetter::AttachedLocationSetter()
{
}


AttachedLocationSetter AttachedLocationSetter::parse(JsonObject& json)
{
	LuaScript<AttachedLocationSetter(JsonObject*)> lua_script("LuaScript/ParseAttachedLocation.lua", "parseAttachedLocation", [](lua_State* lua_state)
	{
		Utility::bindToScript(lua_state);
		JsonObject::bindToScript(lua_state);
		bindToScript(lua_state);
	});

	return lua_script(&json);
}

AttachedLocationSetter AttachedLocationSetter::parse(luabind::object json)
{
	if (luabind::type(json) != LUA_TLIGHTUSERDATA)
	{
		return AttachedLocationSetter();
	}
	JsonObject* node_pointer = static_cast<JsonObject*>(lua_touserdata(json.interpreter(),1));
	return parse(*node_pointer);
}

void AttachedLocationSetter::setLatitude(double latitude)
{
	latitude_(attached_location_) = latitude;
}

void AttachedLocationSetter::setLatitude(const string& latitude)
{
	try
	{
		setLatitude(boost::lexical_cast<double>(latitude));
	}
	catch (boost::bad_lexical_cast)
	{
		setLatitude(-1);
	}
}

void AttachedLocationSetter::setLatitude(const wstring& latitude)
{
	try
	{
		setLatitude(boost::lexical_cast<double>(latitude));
	}
	catch (boost::bad_lexical_cast)
	{
		setLatitude(-1);
	}
}

void AttachedLocationSetter::setLongitude(double longitude)
{
	longitude_(attached_location_) = longitude;
}

void AttachedLocationSetter::setLongitude(const string& longitude)
{
	try
	{
		setLongitude(boost::lexical_cast<double>(longitude));
	}
	catch (boost::bad_lexical_cast)
	{
		setLongitude(-1);
	}
}

void AttachedLocationSetter::setLongitude(const wstring& longitude)
{
	try
	{
		setLongitude(boost::lexical_cast<double>(longitude));
	}
	catch (boost::bad_lexical_cast)
	{
		setLongitude(-1);
	}
}

void AttachedLocationSetter::setLocationName(const string& location_name)
{
	setLocationName(Utility::convertUTF8ToUnicode(location_name));
}

void AttachedLocationSetter::setLocationName(const wstring& location_name)
{
	location_name_(attached_location_) = location_name;
}

void AttachedLocationSetter::setAddress(const string& address)
{
	setAddress(Utility::convertUTF8ToUnicode(address));
}

void AttachedLocationSetter::setAddress(const wstring& address)
{
	address_(attached_location_) = address;
}

string AttachedLocationSetter::getGoogleMapPageImageUrl()
{
	return Utility::convertUnicodeToUTF8(google_map_page_image_url_(attached_location_));
}

void AttachedLocationSetter::setGoogleMapPageImageUrl(const string& google_map_page_image_url)
{
	setGoogleMapPageImageUrl(Utility::convertUTF8ToUnicode(google_map_page_image_url));
}

void AttachedLocationSetter::setGoogleMapPageImageUrl(const wstring& google_map_page_image_url)
{
	google_map_page_image_url_(attached_location_) = google_map_page_image_url;
}

void AttachedLocationSetter::setIsCheckined(bool is_checkined)
{
	is_checkined_(attached_location_) = is_checkined;
}

AttachedLocation AttachedLocationSetter::toAttachedLocation()
{
	return attached_location_;
}

void AttachedLocationSetter::bindToScript(lua_State* lua_state)
{
	module(lua_state)
		[
			class_<AttachedLocationSetter>("AttachedLocationSetter")
			.def(constructor<>())
			.scope
				[
					def("parse", static_cast<AttachedLocationSetter(*)(JsonObject&)>(&AttachedLocationSetter::parse))
				]
			.scope
				[
					def("parse", static_cast<AttachedLocationSetter(*)(luabind::object)>(&AttachedLocationSetter::parse))
				]

			.def("setLatitude", static_cast<void(AttachedLocationSetter::*)(double)>(&AttachedLocationSetter::setLatitude))
			.def("setLatitude", static_cast<void(AttachedLocationSetter::*)(const string&)>(&AttachedLocationSetter::setLatitude))
			.def("setLongitude", static_cast<void(AttachedLocationSetter::*)(double)>(&AttachedLocationSetter::setLongitude))
			.def("setLongitude", static_cast<void(AttachedLocationSetter::*)(const string&)>(&AttachedLocationSetter::setLongitude))
			.def("setLocationName", static_cast<void(AttachedLocationSetter::*)(const string&)>(&AttachedLocationSetter::setLocationName))
			.def("setAddress", static_cast<void(AttachedLocationSetter::*)(const string&)>(&AttachedLocationSetter::setAddress))
			.def("getGoogleMapPageImageUrl", &AttachedLocationSetter::getGoogleMapPageImageUrl)
			.def("setGoogleMapPageImageUrl", static_cast<void(AttachedLocationSetter::*)(const string&)>(&AttachedLocationSetter::setGoogleMapPageImageUrl))
			.def("setIsCheckined", &AttachedLocationSetter::setIsCheckined)
		];
}

AttachedLocationSetter::~AttachedLocationSetter()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite