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
#include <memory>

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Post;

class GOOGLEPLUSLIBRARY_API PostContainer : boost::noncopyable
{
public:
	PostContainer();
	
	static bool insert(const Post& post);

	static boost::signals2::signal<void (const Post&)> onPostInserted;
	static boost::signals2::signal<void (const Post&)> onPostEdited;

	static bool erase(const std::wstring& post_id);
	static boost::signals2::signal<void (const std::wstring&)> onPostDeleted;

	static int count();
	
	static std::shared_ptr<Post> getByPostID(const std::wstring& post_id);

	std::shared_ptr<Post> operator[](const std::wstring& post_id);
	
public:
	virtual ~PostContainer();
	
private:
	static std::map<std::wstring, Post> post_container_;
	static ReadWriteMutex read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite