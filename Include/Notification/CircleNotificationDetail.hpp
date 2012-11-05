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
class AccountList;

class GOOGLEPLUSLIBRARY_API CircleNotificationDetail
{
	friend class Notification;

protected:
	CircleNotificationDetail();
public:
	CircleNotificationDetail(const Notification& notification);

public:
	AccountList getAttachedAccountList();

public:
	virtual ~CircleNotificationDetail();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite