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
#pragma warning (disable:4275)
#endif
#endif

#include <Thread/ReadWriteMutex.hpp>

#include <boost/utility.hpp>
#include <list>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Cookie;

/*!
* @~english
* @brief Container class in order to be able to access cookie information from anywhere
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief �ǂ�����ł��N�b�L�[���ɃA�N�Z�X�ł���悤�ɂ��邽�߂̃R���e�i�N���X
* @warning ���̃N���X�̓��C�u�����J���҂Ȃ�т�Lua�X�N���v�g�ҏW�҈ȊO���p���Ȃ��悤�ɂ��Ă�������
*/
class GOOGLEPLUSLIBRARY_API CookieContainer : boost::noncopyable
{
	/*!
	* @~english
	* @brief Structure for associating cookies and e-mail address, the account ID
	* @~japanese
	* @brief �N�b�L�[�ƃ��[���A�h���X,�A�J�E���gID���֘A�t���邽�߂̍\����
	*/
	struct CookieInformation
	{
		std::string mail_address;
		std::string account_id;
		std::list<Cookie> cookies;
	};

public:
	CookieContainer();

	/*!
	* @~english
	* @brief Associate the account ID that you specify in the email address that you specify
	* @details This function needs to be called other than after a login is not usually
	* @param target_mail_address E-mail address that you want to associate with the account ID(e.g. hogehoge@gmail.com)
	* @param account_id Associate account ID to add(e.g. 116324207729009185938)
	* @~japanese
	* @brief �w�肵�����[���A�h���X�Ɏw�肵���A�J�E���gID���֘A�t���܂�
	* @details �ʏ킱�̊֐��̓��O�C��������ȊO�Ăяo���K�v�͂���܂���
	* @param target_mail_address �A�J�E���gID�Ɋ֘A�t���������[���A�h���X(��: hogehoge@gmail.com)
	* @param account_id �ǉ�����֘A�t����A�J�E���gID(��: 116324207729009185938)
	*/
	static void setConnectID(const std::string& target_mail_address, const std::string& account_id);

	/*!
	* @~english
	* @brief Add the specified cookie to the list of cookies for the specified account ID
	* @param cookie Cookies you want to add
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief �w�肵���A�J�E���gID�̃N�b�L�[�̃��X�g�Ɏw�肵���N�b�L�[��ǉ����܂�
	* @param cookie �ǉ��������N�b�L�[
	* @param account_id �Ώۂ̃A�J�E���gID(��: 116324207729009185938)
	*/
	static void addCookieByAccountID(const Cookie& cookie, const std::string& account_id);

	static void addCookiesByAccountID(const std::list<Cookie>& cookie_list, const std::string& account_id);

	/*!
	* @~english
	* @brief Add the specified cookie to the list of cookies for the specified E-mail address
	* @param cookie Cookies you want to add
	* @param mail_address E-mail address of the target(e.g. hogehoge@gmail.com)
	* @~japanese
	* @brief �w�肵�����[���A�h���X�̃N�b�L�[�̃��X�g�Ɏw�肵���N�b�L�[��ǉ����܂�
	* @param cookie �ǉ��������N�b�L�[
	* @param mail_address �Ώۂ̃��[���A�h���X(��: hogehoge@gmail.com)
	*/
	static void addCookieByMailAddress(const Cookie& cookie, const std::string& mail_address);

	static void addCookiesByMailAddress(const std::list<Cookie>& cookie_list, const std::string& mail_address);

	/*!
	* @~english
	* @brief Displays to standard output a list of cookie names and values of the account id for the specified
	* @param account_id account id of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief �w�肵���A�J�E���gID�̃N�b�L�[�ɂ��Ė��O�ƒl�̈ꗗ��W���o�͂ɕ\�����܂�
	* @param account_id �Ώۂ̃A�J�E���gID(��: 116324207729009185938)
	*/
	static void showCookiesByAccountID(const std::string& account_id);

	/*!
	* @~english
	* @brief Displays to standard output a list of cookie names and values of the e-mail address for the specified
	* @param mail_address E-mail address of the target(e.g. hogehoge@gmail.com)
	* @~japanese
	* @brief �w�肵�����[���A�h���X�̃N�b�L�[�ɂ��Ė��O�ƒl�̈ꗗ��W���o�͂ɕ\�����܂�
	* @param mail_address �Ώۂ̃��[���A�h���X(��: hogehoge@gmail.com)
	*/
	static void showCookiesByMailAddress(const std::string& mail_address);

	/*!
	* @~english
	* @brief Gets a list of cookies for the specified account ID
	* @param account_id account id of the target(e.g. 116324207729009185938)
	* @return List of cookies for the specified account ID
	* @~japanese
	* @brief �w�肵���A�J�E���gID�̃N�b�L�[�̃��X�g���擾����
	* @param account_id �Ώۂ̃A�J�E���gID(��: 116324207729009185938)
	* @return �w�肵���A�J�E���gID�̃N�b�L�[�̃��X�g
	*/
	static std::list<Cookie> getCookieByAccountID(const std::string& account_id);

	/*!
	* @~english
	* @brief Gets a list of cookie for the specified E-mail address
	* @param mail_address E-mail address of the target(e.g. hogehoge@gmail.com)
	* @~japanese
	* @brief �w�肵�����[���A�h���X�̃N�b�L�[�̃��X�g���擾����
	* @param mail_address �Ώۂ̃��[���A�h���X(��: hogehoge@gmail.com)
	*/
	static std::list<Cookie> getCookieByMailAddress(const std::string& mail_address);
	
	/*!
	* @~english
	* @brief Initialize the list of cookies for the specified account id
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief �w�肵���A�J�E���gID�̃N�b�L�[�̃��X�g�����������܂�
	* @param account_id �Ώۂ̃A�J�E���gID(��: 116324207729009185938)
	*/
	static void clearCookieByAccountID(const std::string& account_id);

	/*!
	* @~english
	* @brief Initialize the list of cookies for the specified e-mail address
	* @param mail_address E-mail address of the target(e.g. hogehoge@gmail.com)
	* @~japanese
	* @brief �w�肵�����[���A�h���X�̃N�b�L�[�̃��X�g�����������܂�
	* @param mail_address �Ώۂ̃��[���A�h���X(��: hogehoge@gmail.com)
	*/
	static void clearCookieByMailAddress(const std::string& mail_address);

	/*!
	* @~english
	* @brief Initialize the list of cookies for all accounts
	* @~japanese
	* @brief ���ׂẴA�J�E���g�̃N�b�L�[�̃��X�g�����������܂�
	*/
	static void clearAllCookie();

	virtual ~CookieContainer();

private:
	static std::list<CookieInformation> cookie_container_;
	static ReadWriteMutex read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
