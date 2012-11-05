#include <Account/AccountList/FriendSuggestionList.hpp>
#include <Account/AccountList/AccountList.hpp>

using namespace std;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

FriendSuggestionList::FriendSuggestionList(void)
:my_account_id_(L""),
account_list_(make_shared<AccountList>())
{
}


void FriendSuggestionList::update()
{
	updateAsync();
	waitupdateAsync();
}

void FriendSuggestionList::updateAsync()
{
	boost::thread update_thread(boost::bind(&FriendSuggestionList::updateAsyncThreadMethod, this));
	update_thread_ = boost::move(update_thread);
}

void FriendSuggestionList::waitupdateAsync()
{
	update_thread_.join();
}

void FriendSuggestionList::updateAsyncThreadMethod()
{
	// TODO

	onUpdateCompleted();
}

wstring FriendSuggestionList::getMyAccountID() const
{
	return account_list_->getMyAccountID();
}

void FriendSuggestionList::setMyAccountID(const wstring& my_account_id)
{
	//account_list_->setMyAccountID(my_account_id);
}

FriendSuggestionList::~FriendSuggestionList(void)
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite