#include <Stream/StreamImpl.hpp>
#include <Stream/Post/Post.hpp>
#include <Stream/Post/PostContainer/PostContainer.hpp>
#include <Stream/Comment/CommentList/CommentList.hpp>
#include <Utility/LuaScript.hpp>
#include <Utility/Utility.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

StreamImpl::StreamImpl()
:read_write_mutex_(make_shared<ReadWriteMutex>())
{
	PostContainer::onPostDeleted.connect(boost::bind(&StreamImpl::remove, this, _1));
}

wstring StreamImpl::getAccountID() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return account_id_;
}

void StreamImpl::setAccountID(const wstring& account_id)
{
	ScopedWriteLock lock(*read_write_mutex_);
	account_id_ = account_id;
}

wstring StreamImpl::getTargetCircleID() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return target_circle_id_;
}

void StreamImpl::setTargetCircleID(const wstring& target_circle_id)
{
	ScopedWriteLock lock(*read_write_mutex_);
	target_circle_id_ = target_circle_id;
}

void StreamImpl::refreshupdate()
{
	/*
	LuaScript<bool(string)> lua_script("LuaScript/StreamImplUpdate.lua", "StreamImplRefreshUpdate", [](lua_State* lua_state)
	{
		//LuaConnection::BindModule(lua_state);
	});

	auto result = lua_script(Utility::convertUnicodeToUTF8(account_id_));
	if(result == false)
	{
		// stream update failed
		return;
	}
	*/
}

bool StreamImpl::add(const wstring& post_id)
{
#ifdef SHOW_UPGRADABLE_READLOCKED_FUNCTION
	cout << "StreamImpl::add" << endl;
#endif
	UpgradableReadLock lock(*read_write_mutex_);
	
	if(post_id.empty())
	{
		return false;
	}
	lock.upgradeToWriteLock();
	auto result = post_id_list_.push_back(post_id);
	lock.downgradeToReadLock();
	return result.second;
}

bool StreamImpl::add(const Post& post)
{
	post.getCommentList()->onCommentAdded.connect([this](const Comment& comment)
		{
			onCommentAdded(comment);
		});
		
	post.getCommentList()->onCommentEdited.connect([this](const Comment& comment)
		{
			onCommentEdited(comment);
		});
	post.getCommentList()->onCommentDeleted.connect([this](const wstring& comment_id)
		{
			onCommentDeleted(comment_id);
		});
	
	if(add(post.getPostID()))
	{
		onPostAdded(post);
		return true;
	}
	return false;
}

bool StreamImpl::remove(const wstring& post_id)
{
	typedef PostIDList::index<search_by_post_id>::type PostIndex;

#ifdef SHOW_UPGRADABLE_READLOCKED_FUNCTION
	cout << "StreamImpl::remove" << endl;
#endif
	UpgradableReadLock lock(*read_write_mutex_);
	
	PostIndex& post_index = post_id_list_.get<search_by_post_id>();
	auto post_id_it = post_index.find(post_id);
	if(post_id_it == post_index.end())
	{
		// not found
		return false;
	}

	lock.upgradeToWriteLock();
	post_index.erase(post_id_it, post_index.end());
	
	onPostDeleted(post_id);
	return true;
}

bool StreamImpl::contain(const wstring& post_id) const
{
	typedef PostIDList::index<search_by_post_id>::type PostIndex;

	ScopedReadLock lock(*read_write_mutex_);
	const PostIndex& post_index = post_id_list_.get<search_by_post_id>();
	auto post_id_it = post_index.find(post_id);
	if(post_id_it == post_index.end())
	{
		// not found
		return false;
	}
	return true;
}

shared_ptr<Post> StreamImpl::getByPostID(const wstring& post_id) const
{
	if(!contain(post_id))
	{
		return make_shared<Post>();
	}
	return PostContainer::getByPostID(post_id);
}

shared_ptr<Post> StreamImpl::getByIndex(int index) const
{
	typedef PostIDList::index<search_sequence>::type PostSequencedIndex;

	ScopedReadLock lock(*read_write_mutex_);
	const PostSequencedIndex& post_index = post_id_list_.get<search_sequence>();
	auto post_it = post_index.begin();

	int count = 0;
	while(post_it != post_index.end())
	{
		if(count == index)
		{
			return getByPostID(*post_it);
		}
		++count;
		++post_it;
	}
	return make_shared<Post>();
}

shared_ptr<Post> StreamImpl::operator[](const wstring& post_id) const
{
	return getByPostID(post_id);
}

shared_ptr<Post> StreamImpl::operator[](int index) const
{
	return getByIndex(index);
}

int StreamImpl::count() const
{
	typedef PostIDList::index<search_by_post_id>::type PostIndex;

	ScopedReadLock lock(*read_write_mutex_);
	const PostIndex& post_index = post_id_list_.get<search_by_post_id>();
	return post_index.size();
}

StreamImpl::~StreamImpl()
{
	PostContainer::onPostInserted.disconnect(
		boost::bind(static_cast<bool(StreamImpl::*)(const Post& post)>(&StreamImpl::add), this, _1));

	PostContainer::onPostDeleted.disconnect(boost::bind(&StreamImpl::remove, this, _1));
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite