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
#pragma warning (disable:4275)
#pragma warning (disable:4996)
#endif
#endif

#include <Thread/ReadWriteMutex.hpp>

#include <boost/signals2.hpp>
#include <boost/utility.hpp>
#include <map>

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Account;

/*!
* @~english
* @brief Container class in order to be able to access account information from anywhere
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @warning Please use the AccountList class if you are the general public
* @see AccountList
* @~japanese
* @brief どこからでもアカウント情報にアクセスできるようにするためのコンテナクラス
* @warning このクラスはライブラリ開発者ならびにLuaスクリプト編集者以外利用しないようにしてください
* @warning 一般の方はAccountListクラスをご利用ください
* @see AccountList
*/
class GOOGLEPLUSLIBRARY_API AccountContainer : boost::noncopyable
{
public:
	AccountContainer();

	/*!
	* @~english
	* @brief Add account in the Container
	* @details This is not a function to add the account to the Circle
	* @param account account information that add to the Container
	* @~japanese
	* @brief コンテナにアカウント情報を追加します
	* @details これはサークルにアカウントを追加する関数ではありません
	* @param account 追加するアカウント情報
	*/
	static bool insert(const Account& account);
	static boost::signals2::signal<void (const Account&)> onAccountinserted;

	static void updateItem(const Account& account);
	static boost::signals2::signal<void (const Account&)> onAccountEdited;

	static bool erase(const std::wstring& account_id);
	static boost::signals2::signal<void (const std::wstring&)> onAccountDeleted;

	/*!
	* @~english
	* @brief Get account information from the Container
	* @details Returns null if the corresponding account could not be found
	* @param account_id ID of the account information you want to get(e.g. 110903198133008172755)
	* @return Circle information with the specified circle id
	* @~japanese
	* @brief コンテナからアカウント情報を取得します
	* @details 該当するアカウントが見つからなかった場合nullを返します
	* @param account_id 取得したいアカウントのID(例: 110903198133008172755)
	* @return 指定したアカウントIDを持つアカウントの情報
	*/
	static const Account* getByAccountID(const std::wstring& account_id);

	virtual ~AccountContainer();

public:
	static void bindToScript(lua_State* lua_state);

private:
	static std::map<std::wstring, Account> account_container_;
	static ReadWriteMutex read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite