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

#include <AttachedInfo/AttachedYouTubePlaylist/AttachedYouTubePlaylist.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API AttachedYouTubePlaylistBase
{
public:
	AttachedYouTubePlaylistBase()
	{
	}

	virtual ~AttachedYouTubePlaylistBase()
	{
	}
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite