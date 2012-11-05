#include <Notification/NotificationDetail.hpp>
#include <Notification/Notification.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

NotificationDetail::NotificationDetail(const Notification& notification)
{
	//details_ = notification.getDetails();
}

wstring NotificationDetail::getDetails() const
{
	return details_;
}

NotificationDetail::~NotificationDetail()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite