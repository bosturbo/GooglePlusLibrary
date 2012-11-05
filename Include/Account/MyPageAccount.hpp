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

#include <memory>
#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Account;

/*!
* @~english
* @brief Class that manipulate my Google+ Page
* @~japanese
* @brief 自分のGoogle+ Pageを操作するためのクラス
*/
class GOOGLEPLUSLIBRARY_API MyPageAccount
{
public:
	MyPageAccount();

	/*!
	* @~english
	* @brief Get accout id
	* @return account id(e.g. 116324207729009185938)
	* @~japanese
	* @brief アカウントIDを取得します
	* @return アカウントID(例: 116324207729009185938)
	*/
	std::wstring getAccountID() const;

	virtual ~MyPageAccount();

private:
	std::shared_ptr<Account> google_plus_account_;
};

} // namespace GooglePlusLibrary
} // namespace Gplusnasite