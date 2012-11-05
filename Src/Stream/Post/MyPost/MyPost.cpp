#include <Stream/Post/MyPost/MyPost.hpp>
#include <Stream/Post/PostSetter.hpp>
#include <Share/ShareRangeList.hpp>
#include <AttachedInfo/AttachedAlbum/AttachedAlbum.hpp>
#include <AttachedInfo/AttachedCircle/AttachedCircle.hpp>
#include <AttachedInfo/AttachedImageVideo/AttachedImageVideo.hpp>
#include <AttachedInfo/AttachedLocation/AttachedLocation.hpp>
#include <AttachedInfo/AttachedSearchResult/AttachedSearchResult.hpp>
#include <AttachedInfo/AttachedUrl/AttachedUrl.hpp>
#include <AttachedInfo/AttachedYouTubePlaylist/AttachedYouTubePlaylist.hpp>
#include <Thread/ReadWriteMutex.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

MyPost::MyPost()
:post_setter_(make_shared<PostSetter>()),
read_write_mutex_(make_shared<ReadWriteMutex>())
{
}
/*
void MyPost::create(const wstring& message, const ShareRangeList& share_range)
{

}

void MyPost::create(const wstring& message, const ShareRangeList& share_range, const AttachedAlbum& attached_album)
{

}

void MyPost::create(const wstring& message, const ShareRangeList& share_range, const AttachedCircle& attached_circle)
{

}

void MyPost::create(const wstring& message, const ShareRangeList& share_range, const AttachedImageVideo& attached_image_video)
{

}

void MyPost::create(const wstring& message, const ShareRangeList& share_range, const AttachedLocation& attached_location)
{

}

void MyPost::create(const wstring& message, const ShareRangeList& share_range, const AttachedUrl& attached_url)
{

}

void MyPost::create(const wstring& message, const ShareRangeList& share_range, const AttachedYouTubePlaylist& attached_youtube_playlist)
{

}
*/

wstring MyPost::getPostType() const
{
	return post_setter_->getPostType();
}

wstring MyPost::getAuthorName() const
{
	return post_setter_->getAuthorName();
}

wstring MyPost::getAccountID() const
{
	return post_setter_->getAccountID();
}

wstring MyPost::getAccountImageUrl() const
{
	return post_setter_->getAccountImageUrl();
}

bool MyPost::isResharedPost() const
{
	return post_setter_->isResharedPost();
}

shared_ptr<AttachedAlbum> MyPost::getAttachedAlbum() const
{
	return post_setter_->getAttachedAlbum();
}

shared_ptr<AttachedCircle> MyPost::getAttachedCircle() const
{
	return post_setter_->getAttachedCircle();
}

shared_ptr<AttachedImageVideo> MyPost::getAttachedImageVideo() const
{
	return post_setter_->getAttachedImageVideo();
}

shared_ptr<AttachedLocation> MyPost::getAttachedLocation() const
{
	return post_setter_->getAttachedLocation();
}

shared_ptr<AttachedSearchResult> MyPost::getAttachedSearchResult() const
{
	return post_setter_->getAttachedSearchResult();
}

shared_ptr<AttachedUrl> MyPost::getAttachedUrl() const
{
	return post_setter_->getAttachedUrl();
}

shared_ptr<AttachedYouTubePlaylist> MyPost::getAttachedYouTubePlaylist() const
{
	return post_setter_->getAttachedYouTubePlaylist();
}

wstring MyPost::getOriginalPostID() const
{
	return post_setter_->getOriginalPostID();
}

wstring MyPost::getOriginalPostMessage() const
{
	return post_setter_->getOriginalPostMessage();
}

wstring MyPost::getOriginalPostUrl() const
{
	return post_setter_->getOriginalPostUrl();
}

wstring MyPost::getPostID() const
{
	return post_setter_->getPostID();
}

wstring MyPost::getPostUrl() const
{
	return post_setter_->getPostUrl();
}

wstring MyPost::getPlusOneID() const
{
	return post_setter_->getPlusOneID();
}

boost::posix_time::ptime MyPost::getPostTime() const
{
	return post_setter_->getPostTime();
}

bool MyPost::isPublicPost() const
{
	return post_setter_->isPublicPost();
}

wstring MyPost::getMessage() const
{
	return post_setter_->getMessage();
}

void MyPost::editMessage(const wstring& message)
{
	post_setter_->setMessage(message);
}

bool MyPost::isMobilePost() const
{
	return post_setter_->isMobilePost();
}

bool MyPost::isCommentDisabled() const
{
	return post_setter_->isCommentDisabled();
}

void MyPost::disableComment(bool is_disable)
{
	post_setter_->setIsCommentDisabled(is_disable);
}

bool MyPost::isLockdPost() const
{
	return post_setter_->isLockdPost();
}

void MyPost::lockPost(bool is_lock)
{
	post_setter_->setIsLockdPost(is_lock);
}

bool MyPost::isEdited() const
{
	return post_setter_->isEdited();
}

boost::posix_time::ptime MyPost::getLastEditedTime() const
{
	return post_setter_->getLastEditedTime();
}

void MyPost::reshare(const wstring& my_account_id, const wstring& message, const ShareRangeList& share_range)
{
	return post_setter_->reshare(my_account_id, message, share_range);
}
/*
Post MyPost::toPost()
{
	ScopedReadLock lock(*read_write_mutex_);
	return (post_setter_->toPost());
}
*/
MyPost::~MyPost()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
