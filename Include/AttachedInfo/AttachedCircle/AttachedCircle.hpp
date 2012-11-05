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

#include <Account/AccountList/AccountList.hpp>


#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Circle;
class MyAccount;
class JsonObject;

/*!
* @~english
* @brief Class to generate the information when added sharing circle to share post and to get information when the sharing circle has been attached to the post
* @~japanese
* @brief ���e�ɕt������Ă���T�[�N�����L�̏����擾������A�T�[�N�����L���e���V�F�A����Ƃ��̏��𐶐����邽�߂̃N���X
*/
class GOOGLEPLUSLIBRARY_API AttachedCircle
{
	friend class AttachedCircleBase;
public:
	AttachedCircle();

	/*!
	* @~english
	* @brief create AttachedCircle
	* @details If it fails to generate returns null
	* @param my_account_id account id(e.g. 116324207729009185938)
	* @param circle_id circle id(e.g. 6e1ff5b889ea6c7e)
	* @param is_include_yourself Whether to include the sharing circle
	* @~japanese
	* @brief �p�����[�^�[����AttachedCircle���쐬���܂�
	* @details �����Ɏ��s�����ꍇ��null��Ԃ��܂�
	* @param my_account_id �A�J�E���gID(��: 116324207729009185938)
	* @param circle_id �T�[�N��ID(��: 6e1ff5b889ea6c7e)
	* @param is_include_yourself ���L�T�[�N���Ɏ������܂߂邩�ǂ���
	* @return �������ꂽAttachedCircle
	*/
	static AttachedCircle* create(const std::wstring& my_account_id, const std::wstring& circle_id, bool is_include_yourself = false);

	/*!
	* @~english
	* @brief create AttachedCircle
	* @details If it fails to generate returns null
	* @param my_account_id account id(e.g. 116324207729009185938)
	* @param circle Circle information you would like to share
	* @param is_include_yourself Whether to include the sharing circle
	* @~japanese
	* @brief �p�����[�^�[����AttachedCircle���쐬���܂�
	* @details �����Ɏ��s�����ꍇ��null��Ԃ��܂�
	* @param my_account_id �A�J�E���gID(��: 116324207729009185938)
	* @param circle ���L�������T�[�N�����
	* @param is_include_yourself ���L�T�[�N���Ɏ������܂߂邩�ǂ���
	*/
	static AttachedCircle* create(const std::wstring& my_account_id, const Circle& circle, bool is_include_yourself = false);

	/*!
	* @~english
	* @brief create AttachedCircle
	* @details If it fails to generate returns null
	* @param my_account Target account
	* @param circle_id circle id(e.g. 6e1ff5b889ea6c7e)
	* @param is_include_yourself Whether to include the sharing circle
	* @~japanese
	* @brief �p�����[�^�[����AttachedCircle���쐬���܂�
	* @details �����Ɏ��s�����ꍇ��null��Ԃ��܂�
	* @param my_account �Ώۂ̃A�J�E���g
	* @param circle_id �T�[�N��ID(��: 6e1ff5b889ea6c7e)
	* @param is_include_yourself ���L�T�[�N���Ɏ������܂߂邩�ǂ���
	*/
	static AttachedCircle* create(const MyAccount& my_account, const std::wstring& circle_id, bool is_include_yourself = false);

	/*!
	* @~english
	* @brief create AttachedCircle
	* @details If it fails to generate returns null
	* @param my_account Target account
	* @param circle Circle information you would like to share
	* @param is_include_yourself Whether to include the sharing circle
	* @~japanese
	* @brief �p�����[�^�[����AttachedCircle���쐬���܂�
	* @details �����Ɏ��s�����ꍇ��null��Ԃ��܂�
	* @param my_account �Ώۂ̃A�J�E���g
	* @param circle ���L�������T�[�N�����
	* @param is_include_yourself ���L�T�[�N���Ɏ������܂߂邩�ǂ���
	*/
	static AttachedCircle* create(const MyAccount& my_account, const Circle& circle, bool is_include_yourself = false);

public:
	const AccountList* getAccountList() const;
private:
	std::shared_ptr<AccountList> account_list_;

public:
	virtual ~AttachedCircle();

private:
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
