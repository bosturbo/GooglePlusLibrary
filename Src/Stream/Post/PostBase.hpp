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

#include <Stream/Post/Post.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API PostBase
{
public:
	PostBase()
	{
	}

protected:

	std::shared_ptr<PostImpl>& impl_(Post& post)
	{
		assert(post.impl_);
		return post.impl_;
	}
	
public:
	virtual ~PostBase()
	{
	}
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite