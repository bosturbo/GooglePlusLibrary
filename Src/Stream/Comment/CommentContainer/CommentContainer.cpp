#include <Stream/Comment/CommentContainer/CommentContainer.hpp>
#include <Stream/Comment/Comment.hpp>
#include <Stream/Comment/CommentList/CommentList.hpp>
#include <Stream/Post/PostContainer/PostContainer.hpp>
#include <Stream/Post/Post.hpp>
#include <Utility/Utility.hpp>
#include <Utility/LuaScript.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

boost::signals2::signal<void (const Comment&)> CommentContainer::onCommentinserted;
boost::signals2::signal<void (const Comment&)> CommentContainer::onCommentEdited;
boost::signals2::signal<void (const wstring&)> CommentContainer::onCommentDeleted;

map<wstring, Comment> CommentContainer::comment_container_;
ReadWriteMutex CommentContainer::read_write_mutex_;

CommentContainer::CommentContainer()
{
}

bool CommentContainer::insert(const Comment& comment)
{
	wstring comment_id = comment.getCommentID();
	if(comment_id.empty())
	{
		return false;
	}

	{
		ScopedWriteLock lock(read_write_mutex_);
		auto result = comment_container_.insert(map<wstring, Comment>::value_type(comment_id, comment));
		if(result.second)
		{
			onCommentinserted(comment);
			return true;
		}
	}
	
	if(comment.isEdited())
	{
		// added edited comment
		updateItem(comment);
		onCommentEdited(comment);
		return true;
	}
	return false;
}

void CommentContainer::updateItem(const Comment& comment)
{
	{
		ScopedWriteLock lock(read_write_mutex_);
		comment_container_[comment.getCommentID()] = comment;
	}
}

bool CommentContainer::erase(const wstring& comment_id)
{
	{
		ScopedWriteLock lock(read_write_mutex_);
		auto it = comment_container_.find(comment_id);
		if(it == comment_container_.end())
		{
			// not found
			return false;
		}
		// found
		comment_container_.erase(it);
	}
	
	onCommentDeleted(comment_id);
	return true;
}

int CommentContainer::count()
{
	ScopedReadLock lock(read_write_mutex_);
	return comment_container_.size();
}

const Comment* CommentContainer::getByCommentID(const wstring& comment_id)
{
	ScopedReadLock lock(read_write_mutex_);
	auto it = comment_container_.find(comment_id);

	if(it == comment_container_.end())
	{
		// not found
		return nullptr;
	}
	// found
	return &(it->second);
}

const Comment* CommentContainer::operator[](const wstring& comment_id)
{
	return getByCommentID(comment_id);
}

void CommentContainer::bindToScript(lua_State* lua_state)
{
	module(lua_state)
	[
		class_<CommentContainer>("CommentContainer")
		.def(constructor<>())
		.scope
		[
			def("insert", &CommentContainer::insert)
		]
		.scope
		[
			def("erase", &CommentContainer::erase)
		]
		.scope
		[
			def("getByCommentID", &CommentContainer::getByCommentID)
		]
	];
}

CommentContainer::~CommentContainer()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite