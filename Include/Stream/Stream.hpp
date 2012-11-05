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

#include <boost/signals2.hpp>

#include <memory>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Post;
class Comment;
class StreamImpl;

class GOOGLEPLUSLIBRARY_API Stream
{
	friend class MyAccountImpl;
	friend class MyPageAccount;

public:
	Stream();

public:
	std::wstring getAccountID() const;

protected:
	void setAccountID(const std::wstring& account_id);

public:
	std::wstring getTargetCircleID() const;
protected:
	void setTargetCircleID(const std::wstring& target_circle_id);

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
	virtual ~Stream();

private:
	std::shared_ptr<StreamImpl> impl_;

};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite