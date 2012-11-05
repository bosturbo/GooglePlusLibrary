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

#include <AttachedInfo/AttachedSearchResult/AttachedSearchResult.hpp>
#include <Thread/ReadWriteMutex.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API AttachedSearchResultBase
{
public:
	AttachedSearchResultBase()
	{
	}

protected:
	static std::wstring& search_keyword_(AttachedSearchResult& attached_search_result)
	{
		return attached_search_result.search_keyword_;
	}

	static std::wstring& search_result_page_url_(AttachedSearchResult& attached_search_result)
	{
		return attached_search_result.search_result_page_url_;
	}

	static std::shared_ptr<ReadWriteMutex>& read_write_mutex_(AttachedSearchResult& attached_search_result)
	{
		return attached_search_result.read_write_mutex_;
	}

public:
	virtual ~AttachedSearchResultBase()
	{
	}
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite