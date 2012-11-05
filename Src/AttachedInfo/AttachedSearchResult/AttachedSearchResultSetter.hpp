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

#include <AttachedInfo/AttachedSearchResult/AttachedSearchResultBase.hpp>

#include <luabind/luabind.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API AttachedSearchResultSetter : public AttachedSearchResultBase
{
public:
	AttachedSearchResultSetter();

	static AttachedSearchResultSetter parse(JsonObject& json);
	static AttachedSearchResultSetter parse(luabind::object json);

	std::string getSearchKeyword();
	void setSearchKeyword(const std::string& search_keyword);
	void setSearchKeyword(const std::wstring& search_keyword);

	void setSearchResultPageUrl(const std::string& search_result_page_url);
	void setSearchResultPageUrl(const std::wstring& search_result_page_url);
	
	AttachedSearchResult toAttachedSearchResult();

	static void bindToScript(lua_State* lua_state);

	virtual ~AttachedSearchResultSetter();
private:
	AttachedSearchResult attached_search_result_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite