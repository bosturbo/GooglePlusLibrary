#include <AttachedInfo/AttachedImageVideo/AttachedImageVideo.hpp>
#include <AttachedInfo/AttachedAlbum/AttachedAlbum.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

AttachedImageVideo::AttachedImageVideo()
	:attached_album_(make_shared<AttachedAlbum>())
{
}

void AttachedImageVideo::addFile(const wstring& file_path)
{
	attached_album_->addFile(file_path);
}

void AttachedImageVideo::removeFile(const wstring& file_name)
{
	attached_album_->removeFile(file_name);
}

void AttachedImageVideo::upload(const wstring& account_id)
{
	attached_album_->upload(account_id);
}

AttachedImageVideo::~AttachedImageVideo()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite