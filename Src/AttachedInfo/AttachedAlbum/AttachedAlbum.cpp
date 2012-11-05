#include <AttachedInfo/AttachedAlbum/AttachedAlbum.hpp>
#include <Thread/ReadWriteMutex.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

AttachedAlbum::AttachedAlbum()
:album_name_(L""),
read_write_mutex_(make_shared<ReadWriteMutex>())
{
}

AttachedAlbum::AttachedAlbum(wstring album_name)
:album_name_(album_name),
read_write_mutex_(make_shared<ReadWriteMutex>())
{
}

wstring AttachedAlbum::getAlbumName() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return album_name_;
}

void AttachedAlbum::addFile(const wstring& file_path)
{
	file_list_.push_back(file_path);
}

void AttachedAlbum::removeFile(const wstring& file_name)
{
	//! @todo ‚¿‚á‚ñ‚Æƒtƒ@ƒCƒ‹‚ğíœ‚Å‚«‚é‚æ‚¤‚É‚·‚é
	file_list_.remove(file_name);
}

void AttachedAlbum::upload(const wstring& account_id)
{

}


AttachedAlbum::~AttachedAlbum()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite