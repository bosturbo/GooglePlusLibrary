#include <Stream/Comment/CommentSetter.hpp>

#include <Utility/Utility.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

CommentSetter::CommentSetter()
{
}

void CommentSetter::setPostID(const string& post_id)
{
	setPostID(Utility::convertUTF8ToUnicode(post_id));
}

void CommentSetter::setPostID(const wstring& post_id)
{
	post_id_(comment_) = post_id;
}

void CommentSetter::setCommentID(const string& comment_id)
{
	setCommentID(Utility::convertUTF8ToUnicode(comment_id));
}

void CommentSetter::setCommentID(const wstring& comment_id)
{
	comment_id_(comment_) = comment_id;
}

void CommentSetter::setCommentAuthorName(const string& comment_author_name)
{
	setCommentAuthorName(Utility::convertUTF8ToUnicode(comment_author_name));
}

void CommentSetter::setCommentAuthorName(const wstring& comment_author_name)
{
	comment_author_name_(comment_) = comment_author_name;
}

void CommentSetter::setCommentTime(const boost::posix_time::ptime& comment_time)
{
	comment_time_(comment_) = comment_time;
}

void CommentSetter::setCommentMessage(const string& comment_message)
{
	setCommentMessage(Utility::convertUTF8ToUnicode(comment_message));
}

void CommentSetter::setCommentMessage(const wstring& comment_message)
{
	comment_message_(comment_) = comment_message;
}

void CommentSetter::setCommentAuthorID(const string& comment_author_id)
{
	setCommentAuthorID(Utility::convertUTF8ToUnicode(comment_author_id));
}

void CommentSetter::setCommentAuthorID(const wstring& comment_author_id)
{
	comment_author_id_(comment_) = comment_author_id;
}

void CommentSetter::setCommentAuthorImageUrl(const string& comment_author_image)
{
	setCommentAuthorImageUrl(Utility::convertUTF8ToUnicode(comment_author_image));
}

void CommentSetter::setCommentAuthorImageUrl(const wstring& comment_author_image)
{
	comment_author_image_(comment_) = comment_author_image;
}

void CommentSetter::setIsMyComment(bool is_my_comment)
{
	is_my_comment_(comment_) = is_my_comment;
}

void CommentSetter::setIsEdited(bool is_edited)
{
	is_edited_(comment_) = is_edited;
}

void CommentSetter::setLastEditedTime(const boost::posix_time::ptime& last_edited_time)
{
	last_edited_time_(comment_) = last_edited_time;
}

Comment CommentSetter::toComment()
{
	return comment_;
}

void CommentSetter::bindToScript(lua_State* lua_state)
{
	module(lua_state)
		[
			class_<CommentSetter>("CommentSetter")
			.def(constructor<>())
			.def("setPostID", static_cast<void(CommentSetter::*)(const string&)>(&CommentSetter::setPostID))
			.def("setCommentID", static_cast<void(CommentSetter::*)(const string&)>(&CommentSetter::setCommentID))
			.def("setCommentAuthorName", static_cast<void(CommentSetter::*)(const string&)>(&CommentSetter::setCommentAuthorName))
			.def("setCommentTime", &CommentSetter::setCommentTime)
			.def("setCommentMessage", static_cast<void(CommentSetter::*)(const string&)>(&CommentSetter::setCommentMessage))
			.def("setCommentAuthorID", static_cast<void(CommentSetter::*)(const string&)>(&CommentSetter::setCommentAuthorID))
			.def("setCommentAuthorImageUrl", static_cast<void(CommentSetter::*)(const string&)>(&CommentSetter::setCommentAuthorImageUrl))
			.def("setIsMyCommentSetter", &CommentSetter::setIsMyComment)
			.def("setIsEdited", &CommentSetter::setIsEdited)
			.def("setLastEditedTime", &CommentSetter::setLastEditedTime)
		];
}

CommentSetter::~CommentSetter()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite