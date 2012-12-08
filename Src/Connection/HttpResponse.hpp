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

#include <string>
#include <map>
#include <list>

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Cookie;

/*!
* @~english
* @brief Class of connection to get the results
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief 通信結果を取得するためのクラス
* @warning このクラスはライブラリ開発者ならびにLuaスクリプト編集者以外利用しないようにしてください
*/
class GOOGLEPLUSLIBRARY_API HttpResponse
{
	friend class Connection;
	friend class WebClient;
	friend class WebClientCppNetlib;

public:
	HttpResponse();

protected:
	HttpResponse(const std::string& url, int status_code, const std::map<std::string, std::string>& response_header, 
		const std::list<Cookie>& response_cookie, 
		const std::string& response_body);
	
public:
	std::string getUrl() const;
private:
	std::string url_;

public:
	int getStatusCode();

private:
	int status_code_;

public:
	/*!
	* @~english
	* @brief Gets the response body
	* @return The response body string has been set
	* @~japanese
	* @brief レスポンスボディを取得します
	* @return 設定されたレスポンスボディ文字列
	*/
	std::string getResponseBody() const;
protected:

	/*!
	* @~english
	* @brief Sets the response body
	* @param response_body Response body string you want to set
	* @~japanese
	* @brief レスポンスボディを設定します
	* @param response_body 設定したいレスポンスボディ文字列
	*/
	void setResponseBody(const std::string& response_body);
private:
	std::string response_body_;

public:

	/*!
	* @~english
	* @brief Displays to standard output a list of response cookies names and values 
	* @~japanese
	* @brief レスポンスクッキーについて名前と値の一覧を標準出力に表示します
	*/
	void showResponseCookies();
	
public:
	/*!
	* @~english
	* @brief Gets a list of response cookies
	* @return List of response cookies
	* @~japanese
	* @brief レスポンスクッキーのリストを取得します
	* @return レスポンスクッキーのリスト
	*/
	std::list<Cookie> getResponseCookies() const;

	/*!
	* @~english
	* @brief Gets the value of the cookie from the response cookie with the specified name
	* @details Returns the empty string if the cookie the same as the name specified was not found
	* @return The same as the value of the cookie with the given name
	* @~japanese
	* @brief レスポンスクッキーから指定した名前のクッキーの値を取得します
	* @details 指定した名前と同じクッキーが見つからなかった場合空文字を返します
	* @return 指定した名前と同じクッキーの値
	*/
	std::string getResponseCookie(const std::string& name);
protected:

	/*!
	* @~english
	* @brief Sets the list of cookies in the response cookie
	* @param cookies List of cookies you want to set
	* @~japanese
	* @brief レスポンスクッキーにクッキーのリストを設定します
	* @param cookies 設定したいクッキーのリスト
	*/
	void setResponseCookies(const std::list<Cookie>& cookies);
private:
	std::list<Cookie> response_cookie_;

public:

	/*!
	* @~english
	* @brief Gets the map of the response header
	* @return Map of the response header is set
	* @~japanese
	* @brief レスポンスヘッダのマップを取得します
	* @return 設定されたレスポンスヘッダのマップ
	*/
	std::map<std::string, std::string> getResponseHeaderValues() const;

	/*!
	* @~english
	* @brief Gets the value of the header from the response header with the specified name
	* @details Returns the empty string if the header the same as the name specified was not found
	* @param name The name of the header you want to get
	* @return The same as the value of the header with the given name
	* @~japanese
	* @brief レスポンスヘッダから指定した名前のヘッダの値を取得します
	* @details 指定した名前と同じヘッダが見つからなかった場合空文字を返します
	* @param name 取得したいヘッダの名前
	* @return 指定した名前と同じヘッダの値
	*/
	std::string getResponseHeaderValue(const std::string& name) const;
protected:

	/*!
	* @~english
	* @brief Sets the list of headers in the response header
	* @param headers List of headers you want to set
	* @~japanese
	* @brief レスポンスヘッダにヘッダのリストを設定します
	* @param headers 設定したいヘッダのリスト
	*/
	void setResponseHeader(std::map<std::string, std::string> headers);
private:
	std::map<std::string, std::string> response_header_;

public:
	std::string getRedirectUrl();
private:
	std::string redirect_url_;

public:
	static void bindToScript(lua_State* lua_state);

public:
	virtual ~HttpResponse();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite