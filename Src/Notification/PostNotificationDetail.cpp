#include <Notification/PostNotificationDetail.hpp>
#include <Notification/Notification.hpp>
#include <Stream/Post/Post.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

PostNotificationDetail::PostNotificationDetail()
{
}

PostNotificationDetail::PostNotificationDetail(const Notification& notification)
{
	Notification target_notification = notification;
	
	try
	{
		*this = target_notification.getDetail<PostNotificationDetail>();
	}
	catch (boost::bad_any_cast)
	{
	}
}

Post PostNotificationDetail::getAttachedPost()
{
	Post my_post;
	return my_post;
}

PostNotificationDetail::~PostNotificationDetail()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite