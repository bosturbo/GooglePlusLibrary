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

#include <boost/network/protocol/http/client.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/range/iterator_range.hpp>

#include <string>
#include <map>
#include <list>
#include <iosfwd>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Cookie;
class HttpResponse;

/*!
* @~english
* @brief Class for connection(lower layer)
* @details This class supports the https connection
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief 通信を行うためのクラス(下位層)
* @details このクラスはhttps通信に対応しています
* @warning このクラスはライブラリ開発者ならびにLuaスクリプト編集者以外利用しないようにしてください
*/
class GOOGLEPLUSLIBRARY_API WebClientCppNetlib
{
public:
	WebClientCppNetlib();
	WebClientCppNetlib(const std::string& url);
private:
	std::string url_;
public:
	void setCurrentMailAddress(const std::string& mail_address);
	void setCurrentAccountID(const std::string& account_id);
private:
	std::string current_mail_address_;
	std::string current_account_id_;
public:
	void function_name(boost::iterator_range<const char*> const & range_name, boost::system::error_code const & error_name);
private:
	std::string body_;
public:
	HttpResponse get();
	HttpResponse getStreaming();
	HttpResponse post(const std::string& parameter);
	HttpResponse put(std::ifstream& file_stream);

protected:
	void setRequestSetting(boost::network::http::client::request& request);
	
public:
	/*!
	* @~english
	* @brief Sets the user agent when perform connection
	* @param user_agent The user-agent string you want to set(e.g. Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.56 Safari/535.11)
	* @~japanese
	* @brief 通信を行う際のユーザーエージェントを設定します
	* @param user_agent 設定したいユーザーエージェント文字列(例: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.56 Safari/535.11)
	*/
	void setUserAgent(const std::string& user_agent);
private:
	std::string user_agent_;
		
public:
	/*!
	* @~english
	* @brief Adds a parameter to the request header
	* @param name The name of the parameter you want to add
	* @param value Value of the parameter you want to add
	* @~japanese
	* @brief リクエストヘッダーにパラメーターを追加します
	* @param name 追加したいパラメーターの名前
	* @param value 追加したいパラメーターの値
	*/
	void addHeader(const std::string& name, const std::string& value);

	/*!
	* @~english
	* @brief Adds a parameter to the request header
	* @param name_value_pairs Parameter you want to add
	* @~japanese
	* @brief リクエストヘッダーにパラメーターを追加します
	* @param name_value_pairs 追加したいパラメーター
	*/
	void addHeader(const std::map<std::string, std::string>& name_value_pairs);
private:
	std::map<std::string, std::string> request_headers_;
public:
	/*!
	* @~english
	* @brief Add the specified cookie to the request cookie
	* @param cookie Cookie you want to add
	* @~japanese
	* @brief リクエストクッキーに指定したクッキーを追加します
	* @param cookie 追加したいクッキー
	*/
	void addRequestCookie(const Cookie& cookie);

	void setRequestCookies();
	void setRequestCookies(const std::list<Cookie>& cookies);
	void setResponseCookies();
private:
	std::list<Cookie> request_cookies_;
	std::list<Cookie> response_cookies_;
public:
	~WebClientCppNetlib();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite