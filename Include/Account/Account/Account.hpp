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

#include <memory>
#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class AddedAccountList;
class AddedYouAccountList;
class ReadWriteMutex;

/*!
* @~english
* @brief Class to retrieve the information of Google+
* @~japanese
* @brief Google+ �A�J�E���g�̏����擾���邽�߂̃N���X
*/
class GOOGLEPLUSLIBRARY_API Account
{
friend class AccountBase;

//friend class MyAccountImpl;
//friend class PageAccount;

public:
	Account();

public:

	/*!
	* @~english
	* @brief Check for the correct format of account ID
	* @return True if the format is correct, false if properly
	* @~japanese
	* @brief �A�J�E���gID�̃t�H�[�}�b�g�������������ׂ܂�
	* @return �t�H�[�}�b�g�����������true�A�������Ȃ����false
	*/
	static bool verifyAccountID(const std::wstring& account_id);

	/*!
	* @~english
	* @brief Get accout id
	* @return account id(e.g. 116324207729009185938)
	* @~japanese
	* @brief �A�J�E���gID���擾���܂�
	* @return �A�J�E���gID(��: 116324207729009185938)
	*/
	std::wstring getAccountID() const;
private:
	std::wstring account_id_;

public:
	/*!
	* @~english
	* @brief Gets the name of the account
	* @return Account name
	* @~japanese
	* @brief �A�J�E���g�����擾���܂�
	* @return �A�J�E���g��
	*/
	std::wstring getAccountName() const;
private:
	std::wstring account_name_;

public:

	/*!
	* @~english
	* @brief Get url of the currently set account image
	* @return Url of the currently set account image
	* @~japanese
	* @brief ���ݐݒ肳��Ă���A�J�E���g�C���[�W��Url���擾���܂�
	* @return ���ݐݒ肳��Ă���A�J�E���g�C���[�W��Url
	*/
	std::wstring getCurrentAccountImageUrl() const;
private:
	std::wstring current_account_image_url_;

public:
	AddedAccountList* getAddedAccountList() const;
private:
	std::shared_ptr<AddedAccountList> added_account_list_;

public:
	AddedYouAccountList* getAddedYouAccountList() const;
private:
	std::shared_ptr<AddedYouAccountList> added_you_account_list_;
	
public:
	virtual ~Account();

private:
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

} // namespace GooglePlusLibrary
} // namespace Gplusnasite
