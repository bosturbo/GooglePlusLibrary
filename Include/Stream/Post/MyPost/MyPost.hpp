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

#ifdef GOOGLEPLUSLIBRARY_NO_WARNINGS
#ifdef _MSC_VER
#pragma warning (disable:4251)
#endif
#endif

#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>
#include <memory>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Post;
class PostSetter;
class ShareRangeList;
class AttachedAlbum;
class AttachedCircle;
class AttachedImageVideo;
class AttachedLocation;
class AttachedSearchResult;
class AttachedUrl;
class AttachedYouTubePlaylist;
class ReadWriteMutex;

class GOOGLEPLUSLIBRARY_API MyPost
{
	friend class MyPostNotificationDetail;
	friend class MyPostBase;

public:
	MyPost();

public:
	/*
	void create(const std::wstring& message, const ShareRangeList& share_range);
	void create(const std::wstring& message, const ShareRangeList& share_range, const AttachedAlbum& attached_album);
	void create(const std::wstring& message, const ShareRangeList& share_range, const AttachedCircle& attached_circle);
	void create(const std::wstring& message, const ShareRangeList& share_range, const AttachedImageVideo& attached_image_video);
	void create(const std::wstring& message, const ShareRangeList& share_range, const AttachedLocation& attached_location);
	void create(const std::wstring& message, const ShareRangeList& share_range, const AttachedUrl& attached_url);
	void create(const std::wstring& message, const ShareRangeList& share_range, const AttachedYouTubePlaylist& attached_youtube_playlist);
	*/

public:
	std::wstring getPostType() const;

	std::wstring getAuthorName() const;

	std::wstring getAccountID() const;

	std::wstring getAccountImageUrl() const;

	bool isResharedPost() const;

	std::shared_ptr<AttachedAlbum> getAttachedAlbum() const;

	std::shared_ptr<AttachedCircle> getAttachedCircle() const;

	std::shared_ptr<AttachedImageVideo> getAttachedImageVideo() const;

	std::shared_ptr<AttachedLocation> getAttachedLocation() const;

	std::shared_ptr<AttachedSearchResult> getAttachedSearchResult() const;

	std::shared_ptr<AttachedUrl> getAttachedUrl() const;

	std::shared_ptr<AttachedYouTubePlaylist> getAttachedYouTubePlaylist() const;

	std::wstring getOriginalPostID() const;

	std::wstring getOriginalPostMessage() const;

	std::wstring getOriginalPostUrl() const;

	std::wstring getPostID() const;

	std::wstring getPostUrl() const;

	std::wstring getPlusOneID() const;

	boost::posix_time::ptime getPostTime() const;

	bool isPublicPost() const;

	std::wstring getMessage() const;

	void editMessage(const std::wstring& message);
	
	bool isMobilePost() const;

	bool isCommentDisabled() const;

	void disableComment(bool is_disable);
	
	bool isLockdPost() const;
	
	void lockPost(bool is_lock);

	bool isEdited() const;

	boost::posix_time::ptime getLastEditedTime() const;
	
	void reshare(const std::wstring& my_account_id, const std::wstring& message, const ShareRangeList& share_range);
	
	//Post toPost();
	
public:
	virtual ~MyPost();

private:
	std::shared_ptr<PostSetter> post_setter_;
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;

};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite