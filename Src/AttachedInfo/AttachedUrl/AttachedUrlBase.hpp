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

#include <AttachedInfo/AttachedUrl/AttachedUrl.hpp>
#include <Thread/ReadWriteMutex.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API AttachedUrlBase
{
public:
	AttachedUrlBase()
	{
	}

protected:
	static std::wstring& page_title_(AttachedUrl& attached_url)
	{
		return attached_url.page_title_;
	}
	static std::wstring& page_description_(AttachedUrl& attached_url)
	{
		return attached_url.page_description_;
	}

	static std::wstring& page_favicon_url_(AttachedUrl& attached_url)
	{
		return attached_url.page_favicon_url_;
	}

	static std::wstring& page_url_(AttachedUrl& attached_url)
	{
		return attached_url.page_url_;
	}

	static std::wstring& thumbnail_url_(AttachedUrl& attached_url)
	{
		return attached_url.thumbnail_url_;
	}

	static int& thumbnail_position_(AttachedUrl& attached_url)
	{
		return attached_url.thumbnail_position_;
	}

	static std::shared_ptr<ReadWriteMutex>& read_write_mutex_(AttachedUrl& attached_url)
	{
		return attached_url.read_write_mutex_;
	}

public:
	virtual ~AttachedUrlBase()
	{
	}
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite