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
#pragma warning (disable:4996)
#endif
#endif

#include <boost/detail/scoped_enum_emulation.hpp>

#include <memory>
#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class ReadWriteMutex;

class GOOGLEPLUSLIBRARY_API ContactAddress
{
public:

	BOOST_SCOPED_ENUM_START(AddressType)
	{
		Unknown,
		Phone,
		Mobile,
		Email,
		Address,
		Fax,
		Pager,

		AIM,
		GoogleTalk,
		ICQ,
		Jabber,
		MSN,
		NetMeeting,
		QQ,
		Skype,
		Yahoo
	}; BOOST_SCOPED_ENUM_END

	ContactAddress(BOOST_SCOPED_ENUM(AddressType) address_type = AddressType::Unknown, const std::wstring& address = L"");

public:
	BOOST_SCOPED_ENUM(AddressType) getAddressType() const;
protected:
	void setAddressType(BOOST_SCOPED_ENUM(AddressType) address_type);
private:
	BOOST_SCOPED_ENUM(AddressType) address_type_;

public:
	std::wstring getAddress() const;
protected:
	void setAddress(const std::wstring& address);
private:
	std::wstring address_;

public:
	virtual ~ContactAddress();
private:
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite