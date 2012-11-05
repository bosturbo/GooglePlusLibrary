#include <Stream/Post/Post.hpp>
#include <Stream/Post/PostImpl.hpp>
#include <AttachedInfo/AttachedAlbum/AttachedAlbum.hpp>
#include <AttachedInfo/AttachedCircle/AttachedCircle.hpp>
#include <AttachedInfo/AttachedImageVideo/AttachedImageVideo.hpp>
#include <AttachedInfo/AttachedLocation/AttachedLocation.hpp>
#include <AttachedInfo/AttachedSearchResult/AttachedSearchResult.hpp>
#include <AttachedInfo/AttachedUrl/AttachedUrl.hpp>
#include <AttachedInfo/AttachedYouTubePlaylist/AttachedYouTubePlaylist.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

shared_ptr<AttachedAlbum> Post::getAttachedAlbum() const
{
	return impl_->getAttachedAlbum();
}

shared_ptr<AttachedCircle> Post::getAttachedCircle() const
{
	return impl_->getAttachedCircle();
}

shared_ptr<AttachedImageVideo> Post::getAttachedImageVideo() const
{
	return impl_->getAttachedImageVideo();
}

shared_ptr<AttachedLocation> Post::getAttachedLocation() const
{
	return impl_->getAttachedLocation();
}

shared_ptr<AttachedSearchResult> Post::getAttachedSearchResult() const
{
	return impl_->getAttachedSearchResult();
}

shared_ptr<AttachedUrl> Post::getAttachedUrl() const
{
	return impl_->getAttachedUrl();
}

shared_ptr<AttachedYouTubePlaylist> Post::getAttachedYouTubePlaylist() const
{
	return impl_->getAttachedYouTubePlaylist();
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
