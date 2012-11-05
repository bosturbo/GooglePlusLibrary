#include <Stream/Post/PostSetter.hpp>
#include <Stream/Post/PostImpl.hpp>

#include <Utility/Utility.hpp>

#include <AttachedInfo/AttachedAlbum/AttachedAlbumSetter.hpp>
#include <AttachedInfo/AttachedCircle/AttachedCircleSetter.hpp>
#include <AttachedInfo/AttachedImageVideo/AttachedImageVideoSetter.hpp>
#include <AttachedInfo/AttachedLocation/AttachedLocationSetter.hpp>
#include <AttachedInfo/AttachedSearchResult/AttachedSearchResultSetter.hpp>
#include <AttachedInfo/AttachedUrl/AttachedUrlSetter.hpp>
#include <AttachedInfo/AttachedYouTubePlaylist/AttachedYouTubePlaylistSetter.hpp>

#include <Stream/Comment/CommentList/CommentList.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

void PostSetter::setPostType(const string& post_type)
{
	setPostType(Utility::convertUTF8ToUnicode(post_type));
}

void PostSetter::setPostType(const wstring& post_type)
{
	impl_->setPostType(post_type);
}

void PostSetter::setAuthorName(const string& author_name)
{
	setAuthorName(Utility::convertUTF8ToUnicode(author_name));
}

void PostSetter::setAuthorName(const wstring& author_name)
{
	impl_->setAuthorName(author_name);
}

void PostSetter::setAccountID(const string& account_id)
{
	setAccountID(Utility::convertUTF8ToUnicode(account_id));
}

void PostSetter::setAccountID(const wstring& account_id)
{
	impl_->setAccountID(account_id);
}

void PostSetter::setAccountImageUrl(const string& account_image_url)
{
	setAccountImageUrl(Utility::convertUTF8ToUnicode(account_image_url));
}

void PostSetter::setAccountImageUrl(const wstring& account_image_url)
{
	impl_->setAccountImageUrl(account_image_url);
}

void PostSetter::setIsResharedPost(bool is_shared_post)
{
	impl_->setIsResharedPost(is_shared_post);
}

void PostSetter::setAttachedAlbum(const AttachedAlbum& attached_album)
{
	impl_->setAttachedAlbum(attached_album);
}

void PostSetter::setAttachedAlbum(AttachedAlbumSetter& attached_album_setter)
{
	impl_->setAttachedAlbum(attached_album_setter);
}

void PostSetter::setAttachedCircle(AttachedCircleSetter& attached_circle_setter)
{
	impl_->setAttachedCircle(attached_circle_setter);
}

void PostSetter::setAttachedCircle(const AttachedCircle& attached_circle)
{
	impl_->setAttachedCircle(attached_circle);
}

void PostSetter::setAttachedImageVideo(AttachedImageVideoSetter& attached_image_video_setter)
{
	impl_->setAttachedImageVideo(attached_image_video_setter);
}

void PostSetter::setAttachedImageVideo(const AttachedImageVideo& attached_image_video)
{
	impl_->setAttachedImageVideo(attached_image_video);
}

void PostSetter::setAttachedLocation(AttachedLocationSetter& attached_location_setter)
{
	impl_->setAttachedLocation(attached_location_setter);
}

void PostSetter::setAttachedLocation(const AttachedLocation& attached_location)
{
	impl_->setAttachedLocation(attached_location);
}

void PostSetter::setAttachedSearchResult(AttachedSearchResultSetter& attached_search_result_setter)
{
	impl_->setAttachedSearchResult(attached_search_result_setter);
}

void PostSetter::setAttachedSearchResult(const AttachedSearchResult& attached_search_result)
{
	impl_->setAttachedSearchResult(attached_search_result);
}

void PostSetter::setAttachedUrl(AttachedUrlSetter& attached_url_setter)
{
	impl_->setAttachedUrl(attached_url_setter);
}

void PostSetter::setAttachedUrl(const AttachedUrl& attached_url)
{
	impl_->setAttachedUrl(attached_url);
}

void PostSetter::setAttachedYouTubePlaylist(AttachedYouTubePlaylistSetter& attached_youtube_play_list_setter)
{
	impl_->setAttachedYouTubePlaylist(attached_youtube_play_list_setter);
}

void PostSetter::setAttachedYouTubePlaylist(const AttachedYouTubePlaylist& attached_youtube_play_list)
{
	impl_->setAttachedYouTubePlaylist(attached_youtube_play_list);
}

void PostSetter::setOriginalPostID(const string& original_post_id)
{
	setOriginalPostID(Utility::convertUTF8ToUnicode(original_post_id));
}

void PostSetter::setOriginalPostID(const wstring& original_post_id)
{
	impl_->setOriginalPostID(original_post_id);
}

void PostSetter::setOriginalPostMessage(const string& original_post_message)
{
	setOriginalPostMessage(Utility::convertUTF8ToUnicode(original_post_message));
}

void PostSetter::setOriginalPostMessage(const wstring& original_post_message)
{
	impl_->setOriginalpostMessage(original_post_message);
}

void PostSetter::setOriginalPostUrl(const string& original_post_url)
{
	setOriginalPostUrl(Utility::convertUTF8ToUnicode(original_post_url));
}

void PostSetter::setOriginalPostUrl(const wstring& original_post_url)
{
	impl_->setOriginalPostUrl(original_post_url);
}

void PostSetter::setPostID(const string& post_id)
{
	setPostID(Utility::convertUTF8ToUnicode(post_id));
}

void PostSetter::setPostID(const wstring& post_id)
{
	impl_->setPostID(post_id);
	impl_->getCommentList()->setTargetPostID(post_id);
}

void PostSetter::setPostUrl(const string& post_url)
{
	setPostUrl(Utility::convertUTF8ToUnicode(post_url));
}

void PostSetter::setPostUrl(const wstring& post_url)
{
	impl_->setPostUrl(post_url);
}

void PostSetter::setPlusOneID(const string& plus_one_id)
{
	setPlusOneID(Utility::convertUTF8ToUnicode(plus_one_id));
}

void PostSetter::setPlusOneID(const wstring& plus_one_id)
{
	impl_->setPlusOneID(plus_one_id);
}

void PostSetter::setPostTime(const string& post_unix_time_milliseconds)
{
	setPostTime(Utility::convertUnixTimeFromString(post_unix_time_milliseconds));
}

void PostSetter::setPostTime(const boost::posix_time::ptime& post_time)
{
	impl_->setPostTime(post_time);
}

void PostSetter::setIsPublicPost(bool is_public_post)
{
	impl_->setIsPublicPost(is_public_post);
}

void PostSetter::setMessage(const string& message)
{
	setMessage(Utility::convertUTF8ToUnicode(message));
}

void PostSetter::setMessage(const wstring& message)
{
	impl_->setMessage(message);
}

void PostSetter::setIsMobilePost(bool is_mobile_post)
{
	impl_->setIsMobilePost(is_mobile_post);
}

void PostSetter::setIsCommentDisabled(bool is_comment_disabled)
{
	impl_->setIsCommentDisabled(is_comment_disabled);
}

void PostSetter::setIsLockdPost(bool is_lock_post)
{
	impl_->setIsLockdPost(is_lock_post);
}

void PostSetter::setIsMyPost(bool is_my_post)
{
	impl_->setIsMyPost(is_my_post);
}

void PostSetter::setIsEdited(bool is_edited)
{
	impl_->setIsEdited(is_edited);
}

void PostSetter::setLastEditedTime(const string& last_edited_unix_time_milliseconds)
{
	setLastEditedTime(Utility::convertUnixTimeFromString(last_edited_unix_time_milliseconds));
}

void PostSetter::setLastEditedTime(const boost::posix_time::ptime& last_edited_time)
{
	impl_->setLastEditedTime(last_edited_time);
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite