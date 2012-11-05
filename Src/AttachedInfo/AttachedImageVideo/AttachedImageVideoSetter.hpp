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

#include <AttachedInfo/AttachedImageVideo/AttachedImageVideoBase.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API AttachedImageVideoSetter : public AttachedImageVideoBase
{
public:
	AttachedImageVideoSetter();

	AttachedImageVideo toAttachedImageVideo();

	virtual ~AttachedImageVideoSetter();
private:
	AttachedImageVideo attached_image_video_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite