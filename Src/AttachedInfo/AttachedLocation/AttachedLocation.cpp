#include <AttachedInfo/AttachedLocation/AttachedLocation.hpp>
#include <Utility/Utility.hpp>
#include <Utility/LuaScript.hpp>

#include <Json/JsonObject.hpp>

#include <Thread/ReadWriteMutex.hpp>

#include <boost/lexical_cast.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

AttachedLocation::AttachedLocation()
:latitude_(-1),
longitude_(-1),
location_name_(L""),
address_(L""),
is_checkined_(false),
read_write_mutex_(make_shared<ReadWriteMutex>())
{
}

double AttachedLocation::getLatitude() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return latitude_;
}

double AttachedLocation::getLongitude() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return longitude_;
}

wstring AttachedLocation::getLocationName() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return location_name_;
}

wstring AttachedLocation::getAddress() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return address_;
}

wstring AttachedLocation::getGoogleMapPageImageUrl() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return google_map_page_image_url_;
}

bool AttachedLocation::isCheckined() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return is_checkined_;
}

AttachedLocation::~AttachedLocation()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite

