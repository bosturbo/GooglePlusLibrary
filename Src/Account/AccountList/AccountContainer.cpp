#include <Account/AccountList/AccountContainer.hpp>
#include <Account/Account/Account.hpp>
#include <Utility/Utility.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

boost::signals2::signal<void (const Account&)> AccountContainer::onAccountinserted;
boost::signals2::signal<void (const Account&)> AccountContainer::onAccountEdited;
boost::signals2::signal<void (const wstring&)> AccountContainer::onAccountDeleted;

map<wstring, Account> AccountContainer::account_container_;
ReadWriteMutex AccountContainer::read_write_mutex_;

AccountContainer::AccountContainer()
{
}

bool AccountContainer::insert(const Account& account)
{
	wstring account_id = account.getAccountID();
	if(account_id.empty())
	{
		return false;
	}

	ScopedWriteLock lock(read_write_mutex_);
	auto result = account_container_.insert(map<wstring, Account>::value_type(account_id, account));
	if(!result.second)
	{
		// already exist
		return false;
	}
	onAccountinserted(account);
	return true;
}

void AccountContainer::updateItem(const Account& account)
{
	ScopedWriteLock lock(read_write_mutex_);
	account_container_[account.getAccountID()] = account;
}

bool AccountContainer::erase(const wstring& account_id)
{
	ScopedWriteLock lock(read_write_mutex_);
	auto it = account_container_.find(account_id);

	if(it == account_container_.end())
	{
		// not found
		return false;
	}
	// found
	account_container_.erase(it);
	onAccountDeleted(account_id);
	return true;
}

const Account* AccountContainer::getByAccountID(const wstring& account_id)
{
	ScopedReadLock lock(read_write_mutex_);
	auto it = account_container_.find(account_id);

	if(it == account_container_.end())
	{
		// not found
		return nullptr;
	}
	// found
	return &(it->second);
}

AccountContainer::~AccountContainer()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite