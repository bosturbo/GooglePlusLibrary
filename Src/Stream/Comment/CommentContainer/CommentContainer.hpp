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
#pragma warning (disable:4275)
#pragma warning (disable:4996)
#endif
#endif

#include <Thread/ReadWriteMutex.hpp>

#include <boost/utility.hpp>
#include <boost/signals2.hpp>

#include <string>
#include <map>

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Comment;

class GOOGLEPLUSLIBRARY_API CommentContainer : boost::noncopyable
{
public:
	CommentContainer();
		
	static bool insert(const Comment& comment);
	static boost::signals2::signal<void (const Comment&)> onCommentinserted;

	static void updateItem(const Comment& comment);
	static boost::signals2::signal<void (const Comment&)> onCommentEdited;

	static bool erase(const std::wstring& comment_id);
	static boost::signals2::signal<void (const std::wstring&)> onCommentDeleted;

	static int count();

	static const Comment* getByCommentID(const std::wstring& comment_id);

	const Comment* operator[](const std::wstring& comment_id);

	static void bindToScript(lua_State* lua_state);

	virtual ~CommentContainer();

private:
	static std::map<std::wstring, Comment> comment_container_;
	static ReadWriteMutex read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite