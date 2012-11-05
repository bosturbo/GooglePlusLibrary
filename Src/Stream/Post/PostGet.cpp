#include <Stream/Post/Post.hpp>
#include <Share/ShareRangeList.hpp>
#include <AttachedInfo/AttachedAlbum/AttachedAlbum.hpp>
#include <AttachedInfo/AttachedCircle/AttachedCircle.hpp>
#include <AttachedInfo/AttachedImageVideo/AttachedImageVideo.hpp>
#include <AttachedInfo/AttachedLocation/AttachedLocation.hpp>
#include <AttachedInfo/AttachedSearchResult/AttachedSearchResult.hpp>
#include <AttachedInfo/AttachedUrl/AttachedUrl.hpp>
#include <AttachedInfo/AttachedYouTubePlaylist/AttachedYouTubePlaylist.hpp>
#include <Stream/Comment/CommentList/CommentList.hpp>
#include <Stream/Post/PostImpl.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

Post::Post()
:impl_(new PostImpl())
{
}

wstring Post::getPostType() const
{
	return impl_->getPostType();
}

wstring Post::getAuthorName() const
{
	return impl_->getAuthorName();
}

wstring Post::getAccountID() const
{
	return impl_->getAccountID();
}

wstring Post::getAccountImageUrl() const
{
	return impl_->getAccountImageUrl();
}

bool Post::isResharedPost() const
{
	return impl_->isResharedPost();
}

const AttachedAlbum* Post::getAttachedAlbum() const
{
	return impl_->getAttachedAlbum();
}

const AttachedCircle* Post::getAttachedCircle() const
{
	return impl_->getAttachedCircle();
}

const AttachedImageVideo* Post::getAttachedImageVideo() const
{
	return impl_->getAttachedImageVideo();
}

const AttachedLocation* Post::getAttachedLocation() const
{
	return impl_->getAttachedLocation();
}

const AttachedSearchResult* Post::getAttachedSearchResult() const
{
	return impl_->getAttachedSearchResult();
}

const AttachedUrl* Post::getAttachedUrl() const
{
	return impl_->getAttachedUrl();
}

const AttachedYouTubePlaylist* Post::getAttachedYouTubePlaylist() const
{
	return impl_->getAttachedYouTubePlaylist();
}

wstring Post::getOriginalPostID() const
{
	return impl_->getOriginalPostID();
}

wstring Post::getOriginalPostMessage() const
{
	return impl_->getOriginalpostMessage();
}

wstring Post::getOriginalPostUrl() const
{
	return impl_->getOriginalPostUrl();
}

wstring Post::getPostID() const
{
	return impl_->getPostID();
}

wstring Post::getPostUrl() const
{
	return impl_->getPostUrl();
}

wstring Post::getPlusOneID() const
{
	return impl_->getPlusOneID();
}

boost::posix_time::ptime Post::getPostTime() const
{
	return impl_->getPostTime();
}

bool Post::isPublicPost() const
{
	return impl_->isPublicPost();
}

wstring Post::getMessage() const
{
	return impl_->getMessage();
}

bool Post::isMobilePost() const
{
	return impl_->isMobilePost();
}

bool Post::isCommentDisabled() const
{
	return impl_->isCommentDisabled();
}

bool Post::isLockdPost() const
{
	return impl_->isLockdPost();
}

bool Post::isMyPost() const
{
	return impl_->isMyPost();
}

bool Post::isEdited() const
{
	return impl_->isEdited();
}

boost::posix_time::ptime Post::getLastEditedTime() const
{
	return impl_->getLastEditedTime();
}

void Post::mutePost(bool is_mute)
{
	impl_->mutePost(is_mute);
}

void Post::reshare(const wstring& my_account_id, const wstring& message, const ShareRangeList& share_range)
{
	impl_->reshare(my_account_id, message, share_range);
}

CommentList* Post::getCommentList() const
{
	return impl_->getCommentList();
}

Post::~Post()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
