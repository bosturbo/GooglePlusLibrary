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

class MyAccountImpl;
class Account;
class AddedAccountList;
class AddedYouAccountList;
class talkgadgetConnection;
class LuaConnection;
class ShareRangeList;
class AttachedAlbum;
class AttachedCircle;
class AttachedImageVideo;
class AttachedSearchResult;
class AttachedUrl;
class AttachedYouTubePlaylist;
class Stream;

/*!
* @~english
* @brief Class that will be used to share post or login to Google+
* @~japanese
* @brief Google+にログインしたり投稿するために使われるクラス
*/
class GOOGLEPLUSLIBRARY_API MyAccount
{
	friend LuaConnection;

public:
	MyAccount();

public:

	/*!
	* @~english
	* @brief login to Google+
	* @param mail_address E-mail address of the account(e.g. hogehoge@gmail.com or hogehoge)
	* @param password The password for the account
	* @~japanese
	* @brief Google+にログインします
	* @param mail_address アカウントのメールアドレス(例: hogehoge@gmail.com もしくはhogehoge)
	* @param password アカウントのパスワード
	*/
	void login(const std::wstring& mail_address, const std::wstring& password);

	/*!
	* @~english
	* @brief Asynchronous login to Google+
	* @param mail_address E-mail address of the account(e.g. hogehoge@gmail.com or hogehoge)
	* @param password The password for the account
	* @~japanese
	* @brief Google+に非同期ログインします
	* @param mail_address アカウントのメールアドレス(例: hogehoge@gmail.com もしくはhogehoge)
	* @param password アカウントのパスワード
	*/
	void loginAsync(const std::wstring& mail_address, const std::wstring& password);
	
	/*!
	* @~english
	* @brief Wait asynchronous login to Google+
	* @~japanese
	* @brief 非同期ログインが完了するまで待機します
	*/
	void waitLoginAsync();

	boost::signals2::signal<void()> onLoginCompleted;

private:
	void loginAsyncThreadMethod(const std::wstring& mail_address, const std::wstring& password);
	boost::thread login_thread_;
	std::shared_ptr<talkgadgetConnection> talkgadget_connection_;

public:

	/*!
	* @~english
	* @brief Get accout id
	* @return account id(e.g. 116324207729009185938)
	* @~japanese
	* @brief アカウントIDを取得します
	* @return アカウントID(例: 116324207729009185938)
	*/
	std::wstring getAccountID() const;

	/*!
	* @~english
	* @brief Get accout mailaddress
	* @return account mailaddress(e.g. hogehoge@gmail.com)
	* @~japanese
	* @brief アカウントメールアドレスを取得します
	* @return アカウントメールアドレス(例: hogehoge@gmail.com)
	*/
	std::wstring getMailAddress() const;
private:
	std::wstring mail_address_;

public:
	/*!
	* @~english
	* @brief Gets the name of the account
	* @return Account name
	* @~japanese
	* @brief アカウント名を取得します
	* @return アカウント名
	*/
	std::wstring getAccountName() const;
	
	void sharePost(const std::wstring& message, const ShareRangeList& share_range,
		std::shared_ptr<AttachedSearchResult> attached_search_result = nullptr);

	void sharePost(const std::wstring& message, const ShareRangeList& share_range, const AttachedAlbum& attached_album,
		std::shared_ptr<AttachedSearchResult> attached_search_result = nullptr);

	void sharePost(const std::wstring& message, const ShareRangeList& share_range, const AttachedCircle& attached_circle,
		std::shared_ptr<AttachedSearchResult> attached_search_result = nullptr);

	void sharePost(const std::wstring& message, const ShareRangeList& share_range, const AttachedImageVideo& attached_image_video,
		std::shared_ptr<AttachedSearchResult> attached_search_result = nullptr);

	void sharePost(const std::wstring& message, const ShareRangeList& share_range, const AttachedSearchResult& attached_search_result);

	void sharePost(const std::wstring& message, const ShareRangeList& share_range, const AttachedUrl& attached_url,
		std::shared_ptr<AttachedSearchResult> attached_search_result = nullptr);

	void sharePost(const std::wstring& message, const ShareRangeList& share_range, const AttachedYouTubePlaylist& attached_youtube_playlist,
		std::shared_ptr<AttachedSearchResult> attached_search_result = nullptr);
	
public:
	/*!
	* @~english
	* @brief Gets the list of accounts you have added to the circle
	* @return List of accounts you have added to the circle
	* @~japanese
	* @brief あなたがサークルに追加したアカウントのリストを取得します
	* @return あなたがサークルに追加したアカウントのリスト
	*/
	AddedAccountList* getAddedAccountList() const;

	/*!
	* @~english
	* @brief Gets the list of accounts that you have added to the circle you
	* @return List of accounts that you have added to the circle you
	* @~japanese
	* @brief あなたをサークルに追加したアカウントのリストを取得します
	* @return あなたをサークルに追加したアカウントのリスト
	*/
	AddedYouAccountList* getAddedYouAccountList() const;

	Stream* getMainStream() const;

	/*!
	* @~english
	* @brief Cast as a Account class
	* @return Account class
	* @~japanese
	* @brief Account型クラスとしてキャストします
	* @return Account型としてキャストされたアカウント情報
	*/
	const Account* toAccount();

public:
	virtual ~MyAccount();

private:
	std::shared_ptr<MyAccountImpl> impl_;
};

} // namespace GooglePlusLibrary
} // namespace Gplusnasite
