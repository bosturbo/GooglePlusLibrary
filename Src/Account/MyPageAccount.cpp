#include <Account/MyPageAccount.hpp>
#include <Account/Account/Account.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

MyPageAccount::MyPageAccount()
:google_plus_account_(make_shared<Account>())
{
}

wstring MyPageAccount::getAccountID() const
{
	return google_plus_account_->getAccountID();
}

MyPageAccount::~MyPageAccount()
{
}

} // namespace GooglePlusLibrary
} // namespace Gplusnasite