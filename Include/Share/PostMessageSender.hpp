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

#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class AttachedAlbum;
class AttachedCircle;
class AttachedImageVideo;
class AttachedLocation;
class AttachedUrl;
class AttachedYouTubePlaylist;

/*!
* @~english
* @brief Class in order to share a post
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief ���e���V�F�A���邽�߂̃N���X
* @warning ���̃N���X�̓��C�u�����J���҂Ȃ�т�Lua�X�N���v�g�ҏW�҈ȊO���p���Ȃ��悤�ɂ��Ă�������
*/
class GOOGLEPLUSLIBRARY_API postMessageSender
{
public:
	postMessageSender();

	/*!
	* @~english
	* @brief Creating a post in what has been specified and share it
	* @param message Message content of the post
	* @~japanese
	* @brief �w�肳�ꂽ���e�œ��e���쐬���V�F�A���܂�
	* @param message ���e�̃��b�Z�[�W���e
	*/
	void share(const std::wstring& message);

	void share(const std::wstring& message, const AttachedAlbum& attached_album);

	void share(const std::wstring& message, const AttachedCircle& attached_circle);

	virtual ~postMessageSender();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite