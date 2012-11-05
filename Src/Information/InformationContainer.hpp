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
#include <string>
#include <map>
#include <list>

struct PrivateInformation
{
	std::string mail_address;
	std::string account_id;
	std::map<std::string, std::string> informations;
};

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

/*!
* @~english
* @brief Container class in order to be able to access from anywhere in the specified string
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief どこからでも指定の文字列にアクセスできるようにするためのコンテナクラス
* @warning このクラスはライブラリ開発者ならびにLuaスクリプト編集者以外利用しないようにしてください
*/
class GOOGLEPLUSLIBRARY_API InformationContainer : boost::noncopyable
{
public:
	InformationContainer();

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
	* @brief Add the string specified in the list of account information for the specified id
	* @param name The name of the character string you want to add
	* @param value String value of the information you want to add
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief 指定したアカウントIDの文字列情報のリストに指定した文字列を追加します
	* @param name 追加したい文字列情報の名前
	* @param value 追加したい文字列情報の値
	* @param account_id 対象のアカウントID(例: 116324207729009185938)
	*/
	static void addInformationByAccountID(const std::string& name, const std::string& value, const std::string& account_id);
	
	/*!
	* @~english
	* @brief Adds the number specified in the list of account information for the specified id
	* @param name The name of the numerical information you want to add 
	* @param value numeric value of the information you want to add
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief 指定したアカウントIDの数値情報のリストに指定した文字列を追加します
	* @param name 追加したい数値情報の名前
	* @param value 追加したい数値列情報の値
	* @param account_id 対象のアカウントID(例: 116324207729009185938)
	*/
	static void addInformationByAccountID(const std::string& name, const int value, const std::string& account_id);
	
	/*!
	* @~english
	* @brief Add the string specified in the list of account information for the specified mail address
	* @param name The name of the character string you want to add
	* @param value String value of the information you want to add
	* @param mail_address E-mail address of the target(e.g. hogehoge@gmail.com)
	* @~japanese
	* @brief 指定したアカウントIDの文字列情報のリストに指定した文字列を追加します
	* @param name 追加したい文字列情報の名前
	* @param value 追加したい文字列情報の値
	* @param mail_address 対象のメールアドレス(例: hogehoge@gmail.com)
	*/
	static void addInformationByMailAddress(const std::string& name, const std::string& value, const std::string& mail_address);
	
	/*!
	* @~english
	* @brief Adds the number specified in the list of account information for the specified mail address
	* @param name The name of the numerical information you want to add 
	* @param value numeric value of the information you want to add
	* @param mail_address E-mail address of the target(e.g. hogehoge@gmail.com)
	* @~japanese
	* @brief 指定したアカウントIDの数値情報のリストに指定した文字列を追加します
	* @param name 追加したい数値情報の名前
	* @param value 追加したい数値列情報の値
	* @param mail_address 対象のメールアドレス(例: hogehoge@gmail.com)
	*/
	static void addInformationByMailAddress(const std::string& name, const int value, const std::string& mail_address);

	/*!
	* @~english
	* @brief Gets the contents of the information with the specified name from the list of string information for the account ID that you specify
	* @param name The name of the character string you want to get
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief 指定したアカウントIDの文字列情報のリストから指定した名前の情報の内容を取得します
	* @param name 取得したい文字列情報の名前
	* @param account_id 対象のアカウントID(例: 116324207729009185938)
	*/
	static std::string getInformationByAccountID(const std::string& name, const std::string& account_id);

	/*!
	* @~english
	* @brief Gets the contents of the information with the specified name from the list of string information for the email address that you specify
	* @param name The name of the character string you want to get
	* @param mail_address E-mail address of the target(e.g. hogehoge@gmail.com)
	* @~japanese
	* @brief 指定したメールアドレスの文字列情報のリストから指定した名前の情報の内容を取得します
	* @param name 取得したい文字列情報の名前
	* @param mail_address 対象のメールアドレス(例: hogehoge@gmail.com)
	*/
	static std::string getInformationByMailAddress(const std::string& name, const std::string& mail_address);

	/*!
	* @~english
	* @brief Initialize the list of string information for the specified account id
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief 指定したアカウントIDの文字列情報のリストを初期化します
	* @param account_id 対象のアカウントID(例: 116324207729009185938)
	*/
	static void clearInformationByAccountID(const std::string& account_id);

	/*!
	* @~english
	* @brief Initialize the list of string information for the specified e-mail address
	* @param mail_address E-mail address of the target(e.g. hogehoge@gmail.com)
	* @~japanese
	* @brief 指定したメールアドレスの文字列情報のリストを初期化します
	* @param mail_address 対象のメールアドレス(例: hogehoge@gmail.com)
	*/
	static void clearInformationByMailAddress(const std::string& mail_address);

	/*!
	* @~english
	* @brief Initialize the list of string information for all accounts
	* @~japanese
	* @brief すべてのアカウントの文字列情報のリストを初期化します
	*/
	static void clearAllInformation();

	static void bindToScript(lua_State* lua_state);

	virtual ~InformationContainer();

private:

	static std::list<PrivateInformation> information_container;
	static ReadWriteMutex read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
