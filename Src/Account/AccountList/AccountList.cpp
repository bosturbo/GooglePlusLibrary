#include <Account/AccountList/AccountList.hpp>
#include <Account/Account/Account.hpp>
#include <Account/AccountList/AccountContainer.hpp>
#include <Thread/ReadWriteMutex.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

AccountList::AccountList()
:read_write_mutex_(make_shared<ReadWriteMutex>())
{
}

wstring AccountList::getMyAccountID() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return my_account_id_;
}

void AccountList::setMyAccountID(const wstring& my_account_id)
{
	ScopedWriteLock lock(*read_write_mutex_);
	my_account_id_ = my_account_id;
}

bool AccountList::add(const wstring& account_id)
{
	if(account_id.empty())
	{
		return false;
	}
	ScopedWriteLock lock(*read_write_mutex_);
	auto result = account_id_list_.push_back(account_id);
	return result.second;
}

bool AccountList::add(const Account& account)
{
	if(!add(account.getAccountID()))
	{
		return false;
	}
	onAccountAdded(account);
	return true;
}

void AccountList::updateItem(const Account& account)
{
	AccountContainer::updateItem(account);
}

bool AccountList::remove(const wstring& account_id)
{
	ScopedWriteLock lock(*read_write_mutex_);
	typedef AccountIDList::index<search_by_account_id>::type AccountIndex;

	AccountIndex& account_index = account_id_list_.get<search_by_account_id>();
	auto account_id_it = account_index.find(account_id);
	if(account_id_it == account_index.end())
	{
		// not found
		return false;
	}
	account_index.erase(account_id_it, account_index.end());
	onAccountDeleted(account_id);
	return true;
}

const Account* AccountList::getByAccountID(const wstring& account_id) const
{
	return AccountContainer::getByAccountID(account_id);
}

const Account* AccountList::getByIndex(int index) const
{
	ScopedReadLock lock(*read_write_mutex_);
	typedef AccountIDList::index<search_sequence>::type AccountSequencedIndex;
	const AccountSequencedIndex& account_index = account_id_list_.get<search_sequence>();

	auto account_it = account_index.begin();

	int count = 0;
	while(account_it != account_index.end())
	{
		if(count == index)
		{
			return getByAccountID(*account_it);
		}
		++count;
	}
	return nullptr;
}

const Account* AccountList::operator[](const wstring& account_id) const
{
	return getByAccountID(account_id);
}

const Account* AccountList::operator[](int index) const
{
	return getByIndex(index);
}

int AccountList::count() const
{
	ScopedReadLock lock(*read_write_mutex_);
	typedef AccountIDList::index<search_by_account_id>::type AccountIndex;
	const AccountIndex& account_index = account_id_list_.get<search_by_account_id>();
	return account_index.size();
}

AccountList::~AccountList()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite