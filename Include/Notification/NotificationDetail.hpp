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

#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Notification;

class GOOGLEPLUSLIBRARY_API NotificationDetail
{
public:
	NotificationDetail(const Notification& notification);

protected:
	std::wstring getDetails() const;
private:
	std::wstring details_;

public:
	virtual ~NotificationDetail();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite