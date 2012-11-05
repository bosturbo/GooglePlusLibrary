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
* @brief ���e�ɕt������Ă���YouTube�v���C���X�g�����擾������AYouTube�v���C���X�g�t�����e���V�F�A����Ƃ��̏��𐶐����邽�߂̃N���X
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