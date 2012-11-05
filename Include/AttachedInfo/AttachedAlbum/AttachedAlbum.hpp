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
#endif
#endif

#include <string>
#include <list>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class ReadWriteMutex;

/*!
* @~english
* @brief Class to generate the information when added album to share post and to get information when the album has been attached to the post
* @~japanese
* @brief ���e�ɕt������Ă���A���o�������擾������A�A���o���t�����e���V�F�A����Ƃ��̏��𐶐����邽�߂̃N���X
*/
class GOOGLEPLUSLIBRARY_API AttachedAlbum
{
	friend class AttachedAlbumBase;
public:
	AttachedAlbum();
	AttachedAlbum(std::wstring album_name);

public:

	/*!
	* @~english
	* @brief Gets the name of the album
	* @return Album name is set
	* @~japanese
	* @brief �A���o�������擾���܂�
	* @return �ݒ肳�ꂽ�A���o����
	*/
	std::wstring getAlbumName() const;
private:
	std::wstring album_name_;

public:
	/*!
	* @~english
	* @brief Adds a file to the album
	* @param file_path The path of the file you want to add
	* @~japanese
	* @brief �A���o���Ƀt�@�C����ǉ����܂�
	* @param file_path �ǉ��������t�@�C���̃p�X
	*/
	void addFile(const std::wstring& file_path);

	/*!
	* @~english
	* @brief remove specified file from the album
	* @param file_name The name of the file you want to delete
	* @~japanese
	* @brief �w�肵���t�@�C�����A���o������폜���܂�
	* @param file_name �폜�������t�@�C���̖��O
	*/
	void removeFile(const std::wstring& file_name);

	/*!
	* @~english
	* @brief Upload the album
	* @param account_id account id(e.g. 116324207729009185938)
	* @~japanese
	* @brief �A���o�����A�b�v���[�h���܂�
	* @param account_id �A�J�E���gID(��: 116324207729009185938)
	*/
	void upload(const std::wstring& account_id);

public:
	virtual ~AttachedAlbum();

private:

	std::list<std::wstring> file_list_;
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite