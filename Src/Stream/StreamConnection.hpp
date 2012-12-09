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

#include <boost/scoped_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/signals2.hpp>

#include <string>

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class StreamConnectionImpl;

/*!
* @~english
* @brief Class to connect to the stream and update
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief ストリームに接続し更新するためのクラス
* @warning このクラスはライブラリ開発者ならびにLuaスクリプト編集者以外利用しないようにしてください
*/
class GOOGLEPLUSLIBRARY_API StreamConnection
{
public:
	StreamConnection();

public:

	/*!
	* @~english
	* @brief Initializes the connection to the stream
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief ストリームへの接続を初期化します
	* @param account_id 対象のアカウントID(例: 116324207729009185938)
	*/
	void initialize(const std::wstring& account_id);

	/*!
	* @~english
	* @brief Initialize the asynchronous connection to the stream
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief ストリームへの接続を非同期で初期化します
	* @param account_id 対象のアカウントID(例: 116324207729009185938)
	*/
	void initializeAsync(const std::wstring& account_id);

	/*!
	* @~english
	* @brief Wait until initialization is complete asynchronous connection to the stream
	* @~japanese
	* @brief ストリームへの接続の非同期初期化が完了するまで待機します
	*/
	void waitInitializeAsync();

private:

	/*!
	* @~english
	* @brief A function that initializes the connection to the stream in a separate thread
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief 別スレッドでストリームへの接続を初期化する関数です
	* @param account_id 対象のアカウントID(例: 116324207729009185938)
	*/
	void initializeAsyncThreadMethod(const std::wstring& account_id);
	boost::thread initialize_thread_;

public:
	boost::signals2::signal<void()> onInitializeSucceed;
	boost::signals2::signal<void()> onInitializeFailed;

public:

	/*!
	* @~english
	* @brief Update the stream
	* @details This function is blocking the thread until logout occurs is called in a separate thread
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief ストリームを更新します
	* @details この関数は別スレッドで呼ばれログアウトが行われるまでそのスレッドをブロッキングします
	* @param account_id 対象のアカウントID(例: 116324207729009185938)
	*/
	void update(const std::wstring& account_id);
private:
	boost::thread update_thread_;

public:
	/*!
	* @~english
	* @brief Abort the update stream
	* @details Blocking of the Update () will be released in good time this function is called
	* @warning This function is implemented please do not use full for outstanding
	* @~japanese
	* @brief ストリームを更新を中止します
	* @details この関数が呼ばれるとキリの良いタイミングでupdate()のブロッキングが解除されます
	* @warning この関数は実装が未完全のため使用しないでください
	*/
	void cancelUpdate();
	
	/*!
	* @~english
	* @brief Gets whether the stream was aborted update
	* @return If it is discontinued, true, false otherwise
	* @~japanese
	* @brief ストリームの更新が中止されたかどうかを取得します
	* @return 中止された場合はtrue,そうでない場合はfalse
	*/
	bool isCanceled();

public:
	int getConnectCount() const;
protected:
	void setConnectCount(int connect_count);

public:
	int getMaximumConnectCount() const;
protected:
	void setMaximumConnectCount(int maximum_connect_count);

public:
	static void bindToScript(lua_State* lua_state);

public:
	virtual ~StreamConnection();

private:
	boost::scoped_ptr<StreamConnectionImpl> impl_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
