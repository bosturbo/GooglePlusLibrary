#include <Notification/Notification.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

Notification::Notification()
{
}

Notification Notification::createInstance()
{
	return Notification();
}

wstring Notification::getType() const
{
	return notify_type_;
}

void Notification::setType(const wstring& notify_type)
{
	notify_type_ = notify_type;
}

void Notification::setDetails(const wstring& details)
{
	details_ = details;
}

void Notification::read()
{

}

Notification::~Notification()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite