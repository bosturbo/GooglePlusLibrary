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

#include <AttachedInfo/AttachedImageVideo/AttachedImageVideo.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API AttachedImageVideoBase
{
public:
	AttachedImageVideoBase()
	{
	}

protected:
	static std::shared_ptr<AttachedAlbum>& attached_album_(AttachedImageVideo& attached_image_video)
	{
		return attached_image_video.attached_album_;
	}

public:
	virtual ~AttachedImageVideoBase()
	{
	}
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite