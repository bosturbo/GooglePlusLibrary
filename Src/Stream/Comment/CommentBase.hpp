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

#include <Stream/Comment/Comment.hpp>
#include <Thread/ReadWriteMutex.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API CommentBase
{
public:
	CommentBase()
	{
	}

protected:

	static std::wstring& post_id_(Comment& comment)
	{
		return comment.post_id_;
	}

	static std::wstring& comment_id_(Comment& comment)
	{
		return comment.comment_id_;
	}

	static std::wstring& comment_author_name_(Comment& comment)
	{
		return comment.comment_author_name_;
	}

	static boost::posix_time::ptime& comment_time_(Comment& comment)
	{
		return comment.comment_time_;
	}

	static std::wstring& comment_message_(Comment& comment)
	{
		return comment.comment_message_;
	}

	static std::wstring& comment_author_id_(Comment& comment)
	{
		return comment.comment_author_id_;
	}

	static std::wstring& comment_author_image_(Comment& comment)
	{
		return comment.comment_author_image_;
	}

	static bool& is_my_comment_(Comment& comment)
	{
		return comment.is_my_comment_;
	}

	static bool& is_edited_(Comment& comment)
	{
		return comment.is_edited_;
	}

	static boost::posix_time::ptime& last_edited_time_(Comment& comment)
	{
		return comment.last_edited_time_;
	}

	static std::shared_ptr<ReadWriteMutex>& read_write_mutex_(Comment& comment)
	{
		return comment.read_write_mutex_;
	}

public:
	virtual ~CommentBase()
	{
	}
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite