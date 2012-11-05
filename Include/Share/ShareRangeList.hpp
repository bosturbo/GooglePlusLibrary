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

#include <Circle/Circle.hpp>
#include <Account/Account/Account.hpp>


#include <string>
#include <list>
#include <map>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class MyAccount;
class AccountList;

/*!
* @~english
* @brief Class to share posts to set the range
* @~japanese
* @brief 投稿の公開範囲を設定するクラス
*/
class GOOGLEPLUSLIBRARY_API ShareRangeList
{
public:
	ShareRangeList();

public:
	/*!
	* @~english
	* @brief Range to include the public in post
	* @~japanese
	* @brief 投稿範囲に一般公開を含めます
	*/
	void addPublic();

	/*!
	* @~english
	* @brief Except to the public from a range submitted
	* @~japanese
	* @brief 投稿範囲から一般公開を除きます
	*/
	void removePublic();

private:
	bool is_added_public_;

public:
	/*!
	* @~english
	* @brief Range to include the circle of your post
	* @~japanese
	* @brief 投稿範囲にあなたのサークルを含めます
	*/
	void addYourCircle();

	/*!
	* @~english
	* @brief Except for the circle of your post from a range
	* @~japanese
	* @brief 投稿範囲からあなたのサークルを除きます
	*/
	void removeYourCircle();
private:
	bool is_added_your_circle_;

public:
	/*!
	* @~english
	* @brief Range to include the circle of extend post
	* @~japanese
	* @brief 投稿範囲に友達の友達サークルを含めます
	*/
	void addExtendCircle();

	/*!
	* @~english
	* @brief Except for the circle of extend post from a range
	* @~japanese
	* @brief 投稿範囲から友達の友達サークルを除きます
	*/
	void removeExtendCircle();
private:
	bool is_added_extend_circle_;

public:
	/*!
	* @~english
	* @brief Add the user for mension
	* @param account Account of the user you want to mension
	* @~japanese
	* @brief メンションするユーザーを追加します
	* @param account メンションしたいユーザーのアカウント
	*/
	void addAccount(const Account& account);

	/*!
	* @~english
	* @brief Add the user for mension
	* @param account_list List of accounts of users who want to mension
	* @~japanese
	* @brief メンションするユーザーを追加します
	* @param account_list メンションしたいユーザーのアカウントのリスト
	*/
	void addAccount(const std::list<Account>& account_list);

	/*!
	* @~english
	* @brief Add the user for mension
	* @param account_list List of accounts of users who want to mension
	* @~japanese
	* @brief メンションするユーザーを追加します
	* @param account_list メンションしたいユーザーのアカウントのリスト
	*/
	void addAccount(const AccountList& account_list);
	
	/*!
	* @~english
	* @brief Exclude the specified user from the list of users was set to mension
	* @param account_id ID of the user account that you do not want to mension in the list
	* @~japanese
	* @brief 設定したメンションするユーザーのリストから指定したユーザーを除外します
	* @param account_id リストの中でメンションしたくないユーザーのアカウントID
	*/
	void removeAccount(const std::wstring& account_id);

	/*!
	* @~english
	* @brief Add to specified in the range include the Circle
	* @param circle Circle added to the range you want to specify post
	* @~japanese
	* @brief 投稿範囲に指定したサークルを含めます
	* @param circle 投稿範囲に追加指定したいサークル
	*/
	void addCircle(const Circle& circle);
	
	/*!
	* @~english
	* @brief Except for the ID specified in the range of circle post
	* @param circle_id ID of the circle you want to specify the scope exclusion in post
	* @~japanese
	* @brief 投稿範囲に指定したサークルのIDを除きます
	* @param circle_id 投稿範囲に除外指定したいサークルのID
	*/
	void removeCircle(const std::wstring& circle_id);

	/*!
	* @~english
	* @brief Clears all the user specified mension
	* @~japanese
	* @brief メンション指定したユーザーをすべてクリアします
	*/
	void removeAllAccounts();

	/*!
	* @~english
	* @brief Clears all of the circle was set post added to the range
	* @~japanese
	* @brief 投稿範囲に追加設定したサークルをすべてクリアします
	*/
	void removeAllCircles();

public:
	void isSendMailToNonGooglePlusUser(bool is_send_mail);
private:
	bool is_send_mail_;

protected:
	std::wstring createParameter(const std::wstring& target_account_id) const;
public:
	virtual ~ShareRangeList();

private:
	std::map<std::wstring, Account> account_list_;
	mutable std::map<std::wstring, Circle> circle_list_;
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite