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

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/signals2.hpp>

#include <memory>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Post;
class Comment;
class ReadWriteMutex;

class GOOGLEPLUSLIBRARY_API StreamImpl
{
	friend class Stream;
	//friend class MyAccountImpl;
	//friend class MyPageAccount;

public:
	StreamImpl();

public:
	std::wstring getAccountID() const;

protected:
	void setAccountID(const std::wstring& account_id);

private:
	std::wstring account_id_;

public:
	std::wstring getTargetCircleID() const;
protected:
	void setTargetCircleID(const std::wstring& target_circle_id);
private:
	std::wstring target_circle_id_;

public:
	void refreshupdate();

	boost::signals2::signal<void (const Post&)> onPostAdded;
	boost::signals2::signal<void (const Post&)> onPostEdited;
	boost::signals2::signal<void (const std::wstring&)> onPostDeleted;
	
	boost::signals2::signal<void (const Comment&)> onCommentAdded;
	boost::signals2::signal<void (const Comment&)> onCommentEdited;
	boost::signals2::signal<void (const std::wstring&)> onCommentDeleted;

	boost::signals2::signal<void (const Post&)> onPostUpdated;
	boost::signals2::signal<void (const Post&)> onStreamUpdated;
	
protected:
	bool add(const std::wstring& post_id);

	bool add(const Post& post);

protected:
	bool remove(const std::wstring& post_id);

public:
	bool contain(const std::wstring& post_id) const;

	std::shared_ptr<Post> getByPostID(const std::wstring& post_id) const;

	std::shared_ptr<Post> getByIndex(int index) const;

	std::shared_ptr<Post> operator[](const std::wstring& post_id) const;

	std::shared_ptr<Post> operator[](int index) const;

	int count() const;
	
public:
	virtual ~StreamImpl();

protected:
	struct search_sequence {};
	struct search_by_post_id {};

	typedef boost::multi_index::multi_index_container<
		std::wstring,
		boost::multi_index::indexed_by<
		boost::multi_index::sequenced<boost::multi_index::tag<search_sequence> >,

		boost::multi_index::ordered_unique<
		boost::multi_index::tag<search_by_post_id>,
		boost::multi_index::identity<std::wstring>
		>
		>
	> PostIDList;

private:
	PostIDList post_id_list_;
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite