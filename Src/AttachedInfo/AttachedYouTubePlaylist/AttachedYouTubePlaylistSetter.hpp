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

#include <AttachedInfo/AttachedYouTubePlaylist/AttachedYouTubePlaylistBase.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API AttachedYouTubePlaylistSetter : public AttachedYouTubePlaylistBase
{
public:
	AttachedYouTubePlaylistSetter();

	AttachedYouTubePlaylist toAttachedYouTubePlaylist();

	virtual ~AttachedYouTubePlaylistSetter();
private:
	AttachedYouTubePlaylist attached_youtube_playlist_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite