#include <AttachedInfo/AttachedAlbum/AttachedAlbumSetter.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

AttachedAlbumSetter::AttachedAlbumSetter()
{
}

void AttachedAlbumSetter::setAlbumName(const wstring& album_name)
{
	album_name_(attached_album_) = album_name;
}

AttachedAlbum AttachedAlbumSetter::toAttachedAlbum()
{
	return attached_album_;
}

AttachedAlbumSetter::~AttachedAlbumSetter()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite