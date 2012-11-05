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
#pragma warning (disable:4996)
#endif
#endif

#ifdef USE_WITH_QT
#include <QObject>
#include <QMetaType>
#endif

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/flyweight/no_tracking.hpp>
#include <boost/signals2.hpp>
#include <string>
#include <memory>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class PostImpl;
class ShareRangeList;
class AttachedAlbum;
class AttachedCircle;
class AttachedImageVideo;
class AttachedLocation;
class AttachedSearchResult;
class AttachedUrl;
class AttachedYouTubePlaylist;
class CommentList;
class JsonObject;
class ReadWriteMutex;

class GOOGLEPLUSLIBRARY_API Post
#ifdef USE_WITH_QT
:public QObject
#endif
{
public:
	Post();

	Post(const Post& post);
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

	bool isMobilePost() const;

	bool isCommentDisabled() const;

	bool isLockdPost() const;

	bool isMyPost() const;
	
	bool isEdited() const;
	
	boost::posix_time::ptime getLastEditedTime() const;

	void mutePost(bool is_mute);

	void reshare(const std::wstring& my_account_id, const std::wstring& message, const ShareRangeList& share_range);

	CommentList* getCommentList() const;

	Post& operator=(const Post& rhs);
	
	boost::signals2::signal<void (int)> onCommentAdded;
	
	virtual ~Post();

protected:
	std::shared_ptr<PostImpl> impl_;
	typedef boost::flyweights::flyweight<PostImpl*> flyweight_impl_type;
	flyweight_impl_type flyweight_impl_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite

#ifdef USE_WITH_QT
Q_DECLARE_METATYPE(Gplusnasite::GooglePlusLibrary::Post);
#endif