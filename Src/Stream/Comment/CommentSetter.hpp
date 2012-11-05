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

#include <Stream/Comment/CommentBase.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API CommentSetter : public CommentBase
{
public:
	CommentSetter();

	void setPostID(const std::string& post_id);
	void setPostID(const std::wstring& post_id);

	void setCommentID(const std::string& comment_id);
	void setCommentID(const std::wstring& comment_id);

	void setCommentAuthorName(const std::string& comment_author_name);
	void setCommentAuthorName(const std::wstring& comment_author_name);

	void setCommentTime(const boost::posix_time::ptime& comment_time);

	void setCommentMessage(const std::string& comment_message);
	void setCommentMessage(const std::wstring& comment_message);

	void setCommentAuthorID(const std::string& comment_author_id);
	void setCommentAuthorID(const std::wstring& comment_author_id);

	void setCommentAuthorImageUrl(const std::string& comment_author_image);
	void setCommentAuthorImageUrl(const std::wstring& comment_author_image);
	void setIsMyComment(bool is_my_comment);
	void setIsEdited(bool is_edited);
	void setLastEditedTime(const boost::posix_time::ptime& last_edited_time);
	static void bindToScript(lua_State* lua_state);

	Comment toComment();

	virtual ~CommentSetter();
private:
	Comment comment_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite