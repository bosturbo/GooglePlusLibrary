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

#include <AttachedInfo/AttachedCircle/AttachedCircle.hpp>
#include <Thread/ReadWriteMutex.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API AttachedCircleBase
{
public:
	AttachedCircleBase()
	{
	}

protected:
	static std::shared_ptr<AccountList>& account_list_(AttachedCircle& attached_circle)
	{
		return attached_circle.account_list_;
	}

	static std::shared_ptr<ReadWriteMutex>& read_write_mutex_(AttachedCircle& attached_circle)
	{
		return attached_circle.read_write_mutex_;
	}

public:
	virtual ~AttachedCircleBase()
	{
	}
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite