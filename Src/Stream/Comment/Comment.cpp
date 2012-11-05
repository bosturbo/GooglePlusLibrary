#include <Stream/Comment/Comment.hpp>
#include <Stream/Comment/CommentParser/CommentParser.hpp>

#include <luabind/luabind.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

Comment::Comment()
:post_id_(L""),
comment_id_(L""),
comment_author_name_(L""),
comment_time_(),
comment_message_(L""),
comment_author_id_(L""),
comment_author_image_(L""),
is_my_comment_(false),
is_edited_(false),
last_edited_time_(),
read_write_mutex_(make_shared<ReadWriteMutex>())
{
}

wstring Comment::getPostID() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return post_id_;
}

wstring Comment::getCommentID() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return comment_id_;
}

wstring Comment::getCommentAuthorName() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return comment_author_name_;
}

boost::posix_time::ptime Comment::getCommentTime() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return comment_time_;
}

wstring Comment::getCommentMessage() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return comment_message_;
}

wstring Comment::getCommentAuthorID() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return comment_author_id_;
}

wstring Comment::getCommentAuthorImageUrl() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return comment_author_image_;
}

bool Comment::isMyComment() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return is_my_comment_;
}

bool Comment::isEdited() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return is_edited_;
}

boost::posix_time::ptime Comment::getLastEditedTime() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return last_edited_time_;
}

Comment::~Comment()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
