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
#pragma warning (disable:4819)
#pragma warning (disable:4996)
#endif
#endif

#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

/*!
* @~english
* @brief Class to get used to obtain information on cookies
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief クッキーの情報を取得するための取得するためのクラス
* @warning このクラスはライブラリ開発者ならびにLuaスクリプト編集者以外利用しないようにしてください
*/
class GOOGLEPLUSLIBRARY_API Cookie
{
	friend class WebClient;
	friend class WebClient;
	friend class HttpResponse;
public:
	Cookie();
protected:
	Cookie(const std::string& url, const std::string& raw_information);
	
public:

	/*!
	* @~english
	* @brief Gets the name of the cookie
	* @return The name of the cookie
	* @~japanese
	* @brief クッキー名を取得します
	* @return クッキー名
	*/
	std::string getName() const;
private:
	std::string name_;

public:
	/*!
	* @~english
	* @brief Gets the value of the cookie
	* @return The value of the cookie
	* @~japanese
	* @brief クッキー値を取得します
	* @return クッキー値
	*/
	std::string getValue() const;
private:
	std::string value_;

public:
	/*!
	* @~english
	* @brief Gets the path for this cookie
	* @return Path of the cookie
	* @~japanese
	* @brief クッキーのパスを取得します
	* @return クッキーのパス
	*/
	std::string getPath() const;
private:
	std::string path_;

public:
	/*!
	* @~english
	* @brief Gets the domain for this cookie
	* @return Domain of the cookie
	* @~japanese
	* @brief クッキーのドメインを取得します
	* @return クッキーのドメイン
	*/
	std::string getDomain() const;
private:
	std::string domain_;

public:
	/*!
	* @~english
	* @brief Gets the expiration of the cookie
	* @return Expiration of the cookie
	* @~japanese
	* @brief クッキーの有効期限を取得します
	* @return クッキーの有効期限
	*/
	boost::posix_time::ptime getExpireTime() const;
private:
	boost::posix_time::ptime expire_posix_time_;
	
public:
	/*!
	* @~english
	* @brief Gets a string representing the expiration of the cookie
	* @return A string representing the expiration of the cookie(e.g. Fri, 22-Apr-2022 12:11:30 GMT)
	* @~japanese
	* @brief クッキーの有効期限を表す文字列を取得します
	* @return クッキーの有効期限を表す文字列(例: Fri, 22-Apr-2022 12:11:30 GMT)
	*/
	std::string getRawExpireTime() const;
private:
	std::string raw_expire_time_;
	
public:
	/*!
	* @~english
	* @brief Gets whether the cookie has expired
	* @return True if the expiration date of the cookie has expired, false if it has not expired
	* @~japanese
	* @brief クッキーの有効期限が切れたかどうかを取得します
	* @return クッキーの有効期限が切れた場合はtrue,切れてない場合はfalse
	*/
	bool isExpired() const;
private:
	bool is_expired_;
	
public:
	/*!
	* @~english
	* @brief Gets whether the cookie is secure
	* @return If true, otherwise false if the cookie is secure
	* @~japanese
	* @brief クッキーがセキュアかどうかを取得します
	* @return クッキーがセキュアならばtrue,そうでない場合はfalse
	*/
	bool isSecure() const;
private:
	bool is_secure_;

public:
	/*!
	* @~english
	* @brief Gets whether the HttpOnly cookies
	* @return If true, otherwise false if the cookie is HttpOnly
	* @~japanese
	* @brief クッキーがHttpオンリーかどうかを取得します
	* @return クッキーがHttpオンリーならばtrue,そうでない場合はfalse
	*/
	bool isHttpOnly() const;
private:
	bool is_http_only_;

public:
	/*!
	* @~english
	* @brief Gets a string of original cookie when you get the information
	* @return When the original string of cookies to retrieve information
	* @~japanese
	* @brief クッキー情報を取得した際のオリジナル文字列を取得します
	* @return クッキー情報を取得した際のオリジナル文字列
	*/
	std::string getRawValue() const;
private:
	std::string raw_information_;

public:
	/*!
	* @~english
	* @brief Gets whether the same cookies with this cookie with the specified
	* @return True, false otherwise if the same cookie
	* @~japanese
	* @brief このクッキーと指定したクッキーが同じかどうかを取得します
	* @return 同じクッキーならばtrue,そうでないならfalse
	*/
	bool isEqual(const Cookie& cookie) const;

	virtual ~Cookie();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
