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

#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class AttachedAlbum;
class AttachedCircle;
class AttachedImageVideo;
class AttachedLocation;
class AttachedUrl;
class AttachedYouTubePlaylist;

/*!
* @~english
* @brief Class in order to share a post
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief 投稿をシェアするためのクラス
* @warning このクラスはライブラリ開発者ならびにLuaスクリプト編集者以外利用しないようにしてください
*/
class GOOGLEPLUSLIBRARY_API postMessageSender
{
public:
	postMessageSender();

	/*!
	* @~english
	* @brief Creating a post in what has been specified and share it
	* @param message Message content of the post
	* @~japanese
	* @brief 指定された内容で投稿を作成しシェアします
	* @param message 投稿のメッセージ内容
	*/
	void share(const std::wstring& message);

	void share(const std::wstring& message, const AttachedAlbum& attached_album);

	void share(const std::wstring& message, const AttachedCircle& attached_circle);

	virtual ~postMessageSender();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite