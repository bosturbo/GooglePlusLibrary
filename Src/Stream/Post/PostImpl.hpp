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

#ifdef _MSC_VER
#pragma warning (disable:4251)
#pragma warning (disable:4996)
#endif

#include <Thread/ReadWriteMutex.hpp>

#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/flyweight/no_tracking.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>
#include <memory>

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class ShareRangeList;
class AttachedAlbum;
class AttachedAlbumSetter;
class AttachedCircle;
class AttachedCircleSetter;
class AttachedImageVideo;
class AttachedImageVideoSetter;
class AttachedLocation;
class AttachedLocationSetter;
class AttachedSearchResult;
class AttachedSearchResultSetter;
class AttachedUrl;
class AttachedUrlSetter;
class AttachedYouTubePlaylist;
class AttachedYouTubePlaylistSetter;
class CommentList;
class JsonObject;
//class ReadWriteMutex;

class GOOGLEPLUSLIBRARY_API PostImpl
{
public:
	PostImpl();

public:
	std::wstring getPostType() const;
	void setPostType(const std::wstring& post_type);

private:
	std::wstring post_type_;

public:
	std::wstring getAuthorName() const;
	void setAuthorName(const std::wstring& author_name);
private:
	std::wstring author_name_;

public:
	std::wstring getAccountID() const;
	void setAccountID(const std::wstring& account_id);
private:
	std::wstring account_id_;

public:

	std::wstring getAccountImageUrl() const;
	void setAccountImageUrl(const std::wstring& account_image_url);

private:
	std::wstring account_image_url_;

public:
	bool isResharedPost() const;
	void setIsResharedPost(bool is_shared_post);

private:
	bool is_shared_post_;

public:
	std::shared_ptr<AttachedAlbum> getAttachedAlbum() const;
	void setAttachedAlbum(const AttachedAlbum& attached_album);
	void setAttachedAlbum(AttachedAlbumSetter& attached_album_setter);
private:
	std::shared_ptr<AttachedAlbum> attached_album_;

public:
	std::shared_ptr<AttachedCircle> getAttachedCircle() const;
	void setAttachedCircle(const AttachedCircle& attached_circle);
	void setAttachedCircle(AttachedCircleSetter& attached_circle_setter);
private:
	std::shared_ptr<AttachedCircle> attached_circle_;

public:
	std::shared_ptr<AttachedImageVideo> getAttachedImageVideo() const;
	void setAttachedImageVideo(const AttachedImageVideo& attached_image_video);
	void setAttachedImageVideo(AttachedImageVideoSetter& attached_image_video_setter);
private:
	std::shared_ptr<AttachedImageVideo> attached_image_video_;

public:
	std::shared_ptr<AttachedLocation> getAttachedLocation() const;
	void setAttachedLocation(const AttachedLocation& attached_location);
	void setAttachedLocation(AttachedLocationSetter& attached_location_setter);
private:
	std::shared_ptr<AttachedLocation> attached_location_;

public:
	std::shared_ptr<AttachedSearchResult> getAttachedSearchResult() const;
	void setAttachedSearchResult(const AttachedSearchResult& attached_search_result);
	void setAttachedSearchResult(AttachedSearchResultSetter& attached_search_result_setter);
private:
	std::shared_ptr<AttachedSearchResult> attached_search_result_;

public:
	std::shared_ptr<AttachedUrl> getAttachedUrl() const;
	void setAttachedUrl(const AttachedUrl& attached_url);
	void setAttachedUrl(AttachedUrlSetter& attached_url_setter);
private:
	std::shared_ptr<AttachedUrl> attached_url_;

public:
	std::shared_ptr<AttachedYouTubePlaylist> getAttachedYouTubePlaylist() const;
	void setAttachedYouTubePlaylist(const AttachedYouTubePlaylist& attached_youtube_play_list);
	void setAttachedYouTubePlaylist(AttachedYouTubePlaylistSetter& attached_youtube_play_list_setter);
private:
	std::shared_ptr<AttachedYouTubePlaylist> attached_youtube_play_list_;

public:
	std::wstring getOriginalPostID() const;
	void setOriginalPostID(const std::wstring& original_post_id);
private:
	std::wstring original_post_id_;

public:
	std::wstring getOriginalpostMessage() const;
	void setOriginalpostMessage(const std::wstring& original_post_message);
private:
	std::wstring original_post_message_;

public:
	std::wstring getOriginalPostUrl() const;
	void setOriginalPostUrl(const std::wstring& original_post_url);
private:
	std::wstring original_post_url_;

public:
	std::wstring getPostID() const;
	void setPostID(const std::wstring& post_id);

private:
	std::wstring post_id_;

public:
	std::wstring getPostUrl() const;
	void setPostUrl(const std::wstring& post_url);

private:
	std::wstring post_url_;

public:
	std::wstring getPlusOneID() const;
	void setPlusOneID(const std::wstring& plus_one_id);

private:
	std::wstring plus_one_id_;

public:
	boost::posix_time::ptime getPostTime() const;
	void setPostTime(const boost::posix_time::ptime& post_time);
private:
	boost::posix_time::ptime post_time_;

public:
	bool isPublicPost() const;
	void setIsPublicPost(bool is_public_post);

private:
	bool is_public_post_;

public:
	std::wstring getMessage() const;
	void setMessage(const std::wstring& message);

private:
	std::wstring message_;

public:
	bool isMobilePost() const;
	void setIsMobilePost(bool is_mobile_post);

private:
	bool is_mobile_post_;

public:
	bool isCommentDisabled() const;
	void setIsCommentDisabled(bool is_comment_disabled);

private:
	bool is_comment_disabled_;

public:
	bool isLockdPost() const;
	void setIsLockdPost(bool is_lock_post);

private:
	bool is_lock_post_;

public:
	bool isMyPost() const;
	void setIsMyPost(bool is_my_post);
private:
	bool is_my_post_;

public:
	bool isEdited() const;
	void setIsEdited(bool is_edited);

private:
	bool is_edited_;

public:
	boost::posix_time::ptime getLastEditedTime() const;
	void setLastEditedTime(const boost::posix_time::ptime& last_edited_time);
private:
	boost::posix_time::ptime last_edited_time_;

public:
	void mutePost(bool is_mute);

public:
	void reshare(const std::wstring& my_account_id, const std::wstring& message, const ShareRangeList& share_range);

	CommentList* getCommentList() const;

public:

	//boost::signals2::signal<void (int)> onCommentAdded;

public:
	virtual ~PostImpl();

private:
	std::shared_ptr<CommentList> comment_list_;
	mutable ReadWriteMutex read_write_mutex_;
	
};

struct PostImplExtractor
{
	const std::wstring operator()(const PostImpl& post_impl) const
	{
		return post_impl.getPostID();
	}
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
