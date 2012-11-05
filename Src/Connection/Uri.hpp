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

#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

/*!
* @~english
* @brief Class to get the url information
* @~japanese
* @brief Url情報を取得するためのクラス
*/
class GOOGLEPLUSLIBRARY_API Uri
{
public:
	Uri(const std::string& url);

	/*!
	* @~english
	* @brief Gets the scheme of the url
	* @return Scheme of the url
	* @~japanese
	* @brief Urlのスキームを取得します
	* @return Urlのスキーム
	*/
	std::string getScheme() const;

	/*!
	* @~english
	* @brief Gets the Authority(IP address or DNS host name of the server) of the Url
	* @return Authority of the Url
	* @~japanese
	* @brief UrlのAuthority(サーバーのDNSホスト名またはIPアドレス)を取得します
	* @return UrlのAuthority
	*/
	std::string getAuthority() const;

	/*!
	* @~english
	* @brief Gets the user of the Url
	* @return User of Url
	* @~japanese
	* @brief Urlのユーザーを取得します
	* @return Urlのユーザー
	*/
	std::string getUser() const;

	/*!
	* @~english
	* @brief Gets the host of the Url
	* @return Host of Url
	* @~japanese
	* @brief Urlのホストを取得します
	* @return Urlのホスト
	*/
	std::string getHost() const;

	/*!
	* @~english
	* @brief Gets the port of the Url
	* @todo To be able to get the port number from the scheme even if the port is not listed
	* @return Port of Url
	* @~japanese
	* @brief Urlのポートを取得します
	* @todo ポートが記載されていない場合でもスキームからポート番号を取得できるようにする
	* @return Urlのポート
	*/
	int getPort() const;

	/*!
	* @~english
	* @brief Gets the path of the Url
	* @return Path of Url
	* @~japanese
	* @brief Urlのパスを取得します
	* @return Urlのパス
	*/
	std::string getPath() const;

	/*!
	* @~english
	* @brief Gets the query of the Url
	* @return Query of Url
	* @~japanese
	* @brief Urlのクエリを取得します
	* @return Urlのクエリ
	*/
	std::string getQuery() const;

	/*!
	* @~english
	* @brief Gets the fragment of the Url
	* @return Fragment of Url
	* @~japanese
	* @brief Urlのフラグメントを取得します
	* @return Urlのフラグメント
	*/
	std::string getFragment() const;

	virtual ~Uri();

private:
	std::string scheme;
	std::string authority;
	std::string user;
	std::string host;
	int         port;
	std::string path;
	std::string query;
	std::string fragment;
};

} // namespace GooglePlusLibrary
} // namespace Gplusnasite
