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

#ifdef GOOGLEPLUSLIBRARY_NO_WARNINGS
#ifdef _MSC_VER
#pragma warning (disable:4251)
#pragma warning (disable:4996)
#endif
#endif

#include <memory>
#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class JsonObject;
class ReadWriteMutex;

class GOOGLEPLUSLIBRARY_API AttachedSearchResult
{
	friend class PostParser;
	friend class AttachedSearchResultBase;
public:
	AttachedSearchResult();
	
public:
	std::wstring getSearchKeyword() const;
private:
	std::wstring search_keyword_;

public:
	std::wstring getSearchResultPageUrl() const;
private:
	std::wstring search_result_page_url_;

public:
	virtual ~AttachedSearchResult();

private:
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite