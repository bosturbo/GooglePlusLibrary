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

#include <AttachedInfo/AttachedAlbum/AttachedAlbum.hpp>
#include <Thread/ReadWriteMutex.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API AttachedAlbumBase
{
public:
	AttachedAlbumBase()
	{
	}

protected:

	static std::wstring& album_name_(AttachedAlbum& attached_album)
	{
		return attached_album.album_name_;
	}

	static std::list<std::wstring>& file_list_(AttachedAlbum& attached_album)
	{
		return attached_album.file_list_;
	}

	static std::shared_ptr<ReadWriteMutex>& read_write_mutex_(AttachedAlbum& attached_album)
	{
		return attached_album.read_write_mutex_;
	}

public:
	virtual ~AttachedAlbumBase()
	{
	}
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite