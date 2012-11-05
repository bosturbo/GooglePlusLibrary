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

#include <boost/any.hpp>
#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API Notification
{
	friend class NotificationDetail;

public:// TODO
	Notification();
	static Notification createInstance();

public:
	std::wstring getType() const;
protected:
	void setType(const std::wstring& notify_type);
private:
	std::wstring notify_type_;

public:
	
	template<class T> T getDetail()
	{
		return boost::any_cast<T>(notification_detail_);
	}

protected:
	void setDetails(const std::wstring& details);
private:
	std::wstring details_;

public:
	void read();

public:
	virtual ~Notification();

private:
	boost::any notification_detail_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite