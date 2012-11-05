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

#include <Account/Account/AccountBase.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API AccountSetter : public AccountBase
{

public:
	AccountSetter();

public:
	
	/*!
	* @~english
	* @brief Set accout id
	* @param account_id account id(e.g. 116324207729009185938)
	* @~japanese
	* @brief アカウントIDを設定します
	* @param account_id アカウントID(例: 116324207729009185938)
	*/
	void setAccountID(const std::wstring& account_id);

	/*!
	* @~english
	* @brief Sets the name of the account
	* @param account_name AccountSetter name
	* @~japanese
	* @brief アカウント名を設定します
	* @param account_name アカウント名
	*/
	void setAccountName(const std::wstring& account_name);

	/*!
	* @~english
	* @brief Set url of the currently set account image
	* @param current_account_image_url url of the currently set account image
	* @~japanese
	* @brief 現在設定されているアカウントイメージのUrlを設定します
	* @param current_account_image_url 現在設定されているアカウントイメージのUrl
	*/
	void setCurrentAccountSetterImageUrl(const std::wstring& current_account_image_url);

	std::shared_ptr<Account> result();

public:
	virtual ~AccountSetter();

private:
	std::shared_ptr<Account> account_;
};

} // namespace GooglePlusLibrary
} // namespace Gplusnasite
