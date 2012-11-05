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

#include <Stream/Post/MyPost/MyPost.hpp>
#include <Thread/ReadWriteMutex.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API MyPostBase
{
public:
	MyPostBase()
	{
	}

protected:

	static std::shared_ptr<PostSetter>& post_setter_(MyPost& my_post)
	{
		return my_post.post_setter_;
	}

	static std::shared_ptr<ReadWriteMutex>& read_write_mutex_(MyPost& my_post)
	{
		return my_post.read_write_mutex_;
	}
public:
	virtual ~MyPostBase()
	{
	}
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite