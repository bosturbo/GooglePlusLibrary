#include <Account/AccountProfile/LivedPlace.hpp>
#include <Thread/ReadWriteMutex.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

LivedPlace::LivedPlace(const wstring& city_name, bool is_current)
:city_name_(city_name),
is_current_(is_current),
read_write_mutex_(make_shared<ReadWriteMutex>())
{
}

wstring LivedPlace::getCityName() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return city_name_;
}

void LivedPlace::setCityName(const wstring& city_name)
{
	ScopedWriteLock lock(*read_write_mutex_);
	city_name_ = city_name;
}

bool LivedPlace::isCurrent() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return is_current_;
}

void LivedPlace::setIsCurrent(bool is_current)
{
	ScopedWriteLock lock(*read_write_mutex_);
	is_current_ = is_current;
}

LivedPlace::~LivedPlace()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite