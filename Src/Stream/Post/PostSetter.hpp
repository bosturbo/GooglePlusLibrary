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

#include <Stream/Post/Post.hpp>

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class AttachedAlbumSetter;
class AttachedCircleSetter;
class AttachedImageVideoSetter;
class AttachedLocationSetter;
class AttachedSearchResultSetter;
class AttachedUrlSetter;
class AttachedYouTubePlaylistSetter;

class GOOGLEPLUSLIBRARY_API PostSetter : public Post
{
public:
	PostSetter();
	
	void setPostType(const std::string& post_type);
	void setPostType(const std::wstring& post_type);

	void setAuthorName(const std::string& author_name);
	void setAuthorName(const std::wstring& author_name);

	void setAccountID(const std::string& account_id);
	void setAccountID(const std::wstring& account_id);
	
	void setAccountImageUrl(const std::string& account_image_url);
	void setAccountImageUrl(const std::wstring& account_image_url);

	void setIsResharedPost(bool is_shared_post);

	void setAttachedAlbum(AttachedAlbumSetter& attached_album_setter);
	void setAttachedAlbum(const AttachedAlbum& attached_album);

	void setAttachedCircle(AttachedCircleSetter& attached_circle_setter);
	void setAttachedCircle(const AttachedCircle& attached_circle);

	void setAttachedImageVideo(AttachedImageVideoSetter& attached_image_video_setter);
	void setAttachedImageVideo(const AttachedImageVideo& attached_image_video);

	void setAttachedLocation(AttachedLocationSetter& attached_location_setter);
	void setAttachedLocation(const AttachedLocation& attached_location);

	void setAttachedSearchResult(AttachedSearchResultSetter& attached_search_result_setter);
	void setAttachedSearchResult(const AttachedSearchResult& attached_search_result);

	void setAttachedUrl(AttachedUrlSetter& attached_url_setter);
	void setAttachedUrl(const AttachedUrl& attached_url);

	void setAttachedYouTubePlaylist(AttachedYouTubePlaylistSetter& attached_youtube_play_list_setter);
	void setAttachedYouTubePlaylist(const AttachedYouTubePlaylist& attached_youtube_play_list);

	void setOriginalPostID(const std::string& original_post_id);
	void setOriginalPostID(const std::wstring& original_post_id);

	void setOriginalPostMessage(const std::string& original_post_message);
	void setOriginalPostMessage(const std::wstring& original_post_message);

	void setOriginalPostUrl(const std::string& original_post_url);
	void setOriginalPostUrl(const std::wstring& original_post_url);

	void setPostID(const std::string& post_id);
	void setPostID(const std::wstring& post_id);

	void setPostUrl(const std::string& post_url);
	void setPostUrl(const std::wstring& post_url);

	void setPlusOneID(const std::string& plus_one_id);
	void setPlusOneID(const std::wstring& plus_one_id);

	void setPostTime(const std::string& post_unix_time_milliseconds);
	void setPostTime(const boost::posix_time::ptime& post_time);

	void setIsPublicPost(bool is_public_post);

	void setMessage(const std::string& message);
	void setMessage(const std::wstring& message);

	void setIsMobilePost(bool is_mobile_post);

	void setIsCommentDisabled(bool is_comment_disabled);

	void setIsLockdPost(bool is_lock_post);

	void setIsMyPost(bool is_my_post);

	void setIsEdited(bool is_edited);

	void setLastEditedTime(const std::string& last_edited_unix_time_milliseconds);
	void setLastEditedTime(const boost::posix_time::ptime& last_edited_time);
	
	static void bindToScript(lua_State* lua_state);
	
	virtual ~PostSetter();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite