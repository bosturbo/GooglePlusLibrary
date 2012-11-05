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

#include <string>
#include <map>
#include <iosfwd>
#include <boost/signals2.hpp>

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class HttpResponse;
class JsonObject;

/*!
* @~english
* @brief class for connect to the Google+ server(Upper layer)
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief Google+サーバーと通信するためのクラス(上位層)
* @warning このクラスはライブラリ開発者ならびにLuaスクリプト編集者以外利用しないようにしてください
*/
class GOOGLEPLUSLIBRARY_API Connection
{
public:
	Connection();

	/*!
	* @~english
	* @brief Sets the key e-mail address to save the cookie
	* @details you need to call this function, if you want to connect Google+ with the account ID has not been able to get
	* @param mail_address E-mail address associated with a cookie(e.g. hogehoge@gmail.com)
	* @~japanese
	* @brief クッキーの保存キーとなるメールアドレスを設定します
	* @details アカウントIDが取得できていない状態で通信を行う場合はこの関数を呼び出す必要があります
	* @param mail_address クッキーと関連付けるメールアドレス(例: hogehoge@gmail.com)
	*/
	void setCurrentMailAddress(const std::string& mail_address);

	/*!
	* @~english
	* @brief Sets the key account id to save the cookie
	* @param account_id account id associated with a cookie(e.g. 116324207729009185938)
	* @~japanese
	* @brief クッキーの保存キーとなるアカウントIDを設定します
	* @param account_id クッキーと関連付けるアカウントID(例: 116324207729009185938)
	*/
	void setCurrentAccountID(const std::string& account_id);

	/*!
	* @~english
	* @brief Sets the user agent when perform connection
	* @attention User agent is recommended you set this to what the latest version of Google Chrome
	* @param user_agent The user-agent wstring you want to set(e.g. Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.56 Safari/535.11)
	* @~japanese
	* @brief 通信を行う際のユーザーエージェントを設定します
	* @attention ここに設定するユーザーエージェントはGoogle Chromeの最新バージョンのものを推奨いたします
	* @param user_agent 設定したいユーザーエージェント文字列(例: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.56 Safari/535.11)
	*/
	void setUserAgent(const std::string& user_agent);

	/*!
	* @~english
	* @brief Gets the user agent when perform connection
	* @return User-agent wstring is set(e.g. Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.56 Safari/535.11)
	* @~japanese
	* @brief 通信を行う際のユーザーエージェントを取得します
	* @return 設定されているユーザーエージェント文字列(例: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.56 Safari/535.11)
	*/
	std::string getUserAgent() const;

	/*!
	* @~english
	* @brief Set the timeout when connecting
	* @param time_seconds Timeout period (in seconds)
	* @~japanese
	* @brief 通信する際のタイムアウト時間を設定します
	* @param time_seconds タイムアウト時間(秒)
	*/
	void setTimeOut(long time_seconds);

	/*!
	* @~english
	* @brief Get the timeout when connecting
	* @return Timeout period (in seconds)
	* @~japanese
	* @brief 通信する際のタイムアウト時間を取得します
	* @return タイムアウト時間(秒)
	*/
	long getTimeOut() const;

	/*!
	* @~english
	* @brief Connect HTTP GET to the specified url
	* @param url Url you want to connect
	* @param auto_redirect Whether or not to auto-redirect
	* @return Connection result
	* @~japanese
	* @brief httpGet通信を行います
	* @param url 通信先Url
	* @param auto_redirect オートリダイレクトを行うかどうか
	* @return 通信結果
	*/
	HttpResponse httpGet(const std::string& url, bool auto_redirect = false);
	
	/*!
	* @~english
	* @brief Connect HTTP POST to the specified url
	* @param url Url you want to connect
	* @param parameter_pairs Parameters you want to post
	* @return Connection result
	* @~japanese
	* @brief httpPost通信を行います
	* @param url 通信先Url
	* @param parameter_pairs 投稿したいパラメーター
	* @return 通信結果
	*/
	HttpResponse httpPost(const std::string& url, const std::map<std::string, std::string>& parameter_pairs);

	/*!
	* @~english
	* @brief Connect HTTP POST to the specified url
	* @param url Url you want to connect
	* @param parameter Parameters you want to post
	* @return Connection result
	* @~japanese
	* @brief httpPost通信を行います
	* @param url 通信先Url
	* @param parameter 投稿したいパラメーター
	* @return 通信結果
	*/
	HttpResponse httpPost(const std::string& url, const std::string& parameter);

	/*!
	* @~english
	* @brief Connect HTTP POST to the specified url
	* @param url Url you want to connect
	* @param file_stream File you want to post
	* @return Connection result
	* @~japanese
	* @brief httpPost通信を行います
	* @param url 通信先Url
	* @param file_stream 投稿したいファイル
	* @return 通信結果
	*/
	HttpResponse httpPut(const std::string& url, std::ifstream& file_stream);

public:
	/*!
	* @~english
	* @brief create json from connection result wstring
	* @param response Connection result wstring
	* @param replace_to_valid_json Whether or not to fix the result wstring unauthorized connection(Specify the true in most cases)
	* @return Json
	* @~japanese
	* @brief 通信結果文字列からJsonを生成します
	* @param response 通信結果文字列
	* @param replace_to_valid_json 不正な通信結果文字列を修正するかどうか(ほとんどの場合trueを指定します)
	* @return Json
	*/
	JsonObject convertResponseToJson(const std::string& response);

	/*!
	* @~english
	* @brief create json from connection result
	* @param response Connection result
	* @param replace_to_valid_json Whether or not to modify the contents of the invalid connection result(Specify the true in most cases)
	* @return Json
	* @~japanese
	* @brief 通信結果文字列からJsonを生成します
	* @param response 通信結果
	* @param replace_to_valid_json 不正な通信結果の内容を修正するかどうか(ほとんどの場合trueを指定します)
	* @return Json
	*/
	JsonObject convertResponseToJson(const HttpResponse& response);

	static std::string escapeString(std::string source_text);

	static void bindToScript(lua_State* lua_state);

public:
	boost::signals2::signal<void(HttpResponse)> onResponseReceived;

	virtual ~Connection();
private:

	std::string user_agent_;
	long time_out_;
	std::string current_mail_address_;
	std::string current_account_id_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite