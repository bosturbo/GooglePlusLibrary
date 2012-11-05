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

#include <Account/Account/Account.hpp>
#include <Thread/ReadWriteMutex.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API AccountBase
{
public:
	AccountBase()
	{
	}

protected:

	static std::wstring& account_name_(Account& account)
	{
		return account.account_name_;
	}

	static std::wstring& account_id_(Account& account)
	{
		return account.account_id_;
	}

	static std::wstring& current_account_image_url_(Account& account)
	{
		return account.current_account_image_url_;
	}
	/*
	static std::shared_ptr<AddedAccountBaseList>& added_account_list_(Account& account)
	{
		return account.added_account_list_;
	}

	static std::shared_ptr<AddedYouAccountBaseList>& added_you_account_list_(Account& account)
	{
		return account.added_you_account_list_;
	}
	*/
	static std::shared_ptr<ReadWriteMutex>& read_write_mutex_(Account& account)
	{
		return account.read_write_mutex_;
	}

public:
	virtual ~AccountBase()
	{
	}


};

} // namespace GooglePlusLibrary
} // namespace Gplusnasite
