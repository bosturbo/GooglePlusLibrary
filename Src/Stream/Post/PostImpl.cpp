#include <Stream/Post/PostImpl.hpp>
#include <Share/ShareRangeList.hpp>
#include <AttachedInfo/AttachedAlbum/AttachedAlbumSetter.hpp>
#include <AttachedInfo/AttachedCircle/AttachedCircleSetter.hpp>
#include <AttachedInfo/AttachedImageVideo/AttachedImageVideoSetter.hpp>
#include <AttachedInfo/AttachedLocation/AttachedLocationSetter.hpp>
#include <AttachedInfo/AttachedSearchResult/AttachedSearchResultSetter.hpp>
#include <AttachedInfo/AttachedUrl/AttachedUrlSetter.hpp>
#include <AttachedInfo/AttachedYouTubePlaylist/AttachedYouTubePlaylistSetter.hpp>
#include <Stream/Comment/CommentList/CommentList.hpp>

#include <luabind/luabind.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

PostImpl::PostImpl()
:post_type_(L""),
author_name_(L""),
account_id_(L""),
account_image_url_(L""),
is_shared_post_(L""),
attached_album_(make_shared<AttachedAlbum>()),
attached_circle_(make_shared<AttachedCircle>()),
attached_image_video_(make_shared<AttachedImageVideo>()),
attached_location_(make_shared<AttachedLocation>()),
attached_search_result_(make_shared<AttachedSearchResult>()),
attached_url_(make_shared<AttachedUrl>()),
attached_youtube_play_list_(make_shared<AttachedYouTubePlaylist>()),
original_post_id_(L""),
original_post_message_(L""),
original_post_url_(L""),
post_id_(L""),
post_url_(L""),
plus_one_id_(L""),
post_time_(),
is_public_post_(false),
message_(L""),
is_mobile_post_(false),
is_comment_disabled_(false),
is_lock_post_(false),
is_my_post_(false),
is_edited_(false),
last_edited_time_(),
comment_list_(make_shared<CommentList>())
{
}

wstring PostImpl::getPostType() const
{
	ScopedReadLock lock(read_write_mutex_);
	return post_type_;
}

void PostImpl::setPostType(const wstring& post_type)
{
	ScopedWriteLock lock(read_write_mutex_);
	post_type_ = post_type;
}

wstring PostImpl::getAuthorName() const
{
	ScopedReadLock lock(read_write_mutex_);
	return author_name_;
}

void PostImpl::setAuthorName(const wstring& author_name)
{
	ScopedWriteLock lock(read_write_mutex_);
	author_name_ = author_name;
}

wstring PostImpl::getAccountID() const
{
	ScopedReadLock lock(read_write_mutex_);
	return account_id_;
}

void PostImpl::setAccountID(const wstring& account_id)
{
	ScopedWriteLock lock(read_write_mutex_);
	account_id_ = account_id;
}

wstring PostImpl::getAccountImageUrl() const
{
	ScopedReadLock lock(read_write_mutex_);
	return account_image_url_;
}

void PostImpl::setAccountImageUrl(const wstring& account_image_url)
{
	ScopedWriteLock lock(read_write_mutex_);
	account_image_url_ = account_image_url;
}

bool PostImpl::isResharedPost() const
{
	ScopedReadLock lock(read_write_mutex_);
	return is_shared_post_;
}

shared_ptr<AttachedAlbum> PostImpl::getAttachedAlbum() const
{
	ScopedReadLock lock(read_write_mutex_);
	return attached_album_;
}

void PostImpl::setAttachedAlbum(const AttachedAlbum& attached_album)
{
	ScopedWriteLock lock(read_write_mutex_);
	attached_album_ = make_shared<AttachedAlbum>(attached_album);
}

void PostImpl::setAttachedAlbum(AttachedAlbumSetter& attached_album_setter)
{
	ScopedWriteLock lock(read_write_mutex_);
	attached_album_ = make_shared<AttachedAlbum>(attached_album_setter.toAttachedAlbum());
}

shared_ptr<AttachedCircle> PostImpl::getAttachedCircle() const
{
	ScopedReadLock lock(read_write_mutex_);
	return attached_circle_;
}

void PostImpl::setAttachedCircle(const AttachedCircle& attached_circle)
{
	ScopedWriteLock lock(read_write_mutex_);
	attached_circle_ = make_shared<AttachedCircle>(attached_circle);
}

void PostImpl::setAttachedCircle(AttachedCircleSetter& attached_circle_setter)
{
	ScopedWriteLock lock(read_write_mutex_);
	attached_circle_ = make_shared<AttachedCircle>(attached_circle_setter.toAttachedCircle());
}

shared_ptr<AttachedImageVideo> PostImpl::getAttachedImageVideo() const
{
	ScopedReadLock lock(read_write_mutex_);
	return attached_image_video_;
}

void PostImpl::setAttachedImageVideo(const AttachedImageVideo& attached_image_video)
{
	ScopedWriteLock lock(read_write_mutex_);
	attached_image_video_ = make_shared<AttachedImageVideo>(attached_image_video);
}

void PostImpl::setAttachedImageVideo(AttachedImageVideoSetter& attached_image_video_setter)
{
	ScopedWriteLock lock(read_write_mutex_);
	attached_image_video_ = make_shared<AttachedImageVideo>(attached_image_video_setter.toAttachedImageVideo());
}

shared_ptr<AttachedLocation> PostImpl::getAttachedLocation() const
{
	ScopedReadLock lock(read_write_mutex_);
	return attached_location_;
}

void PostImpl::setAttachedLocation(const AttachedLocation& attached_location)
{
	ScopedWriteLock lock(read_write_mutex_);
	attached_location_ = make_shared<AttachedLocation>(attached_location);
}

void PostImpl::setAttachedLocation(AttachedLocationSetter& attached_location_setter)
{
	ScopedWriteLock lock(read_write_mutex_);
	attached_location_ = make_shared<AttachedLocation>(attached_location_setter.toAttachedLocation());
}

shared_ptr<AttachedSearchResult> PostImpl::getAttachedSearchResult() const
{
	ScopedReadLock lock(read_write_mutex_);
	return attached_search_result_;
}

void PostImpl::setAttachedSearchResult(const AttachedSearchResult& attached_search_result)
{
	ScopedWriteLock lock(read_write_mutex_);
	attached_search_result_ = make_shared<AttachedSearchResult>(attached_search_result);
}

void PostImpl::setAttachedSearchResult(AttachedSearchResultSetter& attached_search_result_setter)
{
	ScopedWriteLock lock(read_write_mutex_);
	attached_search_result_ = make_shared<AttachedSearchResult>(attached_search_result_setter.toAttachedSearchResult());
}

shared_ptr<AttachedUrl> PostImpl::getAttachedUrl() const
{
	ScopedReadLock lock(read_write_mutex_);
	return attached_url_;
}

void PostImpl::setAttachedUrl(const AttachedUrl& attached_url)
{
	ScopedWriteLock lock(read_write_mutex_);
	attached_url_ = make_shared<AttachedUrl>(attached_url);
}

void PostImpl::setAttachedUrl(AttachedUrlSetter& attached_url_setter)
{
	ScopedWriteLock lock(read_write_mutex_);
	attached_url_ = make_shared<AttachedUrl>(attached_url_setter.toAttachedUrl());
}

shared_ptr<AttachedYouTubePlaylist> PostImpl::getAttachedYouTubePlaylist() const
{
	ScopedReadLock lock(read_write_mutex_);
	return attached_youtube_play_list_;
}

void PostImpl::setAttachedYouTubePlaylist(const AttachedYouTubePlaylist& attached_youtube_play_list)
{
	ScopedWriteLock lock(read_write_mutex_);
	attached_youtube_play_list_ = make_shared<AttachedYouTubePlaylist>(attached_youtube_play_list);
}

void PostImpl::setAttachedYouTubePlaylist(AttachedYouTubePlaylistSetter& attached_youtube_play_list_setter)
{
	ScopedWriteLock lock(read_write_mutex_);
	attached_youtube_play_list_ = make_shared<AttachedYouTubePlaylist>(attached_youtube_play_list_setter.toAttachedYouTubePlaylist());
}

void PostImpl::setIsResharedPost(bool is_shared_post)
{
	ScopedWriteLock lock(read_write_mutex_);
	is_shared_post_ = is_shared_post;
}

wstring PostImpl::getOriginalPostID() const
{
	ScopedReadLock lock(read_write_mutex_);
	return original_post_id_;
}

void PostImpl::setOriginalPostID(const wstring& original_post_id)
{
	ScopedWriteLock lock(read_write_mutex_);
	original_post_id_ = original_post_id;
}

wstring PostImpl::getOriginalpostMessage() const
{
	ScopedReadLock lock(read_write_mutex_);
	return original_post_message_;
}

void PostImpl::setOriginalpostMessage(const wstring& original_post_message)
{
	ScopedWriteLock lock(read_write_mutex_);
	original_post_message_ = original_post_message;
}

wstring PostImpl::getOriginalPostUrl() const
{
	ScopedReadLock lock(read_write_mutex_);
	return original_post_url_;
}

void PostImpl::setOriginalPostUrl(const wstring& original_post_url)
{
	ScopedWriteLock lock(read_write_mutex_);
	original_post_url_ = original_post_url;
}

wstring PostImpl::getPostID() const
{
	//ScopedReadLock lock(read_write_mutex_);
	return post_id_;
}

void PostImpl::setPostID(const wstring& post_id)
{
	ScopedWriteLock lock(read_write_mutex_);
	post_id_ = post_id;

	comment_list_->setTargetPostID(post_id);
}

wstring PostImpl::getPostUrl() const
{
	ScopedReadLock lock(read_write_mutex_);
	return post_url_;
}

void PostImpl::setPostUrl(const wstring& post_url)
{
	ScopedWriteLock lock(read_write_mutex_);
	post_url_ = post_url;
}

wstring PostImpl::getPlusOneID() const
{
	ScopedReadLock lock(read_write_mutex_);
	return plus_one_id_;
}

void PostImpl::setPlusOneID(const wstring& plus_one_id)
{
	ScopedWriteLock lock(read_write_mutex_);
	plus_one_id_ = plus_one_id;
}

boost::posix_time::ptime PostImpl::getPostTime() const
{
	ScopedReadLock lock(read_write_mutex_);
	return post_time_;
}

void PostImpl::setPostTime(const boost::posix_time::ptime& post_time)
{
	ScopedWriteLock lock(read_write_mutex_);
	post_time_ = post_time;
}

bool PostImpl::isPublicPost() const
{
	ScopedReadLock lock(read_write_mutex_);
	return is_public_post_;
}

void PostImpl::setIsPublicPost(bool is_public_post)
{
	ScopedWriteLock lock(read_write_mutex_);
	is_public_post_ = is_public_post;
}

wstring PostImpl::getMessage() const
{
	ScopedReadLock lock(read_write_mutex_);
	return message_;
}

void PostImpl::setMessage(const wstring& message)
{
	ScopedWriteLock lock(read_write_mutex_);
	message_ = message;
}

bool PostImpl::isMobilePost() const
{
	ScopedReadLock lock(read_write_mutex_);
	return is_mobile_post_;
}

void PostImpl::setIsMobilePost(bool is_mobile_post)
{
	ScopedWriteLock lock(read_write_mutex_);
	is_mobile_post_ = is_mobile_post;
}

bool PostImpl::isCommentDisabled() const
{
	ScopedReadLock lock(read_write_mutex_);
	return is_comment_disabled_;
}

void PostImpl::setIsCommentDisabled(bool is_disable_comment)
{
	ScopedWriteLock lock(read_write_mutex_);
	is_comment_disabled_ = is_disable_comment;
}

bool PostImpl::isLockdPost() const
{
	ScopedReadLock lock(read_write_mutex_);
	return is_lock_post_;
}

void PostImpl::setIsLockdPost(bool is_lock_post)
{
	ScopedWriteLock lock(read_write_mutex_);
	is_lock_post_ = is_lock_post;
}

bool PostImpl::isMyPost() const
{
	ScopedReadLock lock(read_write_mutex_);
	return is_my_post_;
}

void PostImpl::setIsMyPost(bool is_my_post)
{
	ScopedWriteLock lock(read_write_mutex_);
	is_my_post_ = is_my_post;
}

bool PostImpl::isEdited() const
{
	ScopedReadLock lock(read_write_mutex_);
	return is_edited_;
}

void PostImpl::setIsEdited(bool is_edited)
{
	ScopedWriteLock lock(read_write_mutex_);
	is_edited_ = is_edited;
}

boost::posix_time::ptime PostImpl::getLastEditedTime() const
{
	ScopedReadLock lock(read_write_mutex_);
	return last_edited_time_;
}

void PostImpl::setLastEditedTime(const boost::posix_time::ptime& last_edited_time)
{
	ScopedWriteLock lock(read_write_mutex_);
	last_edited_time_ = last_edited_time;
}

void PostImpl::mutePost(bool is_mute)
{

}

void PostImpl::reshare(const wstring& my_account_id, const wstring& message, const ShareRangeList& share_range)
{

}

CommentList* PostImpl::getCommentList() const
{
	ScopedReadLock lock(read_write_mutex_);
	return comment_list_.get();
}

PostImpl::~PostImpl()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
