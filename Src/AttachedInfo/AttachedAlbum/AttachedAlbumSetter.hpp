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

#include <AttachedInfo/AttachedAlbum/AttachedAlbumBase.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API AttachedAlbumSetter : public AttachedAlbumBase
{
public:
	AttachedAlbumSetter();

	void setAlbumName(const std::wstring& album_name);

	AttachedAlbum toAttachedAlbum();

	virtual ~AttachedAlbumSetter();
private:
	AttachedAlbum attached_album_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite