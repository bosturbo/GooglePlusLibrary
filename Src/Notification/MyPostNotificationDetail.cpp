#include <Notification/MyPostNotificationDetail.hpp>
#include <Notification/Notification.hpp>
#include <Stream/Post/MyPost/MyPost.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

MyPostNotificationDetail::MyPostNotificationDetail()
{
}

MyPostNotificationDetail::MyPostNotificationDetail(const Notification& notification)
{
	Notification target_notification = notification;
	
	try
	{
		*this = target_notification.getDetail<MyPostNotificationDetail>();
	}
	catch (boost::bad_any_cast)
	{
	}
}

MyPost MyPostNotificationDetail::getAttachedMyPost()
{
	MyPost my_post;
	return my_post;
}

MyPostNotificationDetail::~MyPostNotificationDetail()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite