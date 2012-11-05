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
#pragma warning (disable:4996)
#endif
#endif

#include <boost/thread.hpp>
#include <boost/signals2.hpp>
#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Account;
class AccountList;

/*!
* @~english
* @brief Class to get a list of accounts that you have added to the circle that the user
* @~japanese
* @brief そのユーザーをサークルに追加したアカウントのリストを取得するためのクラス
*/
class GOOGLEPLUSLIBRARY_API AddedYouAccountList
{
	friend class MyAccountImpl;

public:
	AddedYouAccountList();

public:

	/*!
	* @~english
	* @brief Update the list
	* @~japanese
	* @brief リストを更新します
	*/
	void update();

	/*!
	* @~english
	* @brief Asynchronous update the list
	* @~japanese
	* @brief リストを非同期に更新します
	*/
	void updateAsync();

	/*!
	* @~english
	* @brief Wait until you have completed asynchronous update of the list
	* @~japanese
	* @brief リストの非同期更新が完了するまで待機します
	*/
	void waitupdateAsync();

	boost::signals2::signal<void()> onUpdateCompleted;
		
private:

	/*!
	* @~english
	* @brief A function to update the list in a separate thread
	* @~japanese
	* @brief 別スレッドでリストの更新をする関数です
	*/
	void updateAsyncThreadMethod();
	boost::thread update_thread_;

	/*!
	* @~english
	* @brief Gets the account id of the target
	* @details Returns the empty wstring if the account id of the target has not been set
	* @return the account id of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief 対象のアカウントIDを取得します
	* @details 対象のアカウントIDが設定されていない場合は空文字を返します
	* @return 対象のアカウントID(例: 116324207729009185938)
	*/
	std::wstring getMyAccountID() const;
protected:

	/*!
	* @~english
	* @brief Sets the account id of the target
	* @param my_account_id the account id of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief 対象のアカウントIDを設定します
	* @param my_account_id 対象のアカウントID(例: 116324207729009185938)
	*/
	void setMyAccountID(const std::wstring& my_account_id);
private:
	std::wstring my_account_id_;

public:

	/*!
	* @~english
	* @brief Get account information
	* @details Returns null if the corresponding account could not be found
	* @param account_id ID of the account information you want to get(e.g. 110903198133008172755)
	* @return Account information with the specified account id
	* @~japanese
	* @brief アカウント情報を取得します
	* @details 該当するアカウントが見つからなかった場合nullを返します
	* @param account_id 取得したいアカウントのID(例: 110903198133008172755)
	* @return 指定したアカウントIDを持つアカウントの情報
	*/
	const Account* getByAccountID(const std::wstring& account_id) const;
	
	const Account* getByIndex(int index) const;

	/*!
	* @~english
	* @brief Get account information
	* @details Returns null if the corresponding account could not be found
	* @details This operator is only internally calls the GetByAccountID
	* @param account_id ID of the account information you want to get(e.g. 110903198133008172755)
	* @return Account information with the specified account id
	* @~japanese
	* @brief アカウント情報を取得します
	* @details 該当するアカウントが見つからなかった場合nullを返します
	* @details この演算子は内部的にGetByAccountIDを呼び出しているだけです
	* @param account_id 取得したいアカウントのID(例: 110903198133008172755)
	* @return 指定したアカウントIDを持つアカウントの情報
	*/
	const Account* operator[](const std::wstring& account_id) const;

	const Account* operator[](int index) const;

	virtual ~AddedYouAccountList();

private:
	std::shared_ptr<AccountList> account_list_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite