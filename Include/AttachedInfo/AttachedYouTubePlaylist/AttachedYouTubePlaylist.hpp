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

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

/*!
* @~english
* @brief Class to generate the information when added YouTube Playlist to share post and to get information when the YouTube Playlist has been attached to the post
* @~japanese
* @brief 投稿に付加されているYouTubeプレイリスト情報を取得したり、YouTubeプレイリスト付加投稿をシェアするときの情報を生成するためのクラス
*/
class GOOGLEPLUSLIBRARY_API AttachedYouTubePlaylist
{
	friend class AttachedYouTubePlaylistBase;
public:
	AttachedYouTubePlaylist();

	virtual ~AttachedYouTubePlaylist();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite