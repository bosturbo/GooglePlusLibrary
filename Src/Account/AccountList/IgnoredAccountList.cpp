#include <Account/AccountList/IgnoredAccountList.hpp>
#include <Account/AccountList/AccountList.hpp>

using namespace std;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

IgnoredAccountList::IgnoredAccountList(void)
:my_account_id_(L""),
account_list_(make_shared<AccountList>())
{
}


void IgnoredAccountList::update()
{
	updateAsync();
	waitupdateAsync();
}

void IgnoredAccountList::updateAsync()
{
	boost::thread update_thread(boost::bind(&IgnoredAccountList::updateAsyncThreadMethod, this));
	update_thread_ = boost::move(update_thread);
}

void IgnoredAccountList::waitupdateAsync()
{
	update_thread_.join();
}

void IgnoredAccountList::updateAsyncThreadMethod()
{
	// TODO

	onUpdateCompleted();
}

wstring IgnoredAccountList::getMyAccountID() const
{
	return account_list_->getMyAccountID();
}

void IgnoredAccountList::setMyAccountID(const wstring& my_account_id)
{
	//account_list_->setMyAccountID(my_account_id);
}

IgnoredAccountList::~IgnoredAccountList(void)
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite