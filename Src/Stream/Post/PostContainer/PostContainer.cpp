#include <Stream/Post/PostContainer/PostContainer.hpp>
#include <Stream/Post/Post.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{
	
using namespace std;

boost::signals2::signal<void (const Post&)> PostContainer::onPostInserted;
boost::signals2::signal<void (const Post&)> PostContainer::onPostEdited;
boost::signals2::signal<void (const wstring&)> PostContainer::onPostDeleted;

map<wstring, Post> PostContainer::post_container_;
ReadWriteMutex PostContainer::read_write_mutex_;

PostContainer::PostContainer()
{
}

bool PostContainer::insert(const Post& post)
{
#ifdef SHOW_UPGRADABLE_READLOCKED_FUNCTION
	cout << "PostContainer::insert" << endl;
#endif
	UpgradableReadLock lock(read_write_mutex_);

	wstring post_id = post.getPostID();
	if(post_id.empty())
	{
		return false;
	}

	lock.upgradeToWriteLock();
	auto result = post_container_.insert(map<wstring, Post>::value_type(post_id, post));
	lock.downgradeToReadLock();

	if(result.second)
	{
		onPostInserted(post);
		return true;
	}

	if(post.isEdited())
	{
		// added edited post
		lock.upgradeToWriteLock();
		post_container_[post_id] = post;
		lock.downgradeToReadLock();
		onPostEdited(post);
		return true;
	}
	
	return false;
}

bool PostContainer::erase(const wstring& post_id)
{
#ifdef SHOW_UPGRADABLE_READLOCKED_FUNCTION
	cout << "PostContainer::erase" << endl;
#endif
	UpgradableReadLock lock(read_write_mutex_);
	auto it = post_container_.find(post_id);
	if(it == post_container_.end())
	{
		// not found
		return false;
	}
	
	// found
	lock.upgradeToWriteLock();
	post_container_.erase(it);
	lock.downgradeToReadLock();

	onPostDeleted(post_id);
	
	return true;
}

shared_ptr<Post> PostContainer::getByPostID(const wstring& post_id)
{
	ScopedReadLock lock(read_write_mutex_);
	auto it = post_container_.find(post_id);
	if(it == post_container_.end())
	{
		// not found
		return make_shared<Post>();
	}
	// found
	return make_shared<Post>(it->second);
}

shared_ptr<Post> PostContainer::operator[](const wstring& post_id)
{
	return getByPostID(post_id);
}

int PostContainer::count()
{
	ScopedReadLock lock(read_write_mutex_);
	return post_container_.size();
}

PostContainer::~PostContainer()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite