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

#include <boost/date_time/posix_time/posix_time.hpp>

#include <string>

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class CommentParser;
class JsonObject;
class ReadWriteMutex;

/*!
* @~english
* @brief Class for operating comment information
* @~japanese
* @brief コメントを操作するためのクラス
*/
class GOOGLEPLUSLIBRARY_API Comment
{
	friend class CommentBase;
public:
	Comment();

	/*!
	* @~english
	* @brief Gets the post ID of this comment has been posted
	* @return the post ID of this comment has been posted(e.g. z12jxbmyulblgnudc232srv5iw3futrdp)
	* @~japanese
	* @brief このコメントがされている投稿のIDを取得します
	* @return このコメントがされている投稿のID(例: z12jxbmyulblgnudc232srv5iw3futrdp)
	*/
	std::wstring getPostID() const;
private:
	std::wstring post_id_;

public:
	/*!
	* @~english
	* @brief Gets the comment ID of this comment
	* @return the comment ID of this comment(e.g. z12jxbmyulblgnudc232srv5iw3futrdp#1335189462073143)
	* @~japanese
	* @brief このコメントのIDを取得します
	* @return このコメントがされている投稿のID(例: z12jxbmyulblgnudc232srv5iw3futrdp#1335189462073143)
	*/
	std::wstring getCommentID() const;
private:
	std::wstring comment_id_;

public:
	/*!
	* @~english
	* @brief Gets the name of the user who posted this comment
	* @return the name of the user who posted this comment
	* @~japanese
	* @brief このコメントを投稿したユーザーの名前を取得します
	* @return このコメントを投稿したユーザーの名前
	*/
	std::wstring getCommentAuthorName() const;
private:
	std::wstring comment_author_name_;

public:
	boost::posix_time::ptime getCommentTime() const;
private:
	boost::posix_time::ptime comment_time_;

public:
	/*!
	* @~english
	* @brief Gets the message of comments
	* @return The message of comments
	* @~japanese
	* @brief コメントメッセージを取得します
	* @return コメントメッセージ
	*/
	std::wstring getCommentMessage() const;
private:
	std::wstring comment_message_;

public:
	/*!
	* @~english
	* @brief Gets the id of the user who posted this comment
	* @return the id of the user who posted this comment
	* @~japanese
	* @brief このコメントを投稿したユーザーのIDを取得します
	* @return このコメントを投稿したユーザーのID
	*/
	std::wstring getCommentAuthorID() const;
private:
	std::wstring comment_author_id_;

public:
	/*!
	* @~english
	* @brief Gets the url of the account image of account who posted this comment
	* @return the url of the account image of account who posted this comment
	* @~japanese
	* @brief このコメントを投稿したユーザーのアカウント画像のUrlを取得します
	* @return このコメントを投稿したユーザーのアカウント画像のUrl
	*/
	std::wstring getCommentAuthorImageUrl() const;
private:
	std::wstring comment_author_image_;

public:
	/*!
	* @~english
	* @brief Gets whether or not own comment
	* @return Whether own comment
	* @~japanese
	* @brief 自分の投稿かどうかを取得します
	* @return 自分の投稿かどうか
	*/
	bool isMyComment() const;
private:
	bool is_my_comment_;

public:
	/*!
	* @~english
	* @brief Get is comment edited
	* @return Is comment edited
	* @~japanese
	* @brief コメントが編集されているかどうかを取得します
	* @return コメントが編集されているかどうか
	*/
	bool isEdited() const;
private:
	bool is_edited_;

public:
	boost::posix_time::ptime getLastEditedTime() const;
private:
	boost::posix_time::ptime last_edited_time_;

public:
	virtual ~Comment();

private:
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
