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

#include <Stream/Post/PostSetter.hpp>

#include <string>
#include <queue>

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class JsonObject;

/*!
* @~english
* @brief Class to convert a Json to a Post
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief Jsonを投稿クラスに変換するためのクラス
* @warning このクラスはライブラリ開発者ならびにLuaスクリプト編集者以外利用しないようにしてください
*/
class GOOGLEPLUSLIBRARY_API PostParser
{
public:
	PostParser();

	/*!
	* @~english
	* @brief Converts Json to Post and update the post list(Stream) of all applicable
	* @param json Json comment information is stored
	* @~japanese
	* @brief JsonをPostクラスに変換し、該当するすべての投稿リスト(ストリーム)を更新します
	* @param json 投稿情報が格納されているJson
	*/
	static void add(JsonObject& json);

	/*!
	* @~english
	* @brief removes the specified ID from the post list(Stream) of all applicable
	* @param post_id ID of the post has been deleted(e.g. z12jxbmyulblgnudc232srv5iw3futrdp)
	* @~japanese
	* @brief 指定されたIDの投稿を該当するすべての投稿リスト(ストリーム)から削除します
	* @param post_id 削除された投稿のID(例: z12jxbmyulblgnudc232srv5iw3futrdp)
	*/
	static void erase(const std::string& post_id);
	static void erase(const std::wstring& post_id);

public:
	static void bindToScript(lua_State* lua_state);

public:
	virtual ~PostParser();

private:
	static std::queue<Post> post_info_queue;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
