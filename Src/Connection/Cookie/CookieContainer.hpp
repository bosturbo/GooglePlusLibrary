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
#endif
#endif

#include <Thread/ReadWriteMutex.hpp>

#include <boost/utility.hpp>
#include <list>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Cookie;

/*!
* @~english
* @brief Container class in order to be able to access cookie information from anywhere
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief どこからでもクッキー情報にアクセスできるようにするためのコンテナクラス
* @warning このクラスはライブラリ開発者ならびにLuaスクリプト編集者以外利用しないようにしてください
*/
class GOOGLEPLUSLIBRARY_API CookieContainer : boost::noncopyable
{
	/*!
	* @~english
	* @brief Structure for associating cookies and e-mail address, the account ID
	* @~japanese
	* @brief クッキーとメールアドレス,アカウントIDを関連付けるための構造体
	*/
	struct CookieInformation
	{
		std::string mail_address;
		std::string account_id;
		std::list<Cookie> cookies;
	};

public:
	CookieContainer();

	/*!
	* @~english
	* @brief Associate the account ID that you specify in the email address that you specify
	* @details This function needs to be called other than after a login is not usually
	* @param target_mail_address E-mail address that you want to associate with the account ID(e.g. hogehoge@gmail.com)
	* @param account_id Associate account ID to add(e.g. 116324207729009185938)
	* @~japanese
	* @brief 指定したメールアドレスに指定したアカウントIDを関連付けます
	* @details 通常この関数はログイン完了後以外呼び出す必要はありません
	* @param target_mail_address アカウントIDに関連付けたいメールアドレス(例: hogehoge@gmail.com)
	* @param account_id 追加する関連付けるアカウントID(例: 116324207729009185938)
	*/
	static void setConnectID(const std::string& target_mail_address, const std::string& account_id);

	/*!
	* @~english
	* @brief Add the specified cookie to the list of cookies for the specified account ID
	* @param cookie Cookies you want to add
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief 指定したアカウントIDのクッキーのリストに指定したクッキーを追加します
	* @param cookie 追加したいクッキー
	* @param account_id 対象のアカウントID(例: 116324207729009185938)
	*/
	static void addCookieByAccountID(const Cookie& cookie, const std::string& account_id);

	static void addCookiesByAccountID(const std::list<Cookie>& cookie_list, const std::string& account_id);

	/*!
	* @~english
	* @brief Add the specified cookie to the list of cookies for the specified E-mail address
	* @param cookie Cookies you want to add
	* @param mail_address E-mail address of the target(e.g. hogehoge@gmail.com)
	* @~japanese
	* @brief 指定したメールアドレスのクッキーのリストに指定したクッキーを追加します
	* @param cookie 追加したいクッキー
	* @param mail_address 対象のメールアドレス(例: hogehoge@gmail.com)
	*/
	static void addCookieByMailAddress(const Cookie& cookie, const std::string& mail_address);

	static void addCookiesByMailAddress(const std::list<Cookie>& cookie_list, const std::string& mail_address);

	/*!
	* @~english
	* @brief Displays to standard output a list of cookie names and values of the account id for the specified
	* @param account_id account id of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief 指定したアカウントIDのクッキーについて名前と値の一覧を標準出力に表示します
	* @param account_id 対象のアカウントID(例: 116324207729009185938)
	*/
	static void showCookiesByAccountID(const std::string& account_id);

	/*!
	* @~english
	* @brief Displays to standard output a list of cookie names and values of the e-mail address for the specified
	* @param mail_address E-mail address of the target(e.g. hogehoge@gmail.com)
	* @~japanese
	* @brief 指定したメールアドレスのクッキーについて名前と値の一覧を標準出力に表示します
	* @param mail_address 対象のメールアドレス(例: hogehoge@gmail.com)
	*/
	static void showCookiesByMailAddress(const std::string& mail_address);

	/*!
	* @~english
	* @brief Gets a list of cookies for the specified account ID
	* @param account_id account id of the target(e.g. 116324207729009185938)
	* @return List of cookies for the specified account ID
	* @~japanese
	* @brief 指定したアカウントIDのクッキーのリストを取得する
	* @param account_id 対象のアカウントID(例: 116324207729009185938)
	* @return 指定したアカウントIDのクッキーのリスト
	*/
	static std::list<Cookie> getCookieByAccountID(const std::string& account_id);

	/*!
	* @~english
	* @brief Gets a list of cookie for the specified E-mail address
	* @param mail_address E-mail address of the target(e.g. hogehoge@gmail.com)
	* @~japanese
	* @brief 指定したメールアドレスのクッキーのリストを取得する
	* @param mail_address 対象のメールアドレス(例: hogehoge@gmail.com)
	*/
	static std::list<Cookie> getCookieByMailAddress(const std::string& mail_address);
	
	/*!
	* @~english
	* @brief Initialize the list of cookies for the specified account id
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief 指定したアカウントIDのクッキーのリストを初期化します
	* @param account_id 対象のアカウントID(例: 116324207729009185938)
	*/
	static void clearCookieByAccountID(const std::string& account_id);

	/*!
	* @~english
	* @brief Initialize the list of cookies for the specified e-mail address
	* @param mail_address E-mail address of the target(e.g. hogehoge@gmail.com)
	* @~japanese
	* @brief 指定したメールアドレスのクッキーのリストを初期化します
	* @param mail_address 対象のメールアドレス(例: hogehoge@gmail.com)
	*/
	static void clearCookieByMailAddress(const std::string& mail_address);

	/*!
	* @~english
	* @brief Initialize the list of cookies for all accounts
	* @~japanese
	* @brief すべてのアカウントのクッキーのリストを初期化します
	*/
	static void clearAllCookie();

	virtual ~CookieContainer();

private:
	static std::list<CookieInformation> cookie_container_;
	static ReadWriteMutex read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
