#include <Stream/Comment/CommentList/CommentList.hpp>
#include <Stream/Comment/Comment.hpp>
#include <Stream/Comment/CommentContainer/CommentContainer.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{
	
using namespace std;

CommentList::CommentList()
:target_post_id_(L""),
read_write_mutex_(make_shared<ReadWriteMutex>())
{
	CommentContainer::onCommentinserted.connect(
		boost::bind(static_cast<bool(CommentList::*)(const Comment& comment)>(&CommentList::add), this, _1));
	
	CommentContainer::onCommentEdited.connect(boost::bind(&CommentList::updateItem, this, _1));
	CommentContainer::onCommentDeleted.connect(boost::bind(&CommentList::remove, this, _1));
}

wstring CommentList::getTargetPostID() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return target_post_id_;
}

void CommentList::setTargetPostID(const wstring& target_post_id)
{
	ScopedWriteLock lock(*read_write_mutex_);
	target_post_id_ = target_post_id;
}

bool CommentList::add(const wstring& comment_id)
{
	if(comment_id.empty())
	{
		return false;
	}
	
	ScopedWriteLock lock(*read_write_mutex_);
	auto result = comment_id_list_.push_back(comment_id);
	return result.second;
}

bool CommentList::add(const Comment& comment)
{
	if(comment.getPostID() != getTargetPostID())
	{
		return false;
	}

	if(!add(comment.getCommentID()))
	{
		return false;
	}
	onCommentAdded(comment);
	return true;
}

void CommentList::updateItem(const Comment& comment)
{
	CommentContainer::updateItem(comment);
}

bool CommentList::remove(const wstring& comment_id)
{
	typedef CommentIDList::index<search_by_comment_id>::type CommentIndex;

#ifdef SHOW_UPGRADABLE_READLOCKED_FUNCTION
	cout << "CommentList::remove" << endl;
#endif
	UpgradableReadLock lock(*read_write_mutex_);
	
	CommentIndex& comment_index = comment_id_list_.get<search_by_comment_id>();
	auto comment_id_it = comment_index.find(comment_id);
	if(comment_id_it == comment_index.end())
	{
		// not found
		return false;
	}
	lock.upgradeToWriteLock();
	comment_index.erase(comment_id_it, comment_index.end());
	lock.downgradeToReadLock();
	onCommentDeleted(comment_id);
	return true;
}

bool CommentList::contain(const wstring& comment_id) const
{
	typedef CommentIDList::index<search_by_comment_id>::type CommentIndex;
	ScopedReadLock lock(*read_write_mutex_);
	const CommentIndex& comment_index = comment_id_list_.get<search_by_comment_id>();
	
	auto comment_id_it = comment_index.find(comment_id);

	if(comment_id_it == comment_index.end())
	{
		// not found
		return false;
	}
	return true;
}

const Comment* CommentList::getByCommentID(const wstring& comment_id) const
{
	if(!contain(comment_id))
	{
		return nullptr;
	}
	return CommentContainer::getByCommentID(comment_id);
}

const Comment* CommentList::getByIndex(int index) const
{
	typedef CommentIDList::index<search_sequence>::type CommentSequencedIndex;
	
	ScopedReadLock lock(*read_write_mutex_);
	const CommentSequencedIndex& comment_index = comment_id_list_.get<search_sequence>();
	auto comment_it = comment_index.begin();

	int count = 0;
	while(comment_it != comment_index.end())
	{
		if(count == index)
		{
			return getByCommentID(*comment_it);
		}
		++count;
		++comment_it;
	}
	return nullptr;
}

const Comment* CommentList::operator[](const wstring& comment_id) const
{
	return getByCommentID(comment_id);
}

const Comment* CommentList::operator[](int index) const
{
	return getByIndex(index);
}

int CommentList::count() const
{
	typedef CommentIDList::index<search_by_comment_id>::type CommentIndex;

	ScopedReadLock lock(*read_write_mutex_);
	const CommentIndex& comment_index = comment_id_list_.get<search_by_comment_id>();
	return comment_index.size();
}

CommentList::~CommentList()
{
	CommentContainer::onCommentinserted.disconnect(
		boost::bind(static_cast<bool(CommentList::*)(const Comment& comment)>(&CommentList::add), this, _1));
	
	CommentContainer::onCommentEdited.disconnect(boost::bind(&CommentList::updateItem, this, _1));
	CommentContainer::onCommentDeleted.disconnect(boost::bind(&CommentList::remove, this, _1));

	onCommentAdded.disconnect_all_slots();
	onCommentEdited.disconnect_all_slots();
	onCommentDeleted.disconnect_all_slots();
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite