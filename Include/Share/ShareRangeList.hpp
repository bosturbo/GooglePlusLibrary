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

#include <Circle/Circle.hpp>
#include <Account/Account/Account.hpp>


#include <string>
#include <list>
#include <map>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class MyAccount;
class AccountList;

/*!
* @~english
* @brief Class to share posts to set the range
* @~japanese
* @brief ���e�̌��J�͈͂�ݒ肷��N���X
*/
class GOOGLEPLUSLIBRARY_API ShareRangeList
{
public:
	ShareRangeList();

public:
	/*!
	* @~english
	* @brief Range to include the public in post
	* @~japanese
	* @brief ���e�͈͂Ɉ�ʌ��J���܂߂܂�
	*/
	void addPublic();

	/*!
	* @~english
	* @brief Except to the public from a range submitted
	* @~japanese
	* @brief ���e�͈͂����ʌ��J�������܂�
	*/
	void removePublic();

private:
	bool is_added_public_;

public:
	/*!
	* @~english
	* @brief Range to include the circle of your post
	* @~japanese
	* @brief ���e�͈͂ɂ��Ȃ��̃T�[�N�����܂߂܂�
	*/
	void addYourCircle();

	/*!
	* @~english
	* @brief Except for the circle of your post from a range
	* @~japanese
	* @brief ���e�͈͂��炠�Ȃ��̃T�[�N���������܂�
	*/
	void removeYourCircle();
private:
	bool is_added_your_circle_;

public:
	/*!
	* @~english
	* @brief Range to include the circle of extend post
	* @~japanese
	* @brief ���e�͈͂ɗF�B�̗F�B�T�[�N�����܂߂܂�
	*/
	void addExtendCircle();

	/*!
	* @~english
	* @brief Except for the circle of extend post from a range
	* @~japanese
	* @brief ���e�͈͂���F�B�̗F�B�T�[�N���������܂�
	*/
	void removeExtendCircle();
private:
	bool is_added_extend_circle_;

public:
	/*!
	* @~english
	* @brief Add the user for mension
	* @param account Account of the user you want to mension
	* @~japanese
	* @brief �����V�������郆�[�U�[��ǉ����܂�
	* @param account �����V�������������[�U�[�̃A�J�E���g
	*/
	void addAccount(const Account& account);

	/*!
	* @~english
	* @brief Add the user for mension
	* @param account_list List of accounts of users who want to mension
	* @~japanese
	* @brief �����V�������郆�[�U�[��ǉ����܂�
	* @param account_list �����V�������������[�U�[�̃A�J�E���g�̃��X�g
	*/
	void addAccount(const std::list<Account>& account_list);

	/*!
	* @~english
	* @brief Add the user for mension
	* @param account_list List of accounts of users who want to mension
	* @~japanese
	* @brief �����V�������郆�[�U�[��ǉ����܂�
	* @param account_list �����V�������������[�U�[�̃A�J�E���g�̃��X�g
	*/
	void addAccount(const AccountList& account_list);
	
	/*!
	* @~english
	* @brief Exclude the specified user from the list of users was set to mension
	* @param account_id ID of the user account that you do not want to mension in the list
	* @~japanese
	* @brief �ݒ肵�������V�������郆�[�U�[�̃��X�g����w�肵�����[�U�[�����O���܂�
	* @param account_id ���X�g�̒��Ń����V�����������Ȃ����[�U�[�̃A�J�E���gID
	*/
	void removeAccount(const std::wstring& account_id);

	/*!
	* @~english
	* @brief Add to specified in the range include the Circle
	* @param circle Circle added to the range you want to specify post
	* @~japanese
	* @brief ���e�͈͂Ɏw�肵���T�[�N�����܂߂܂�
	* @param circle ���e�͈͂ɒǉ��w�肵�����T�[�N��
	*/
	void addCircle(const Circle& circle);
	
	/*!
	* @~english
	* @brief Except for the ID specified in the range of circle post
	* @param circle_id ID of the circle you want to specify the scope exclusion in post
	* @~japanese
	* @brief ���e�͈͂Ɏw�肵���T�[�N����ID�������܂�
	* @param circle_id ���e�͈͂ɏ��O�w�肵�����T�[�N����ID
	*/
	void removeCircle(const std::wstring& circle_id);

	/*!
	* @~english
	* @brief Clears all the user specified mension
	* @~japanese
	* @brief �����V�����w�肵�����[�U�[�����ׂăN���A���܂�
	*/
	void removeAllAccounts();

	/*!
	* @~english
	* @brief Clears all of the circle was set post added to the range
	* @~japanese
	* @brief ���e�͈͂ɒǉ��ݒ肵���T�[�N�������ׂăN���A���܂�
	*/
	void removeAllCircles();

public:
	void isSendMailToNonGooglePlusUser(bool is_send_mail);
private:
	bool is_send_mail_;

protected:
	std::wstring createParameter(const std::wstring& target_account_id) const;
public:
	virtual ~ShareRangeList();

private:
	std::map<std::wstring, Account> account_list_;
	mutable std::map<std::wstring, Circle> circle_list_;
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite