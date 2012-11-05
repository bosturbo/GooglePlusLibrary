#include <Notification/CircleNotificationDetail.hpp>
#include <Notification/Notification.hpp>
#include <Account/AccountList/AccountList.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

CircleNotificationDetail::CircleNotificationDetail()
{
}

CircleNotificationDetail::CircleNotificationDetail(const Notification& notification)
{
	Notification target_notification = notification;
	try
	{
		*this = target_notification.getDetail<CircleNotificationDetail>();
	}
	catch (boost::bad_any_cast)
	{
	}
}

AccountList CircleNotificationDetail::getAttachedAccountList()
{
	AccountList account_list;

	return account_list;
}

CircleNotificationDetail::~CircleNotificationDetail()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite