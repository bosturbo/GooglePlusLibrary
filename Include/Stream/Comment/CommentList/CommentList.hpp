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

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/signals2.hpp>

#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Comment;
class ReadWriteMutex;

class GOOGLEPLUSLIBRARY_API CommentList
{
	friend class Post;
	friend class PostImpl;
	friend class PostSetter;
public:
	CommentList();

public:
	std::wstring getTargetPostID() const;
protected:
	void setTargetPostID(const std::wstring& target_post_id);
private:
	std::wstring target_post_id_;

protected:
	bool add(const std::wstring& comment_id);
	bool add(const Comment& comment);

public:
	boost::signals2::signal<void (const Comment&)> onCommentAdded;

public:
	void updateItem(const Comment& comment);
	boost::signals2::signal<void (const Comment&)> onCommentEdited;

protected:
	bool remove(const std::wstring& comment_id);

public:
	boost::signals2::signal<void (const std::wstring&)> onCommentDeleted;

public:
	bool contain(const std::wstring& comment_id) const;

	const Comment* getByCommentID(const std::wstring& comment_id) const;

	const Comment* getByIndex(int index) const;

	const Comment* operator[](const std::wstring& comment_id) const;
	const Comment* operator[](int index) const;

	int count() const;

public:
	virtual ~CommentList();

protected:

	struct search_sequence {};
	struct search_by_comment_id {};

	typedef boost::multi_index::multi_index_container<
		std::wstring,
		boost::multi_index::indexed_by<
		boost::multi_index::sequenced<boost::multi_index::tag<search_sequence> >,

		boost::multi_index::ordered_unique<
		boost::multi_index::tag<search_by_comment_id>,
		boost::multi_index::identity<std::wstring>
		>
		>
	> CommentIDList;
private:
	CommentIDList comment_id_list_;
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite