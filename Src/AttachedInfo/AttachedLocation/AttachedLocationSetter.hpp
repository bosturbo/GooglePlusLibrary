#pragma once

#ifdef _MSC_VER
#ifdef GOOGLEPLUSLIBRARY_EXPORTS
#define GOOGLEPLUSLIBRARY_API __declspec(dllexport)
#else
#define GOOGLEPLUSLIBRARY_API __declspec(dllimport)
#endif
#else
#define GOOGLEPLUSLIBRARY_API
#endif

#include <AttachedInfo/AttachedLocation/AttachedLocationBase.hpp>

#include <luabind/luabind.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API AttachedLocationSetter : public AttachedLocationBase
{
public:
	AttachedLocationSetter();

	static AttachedLocationSetter parse(JsonObject& json);
	static AttachedLocationSetter parse(luabind::object json);

	void setLatitude(double latitude);
	void setLatitude(const std::string& latitude);
	void setLatitude(const std::wstring& latitude);

	void setLongitude(double longitude);
	void setLongitude(const std::string& longitude);
	void setLongitude(const std::wstring& longitude);

	void setLocationName(const std::string& location_name);
	void setLocationName(const std::wstring& location_name);

	void setAddress(const std::string& address);
	void setAddress(const std::wstring& address);

	std::string getGoogleMapPageImageUrl();
	void setGoogleMapPageImageUrl(const std::string& google_map_page_image_url);
	void setGoogleMapPageImageUrl(const std::wstring& google_map_page_image_url);

	void setIsCheckined(bool is_checkined);

	AttachedLocation toAttachedLocation();

	static void bindToScript(lua_State* lua_state);

	virtual ~AttachedLocationSetter();

private:
	AttachedLocation attached_location_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite