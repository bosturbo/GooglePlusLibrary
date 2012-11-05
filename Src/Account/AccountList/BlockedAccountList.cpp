#include <Account/AccountList/BlockedAccountList.hpp>
#include <Account/AccountList/AccountList.hpp>

using namespace std;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

BlockedAccountList::BlockedAccountList(void)
:my_account_id_(L""),
account_list_(make_shared<AccountList>())
{
}


void BlockedAccountList::update()
{
	updateAsync();
	waitupdateAsync();
}

void BlockedAccountList::updateAsync()
{
	boost::thread update_thread(boost::bind(&BlockedAccountList::updateAsyncThreadMethod, this));
	update_thread_ = boost::move(update_thread);
}

void BlockedAccountList::waitupdateAsync()
{
	update_thread_.join();
}

void BlockedAccountList::updateAsyncThreadMethod()
{
	// TODO

	onUpdateCompleted();
}

wstring BlockedAccountList::getMyAccountID() const
{
	return account_list_->getMyAccountID();
}

void BlockedAccountList::setMyAccountID(const wstring& my_account_id)
{
	//account_list_->setMyAccountID(my_account_id);
}

BlockedAccountList::~BlockedAccountList(void)
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite