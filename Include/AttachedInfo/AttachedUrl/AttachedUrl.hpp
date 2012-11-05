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
#pragma warning (disable:4996)
#endif
#endif

#include <memory>
#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class MyAccount;
class MyPageAccount;
class JsonObject;
class ReadWriteMutex;

/*!
* @~english
* @brief Class to generate the information when added url to share post and to get information when the url has been attached to the post
* @~japanese
* @brief ���e�ɕt������Ă���Url�����擾������AUrl�t�����e���V�F�A����Ƃ��̏��𐶐����邽�߂̃N���X
*/
class GOOGLEPLUSLIBRARY_API AttachedUrl
{
	friend class AttachedUrlBase;
public:
	AttachedUrl();

	/*!
	* @~english
	* @brief create AttachedUrl(No thumbnail)
	* @details If it fails to generate returns null
	* @param account_id account id(e.g. 116324207729009185938)
	* @param url Url to be added to post
	* @~japanese
	* @brief �p�����[�^�[����AttachedUrl���쐬���܂�(�T���l�C���͕t�����Ȃ�)
	* @details �����Ɏ��s�����ꍇ��null��Ԃ��܂�
	* @param account_id �A�J�E���gID(��: 116324207729009185938)
	* @param url ���e�ɕt������Url
	*/
	static AttachedUrl* create(const std::wstring& account_id, const std::wstring& url);

	/*!
	* @~english
	* @brief create AttachedUrl(No thumbnail)
	* @details If it fails to generate returns null
	* @param my_account my account that posts this information
	* @param url Url to be added to post
	* @~japanese
	* @brief �p�����[�^�[����AttachedUrl���쐬���܂�(�T���l�C���͕t�����Ȃ�)
	* @details �����Ɏ��s�����ꍇ��null��Ԃ��܂�
	* @param my_account ���e���s�������̃A�J�E���g
	* @param url ���e�ɕt������Url
	*/
	static AttachedUrl* create(const MyAccount& my_account, const std::wstring& url);

	/*!
	* @~english
	* @brief create AttachedUrl(No thumbnail)
	* @details If it fails to generate returns null
	* @param my_page_account my account that posts this information
	* @param url Url to be added to post
	* @~japanese
	* @brief �p�����[�^�[����AttachedUrl���쐬���܂�(�T���l�C���͕t�����Ȃ�)
	* @details �����Ɏ��s�����ꍇ��null��Ԃ��܂�
	* @param my_page_account ���e���s�������̃A�J�E���g
	* @param url ���e�ɕt������Url
	*/
	static AttachedUrl* create(const MyPageAccount& my_page_account, const std::wstring& url);

	/*!
	* @~english
	* @brief create AttachedUrl
	* @details If it fails to generate returns null
	* @param account_id account id(e.g. 116324207729009185938)
	* @param url Url to be added to post
	* @param thumbnail_number the position of the thumbnail that when share posts(0 start)
	* @~japanese
	* @brief �p�����[�^�[����AttachedUrl���쐬���܂�
	* @details �����Ɏ��s�����ꍇ��null��Ԃ��܂�
	* @param account_id �A�J�E���gID(��: 116324207729009185938)
	* @param url ���e�ɕt������Url
	* @param thumbnail_number ���e���ɐݒ肷��T���l�C���̈ʒu(0�X�^�[�g)
	*/
	static AttachedUrl* create(const std::wstring& account_id, const std::wstring& url, int thumbnail_number);

	/*!
	* @~english
	* @brief create AttachedUrl
	* @details If it fails to generate returns null
	* @param my_account My account that posts this information
	* @param url Url to be added to post
	* @param thumbnail_number the position of the thumbnail that when share posts(0 start)
	* @~japanese
	* @brief �p�����[�^�[����AttachedUrl���쐬���܂�
	* @details �����Ɏ��s�����ꍇ��null��Ԃ��܂�
	* @param my_account ���e���s�������̃A�J�E���g
	* @param url ���e�ɕt������Url
	* @param thumbnail_number ���e���ɐݒ肷��T���l�C���̈ʒu(0�X�^�[�g)
	*/
	static AttachedUrl* create(const MyAccount& my_account, const std::wstring& url, int thumbnail_number);

	/*!
	* @~english
	* @brief create AttachedUrl
	* @details If it fails to generate returns null
	* @param my_page_account My account that posts this information
	* @param url Url to be added to post
	* @param thumbnail_number the position of the thumbnail that when share posts(0 start)
	* @~japanese
	* @brief �p�����[�^�[����AttachedUrl���쐬���܂�
	* @details �����Ɏ��s�����ꍇ��null��Ԃ��܂�
	* @param my_page_account ���e���s�������̃A�J�E���g
	* @param url ���e�ɕt������Url
	* @param thumbnail_number ���e���ɐݒ肷��T���l�C���̈ʒu(0�X�^�[�g)
	*/
	static AttachedUrl* create(const MyPageAccount& my_page_account, const std::wstring& url, int thumbnail_number);

public:
	std::wstring getPageTitle() const;
private:
	std::wstring page_title_;

public:
	std::wstring getPageDescription() const;
private:
	std::wstring page_description_;

public:
	std::wstring getPageFaviconUrl() const;
private:
	std::wstring page_favicon_url_;

public:
	std::wstring getPageUrl() const;
private:
	std::wstring page_url_;

public:
	/*!
	* @~english
	* @brief Get Thumbnail image Url is set
	* @return Thumbnail image Url is set
	* @~japanese
	* @brief �ݒ肳��Ă���T���l�C���摜Url���擾���܂�
	* @return �ݒ肳��Ă���T���l�C���摜Url
	*/
	std::wstring getThumbnailUrl() const;
private:
	std::wstring thumbnail_url_;

public:

	/*!
	* @~english
	* @brief Get the position of the image thumbnail is set
	* @return The position of the image thumbnail is set
	* @~japanese
	* @brief �ݒ肳��Ă���T���l�C���摜�̈ʒu���擾���܂�
	* @return �ݒ肳��Ă���T���l�C���摜�̈ʒu
	*/
	int getThumbnailPosition() const;

	/*!
	* @~english
	* @brief Set the position of the thumbnail images
	* @param thumbnail_position The position of the image thumbnail is set to post(0 start)
	* @~japanese
	* @brief �T���l�C���摜�̈ʒu��ݒ肵�܂�
	* @param thumbnail_position ���e�ɐݒ肷��T���l�C���摜�̈ʒu(0�X�^�[�g)
	*/
	void setThumbnailPosition(int thumbnail_position);
private:
	int thumbnail_position_;
	
public:
	virtual ~AttachedUrl();

private:
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
