#include <Account/AccountProfile/ContactAddress.hpp>
#include <Thread/ReadWriteMutex.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

ContactAddress::ContactAddress(BOOST_SCOPED_ENUM(AddressType) address_type, const wstring& address)
:address_type_(AddressType::Unknown),
address_(address),
read_write_mutex_(make_shared<ReadWriteMutex>())
{
}

ContactAddress::BOOST_SCOPED_ENUM(AddressType) ContactAddress::getAddressType() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return address_type_;
}

void ContactAddress::setAddressType(BOOST_SCOPED_ENUM(AddressType) address_type)
{
	ScopedWriteLock lock(*read_write_mutex_);
	address_type_ = address_type;
}

wstring ContactAddress::getAddress() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return address_;
}

void ContactAddress::setAddress(const wstring& address)
{
	ScopedWriteLock lock(*read_write_mutex_);
	address_ = address;
}

ContactAddress::~ContactAddress()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite