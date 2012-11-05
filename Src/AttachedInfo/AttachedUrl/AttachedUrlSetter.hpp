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

#include <AttachedInfo/AttachedUrl/AttachedUrlBase.hpp>

#include <luabind/luabind.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API AttachedUrlSetter : public AttachedUrlBase
{
public:
	AttachedUrlSetter();

	static AttachedUrlSetter parse(JsonObject& json);
	static AttachedUrlSetter parse(luabind::object json);

	void setPageTitle(const std::string& page_title);
	void setPageTitle(const std::wstring& page_title);
	void setPageDescription(const std::string& page_description);
	void setPageDescription(const std::wstring& page_description);
	void setPageFaviconUrl(const std::string& page_favicon_url);
	void setPageFaviconUrl(const std::wstring& page_favicon_url);
	
	std::string getPageUrl();
	void setPageUrl(const std::string& page_url);
	void setPageUrl(const std::wstring& page_url);
	void setThumbnailUrl(const std::string& thumbnail_url);
	void setThumbnailUrl(const std::wstring& thumbnail_url);
	void setThumbnailPosition(int thumbnail_position);

	AttachedUrl toAttachedUrl();

	static void bindToScript(lua_State* lua_state);

	virtual ~AttachedUrlSetter();
private:
	AttachedUrl attached_url_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite