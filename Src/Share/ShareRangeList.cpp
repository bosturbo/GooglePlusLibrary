#include <Share/ShareRangeList.hpp>
#include <Account/MyAccount/MyAccount.hpp>
#include <Account/AccountList/AccountList.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

ShareRangeList::ShareRangeList()
:is_added_public_(false),
is_added_your_circle_(false),
is_added_extend_circle_(false),
is_send_mail_(false)
{
}

void ShareRangeList::addPublic()
{
	is_added_public_ = true;
}

void ShareRangeList::removePublic()
{
	is_added_public_ = false;
}

void ShareRangeList::addYourCircle()
{
	is_added_your_circle_ = true;
}

void ShareRangeList::removeYourCircle()
{
	is_added_your_circle_ = false;
}

void ShareRangeList::addExtendCircle()
{
	is_added_extend_circle_ = true;
}

void ShareRangeList::removeExtendCircle()
{
	is_added_extend_circle_ = false;
}

void ShareRangeList::addAccount(const Account& account)
{
	account_list_.insert(map<wstring, Account>::value_type(account.getAccountID(), account));
}

void ShareRangeList::addAccount(const list<Account>& account_list)
{
	auto it = account_list.begin();
	while(it != account_list.end())
	{
		addAccount(*it);
		++it;
	}
}

void ShareRangeList::addAccount(const AccountList& account_list)
{

}

void ShareRangeList::removeAccount(const wstring& account_id)
{
	account_list_.erase(account_id);
}

void ShareRangeList::addCircle(const Circle& circle)
{
	circle_list_.insert(map<wstring, Circle>::value_type(circle.getCircleID(), circle));
}

void ShareRangeList::removeCircle(const wstring& circle_id)
{
	circle_list_.erase(circle_id);
}

void ShareRangeList::removeAllAccounts()
{
	account_list_.clear();
}

void ShareRangeList::removeAllCircles()
{
	circle_list_.clear();
}

void ShareRangeList::isSendMailToNonGooglePlusUser(bool is_send_mail)
{
	is_send_mail_ = is_send_mail;
}

wstring ShareRangeList::createParameter(const wstring& target_account_id) const
{
	wstring result(L"");

	if(is_added_public_ == true)
	{
		// add public
		Circle circle(L"", L"anyone");
		circle_list_.insert(map<wstring, Circle>::value_type(L"Anyone", circle));
	}
	if(is_added_your_circle_ == true)
	{
		wstring circle_id = target_account_id + L".1c";
		Circle circle(L"", circle_id);
		circle_list_.insert(map<wstring, Circle>::value_type(L"Your circles", circle));
	}
	if(is_added_extend_circle_ == true)
	{
		wstring circle_id = target_account_id + L".1f";
		Circle circle(L"", circle_id);
		circle_list_.insert(map<wstring, Circle>::value_type(L"Extended circles", circle));
	}

	result += L"{\"aclEntries\":[";

	// add circle
	auto circle_it = circle_list_.begin();
	int count = 0;
	while(circle_it != circle_list_.end())
	{
		if(count > 0)
		{
			result += L",";
		}
		result += L"{\\\"scope\\\":{\\\"scopeType\\\":\\\"focusGroup\\\",\\\"name\\\":\\\"\" + circle_it->second.getCircleName() + \"\\\",\\\"id\\\":\\\"\" + circle_it->first + \"\\\",\\\"me\\\":false,\\\"requiresKey\\\":false,\\\"groupType\\\":\\\"p\\\"},\\\"role\\\":20},";
		result += L"{\\\"scope\\\":{\\\"scopeType\\\":\\\"focusGroup\\\",\\\"name\\\":\\\"\" + circle_it->second.getCircleName() + \"\\\",\\\"id\\\":\\\"\" + circle_it->first + \"\\\",\\\"me\\\":false,\\\"requiresKey\\\":false,\\\"groupType\\\":\\\"p\\\"},\\\"role\\\":60}";
		
		++circle_it;
		++count;
	}

	// add account(mention)
	auto account_it = account_list_.begin();
	count = 0;
	bool is_contain_non_googleplus_user = false;
	while(account_it != account_list_.end())
	{
		if(count > 0)
		{
			result += L",";
		}
		result += L"{\\\"scope\\\":{\\\"iconUrl\\\":\\\"//lh5.googleusercontent.com/-h8VRA_0nnHM/AAAAAAAAAAI/AAAAAAAAABo/gNkVeE-6Lic/photo.jpg?sz=32\\\",\\\"scopeType\\\":\\\"user\\\",\\\"name\\\":\\\"\" + account_it->second.getAccountName() + \"\\\",\\\"id\\\":\\\"\" + account_it->first + \"\\\",\\\"me\\\":false,\\\"requiresKey\\\":false,\\\"isMe\\\":false},\\\"role\\\":20},";
		result += L"{\\\"scope\\\":{\\\"iconUrl\\\":\\\"//lh5.googleusercontent.com/-h8VRA_0nnHM/AAAAAAAAAAI/AAAAAAAAABo/gNkVeE-6Lic/photo.jpg?sz=32\\\",\\\"scopeType\\\":\\\"user\\\",\\\"name\\\":\\\"\" + account_it->second.getAccountName() + \"\\\",\\\"id\\\":\\\"\" + account_it->first + \"\\\",\\\"me\\\":false,\\\"requiresKey\\\":false,\\\"isMe\\\":false},\\\"role\\\":60}";

		/*
		TODO
		if(account_it->second.getisnon)
		{
			is_contain_non_googleplus_user = true;
		}
		*/
		++account_it;
		++count;
	}

	result += L",true,[";

	account_it = account_list_.begin();
	count = 0;
	while(account_it != account_list_.end())
	{
		if(count > 0)
		{
			result += L",";
		}
		result += L"[null,\"" + account_it->first + L"\"]";

		++account_it;
		++count;
	}
	result += L"],";

	// is send mail non googleplus user
	if((is_send_mail_ == true) && (is_contain_non_googleplus_user == true))
	{
		result += L"true";
	}
	else
	{
		result += L"false";
	}
	result += L",";

	//! @todo Google+を使ってないユーザーかどうかを取得する関数を実装しないと先へすすめない
	// is contains non googleplus user
	if(is_contain_non_googleplus_user == true)
	{
		result += L"true";
	}
	else
	{
		result += L"false";
	}

	return result;
}

ShareRangeList::~ShareRangeList()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite