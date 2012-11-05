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

#include <memory>
#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class MyAccount;
class MyPageAccount;
class JsonObject;
class ReadWriteMutex;

/*!
* @~english
* @brief Class to generate the information when added url to share post and to get information when the url has been attached to the post
* @~japanese
* @brief 投稿に付加されているUrl情報を取得したり、Url付加投稿をシェアするときの情報を生成するためのクラス
*/
class GOOGLEPLUSLIBRARY_API AttachedUrl
{
	friend class AttachedUrlBase;
public:
	AttachedUrl();

	/*!
	* @~english
	* @brief create AttachedUrl(No thumbnail)
	* @details If it fails to generate returns null
	* @param account_id account id(e.g. 116324207729009185938)
	* @param url Url to be added to post
	* @~japanese
	* @brief パラメーターからAttachedUrlを作成します(サムネイルは付加しない)
	* @details 生成に失敗した場合はnullを返します
	* @param account_id アカウントID(例: 116324207729009185938)
	* @param url 投稿に付加するUrl
	*/
	static AttachedUrl* create(const std::wstring& account_id, const std::wstring& url);

	/*!
	* @~english
	* @brief create AttachedUrl(No thumbnail)
	* @details If it fails to generate returns null
	* @param my_account my account that posts this information
	* @param url Url to be added to post
	* @~japanese
	* @brief パラメーターからAttachedUrlを作成します(サムネイルは付加しない)
	* @details 生成に失敗した場合はnullを返します
	* @param my_account 投稿を行う自分のアカウント
	* @param url 投稿に付加するUrl
	*/
	static AttachedUrl* create(const MyAccount& my_account, const std::wstring& url);

	/*!
	* @~english
	* @brief create AttachedUrl(No thumbnail)
	* @details If it fails to generate returns null
	* @param my_page_account my account that posts this information
	* @param url Url to be added to post
	* @~japanese
	* @brief パラメーターからAttachedUrlを作成します(サムネイルは付加しない)
	* @details 生成に失敗した場合はnullを返します
	* @param my_page_account 投稿を行う自分のアカウント
	* @param url 投稿に付加するUrl
	*/
	static AttachedUrl* create(const MyPageAccount& my_page_account, const std::wstring& url);

	/*!
	* @~english
	* @brief create AttachedUrl
	* @details If it fails to generate returns null
	* @param account_id account id(e.g. 116324207729009185938)
	* @param url Url to be added to post
	* @param thumbnail_number the position of the thumbnail that when share posts(0 start)
	* @~japanese
	* @brief パラメーターからAttachedUrlを作成します
	* @details 生成に失敗した場合はnullを返します
	* @param account_id アカウントID(例: 116324207729009185938)
	* @param url 投稿に付加するUrl
	* @param thumbnail_number 投稿時に設定するサムネイルの位置(0スタート)
	*/
	static AttachedUrl* create(const std::wstring& account_id, const std::wstring& url, int thumbnail_number);

	/*!
	* @~english
	* @brief create AttachedUrl
	* @details If it fails to generate returns null
	* @param my_account My account that posts this information
	* @param url Url to be added to post
	* @param thumbnail_number the position of the thumbnail that when share posts(0 start)
	* @~japanese
	* @brief パラメーターからAttachedUrlを作成します
	* @details 生成に失敗した場合はnullを返します
	* @param my_account 投稿を行う自分のアカウント
	* @param url 投稿に付加するUrl
	* @param thumbnail_number 投稿時に設定するサムネイルの位置(0スタート)
	*/
	static AttachedUrl* create(const MyAccount& my_account, const std::wstring& url, int thumbnail_number);

	/*!
	* @~english
	* @brief create AttachedUrl
	* @details If it fails to generate returns null
	* @param my_page_account My account that posts this information
	* @param url Url to be added to post
	* @param thumbnail_number the position of the thumbnail that when share posts(0 start)
	* @~japanese
	* @brief パラメーターからAttachedUrlを作成します
	* @details 生成に失敗した場合はnullを返します
	* @param my_page_account 投稿を行う自分のアカウント
	* @param url 投稿に付加するUrl
	* @param thumbnail_number 投稿時に設定するサムネイルの位置(0スタート)
	*/
	static AttachedUrl* create(const MyPageAccount& my_page_account, const std::wstring& url, int thumbnail_number);

public:
	std::wstring getPageTitle() const;
private:
	std::wstring page_title_;

public:
	std::wstring getPageDescription() const;
private:
	std::wstring page_description_;

public:
	std::wstring getPageFaviconUrl() const;
private:
	std::wstring page_favicon_url_;

public:
	std::wstring getPageUrl() const;
private:
	std::wstring page_url_;

public:
	/*!
	* @~english
	* @brief Get Thumbnail image Url is set
	* @return Thumbnail image Url is set
	* @~japanese
	* @brief 設定されているサムネイル画像Urlを取得します
	* @return 設定されているサムネイル画像Url
	*/
	std::wstring getThumbnailUrl() const;
private:
	std::wstring thumbnail_url_;

public:

	/*!
	* @~english
	* @brief Get the position of the image thumbnail is set
	* @return The position of the image thumbnail is set
	* @~japanese
	* @brief 設定されているサムネイル画像の位置を取得します
	* @return 設定されているサムネイル画像の位置
	*/
	int getThumbnailPosition() const;

	/*!
	* @~english
	* @brief Set the position of the thumbnail images
	* @param thumbnail_position The position of the image thumbnail is set to post(0 start)
	* @~japanese
	* @brief サムネイル画像の位置を設定します
	* @param thumbnail_position 投稿に設定するサムネイル画像の位置(0スタート)
	*/
	void setThumbnailPosition(int thumbnail_position);
private:
	int thumbnail_position_;
	
public:
	virtual ~AttachedUrl();

private:
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
