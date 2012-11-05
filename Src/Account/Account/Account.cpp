#include <Account/Account/Account.hpp>
#include <Account/AccountList/AddedAccountList.hpp>
#include <Account/AccountList/AddedYouAccountList.hpp>
#include <Thread/ReadWriteMutex.hpp>

#ifdef GOOGLEPLUSLIBRARY_NO_WARNINGS
#ifdef _MSC_VER
#pragma warning (disable:4819)
#endif
#endif

#include <boost/spirit/include/qi.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
namespace qi = boost::spirit::qi;

Account::Account()
:account_id_(L""),
current_account_image_url_(L""),
added_account_list_(make_shared<AddedAccountList>()),
added_you_account_list_(make_shared<AddedYouAccountList>()),
read_write_mutex_(make_shared<ReadWriteMutex>())
{
}


bool Account::verifyAccountID(const wstring& account_id)
{
	qi::rule<wstring::const_iterator, wstring()> id_rule = qi::char_('0','9') | qi::char_('a','z') | qi::char_('A','Z');

	if(qi::parse(account_id.cbegin(), account_id.cend(), +id_rule))
	{
		return true;
	}
	else
	{
		return false;
	}
}

wstring Account::getAccountID() const
{
	return account_id_;
}

wstring Account::getAccountName() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return account_name_;
}

wstring Account::getCurrentAccountImageUrl() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return current_account_image_url_;
}

AddedAccountList* Account::getAddedAccountList() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return added_account_list_.get();
}

AddedYouAccountList* Account::getAddedYouAccountList() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return added_you_account_list_.get();
}

Account::~Account()
{

}

} // namespace GooglePlusLibrary
} // namespace Gplusnasite
