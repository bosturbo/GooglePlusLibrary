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

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Notification;
class Post;

class GOOGLEPLUSLIBRARY_API PostNotificationDetail
{
	friend class Notification;

protected:
	PostNotificationDetail();

public:
	PostNotificationDetail(const Notification& notification);

public:
	Post getAttachedPost();

public:
	virtual ~PostNotificationDetail();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite