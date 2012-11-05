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
class MyPost;

class GOOGLEPLUSLIBRARY_API MyPostNotificationDetail
{
	friend class Notification;

protected:
	MyPostNotificationDetail();
public:
	MyPostNotificationDetail(const Notification& notification);

public:
	MyPost getAttachedMyPost();

public:
	virtual ~MyPostNotificationDetail();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite