#include <Account/Account/AccountSetter.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

AccountSetter::AccountSetter()
:account_(make_shared<Account>())
{
}

void AccountSetter::setAccountID(const wstring& account_id)
{
	ScopedWriteLock lock(*read_write_mutex_(*(account_.get())));
	account_id_(*(account_.get())) = account_id;
}

void AccountSetter::setAccountName(const wstring& account_name)
{
	ScopedWriteLock lock(*read_write_mutex_(*(account_.get())));
	account_name_(*(account_.get())) = account_name;
}

void AccountSetter::setCurrentAccountSetterImageUrl(const wstring& current_account_image_url)
{
	ScopedWriteLock lock(*read_write_mutex_(*(account_.get())));
	current_account_image_url_(*(account_.get())) = current_account_image_url;
}

shared_ptr<Account> AccountSetter::result()
{
	return account_;
}

AccountSetter::~AccountSetter()
{

}

} // namespace GooglePlusLibrary
} // namespace Gplusnasite
