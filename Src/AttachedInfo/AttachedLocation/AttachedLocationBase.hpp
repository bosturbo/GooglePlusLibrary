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

#include <AttachedInfo/AttachedLocation/AttachedLocation.hpp>
#include <Thread/ReadWriteMutex.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API AttachedLocationBase
{
public:
	AttachedLocationBase()
	{
	}

protected:

	static double& latitude_(AttachedLocation& attached_location)
	{
		return attached_location.latitude_;
	}
	static double& longitude_(AttachedLocation& attached_location)
	{
		return attached_location.longitude_;
	}

	static std::wstring& location_name_(AttachedLocation& attached_location)
	{
		return attached_location.location_name_;
	}

	static std::wstring& address_(AttachedLocation& attached_location)
	{
		return attached_location.address_;
	}

	static std::wstring& google_map_page_image_url_(AttachedLocation& attached_location)
	{
		return attached_location.google_map_page_image_url_;
	}

	static bool& is_checkined_(AttachedLocation& attached_location)
	{
		return attached_location.is_checkined_;
	}

	static std::shared_ptr<ReadWriteMutex>& read_write_mutex_(AttachedLocation& attached_location)
	{
		return attached_location.read_write_mutex_;
	}

public:
	virtual ~AttachedLocationBase()
	{
	}
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite