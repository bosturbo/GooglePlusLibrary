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
#include <string>
#include <map>
#include <list>

struct PrivateInformation
{
	std::string mail_address;
	std::string account_id;
	std::map<std::string, std::string> informations;
};

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

/*!
* @~english
* @brief Container class in order to be able to access from anywhere in the specified string
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief �ǂ�����ł��w��̕�����ɃA�N�Z�X�ł���悤�ɂ��邽�߂̃R���e�i�N���X
* @warning ���̃N���X�̓��C�u�����J���҂Ȃ�т�Lua�X�N���v�g�ҏW�҈ȊO���p���Ȃ��悤�ɂ��Ă�������
*/
class GOOGLEPLUSLIBRARY_API InformationContainer : boost::noncopyable
{
public:
	InformationContainer();

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
	* @brief Add the string specified in the list of account information for the specified id
	* @param name The name of the character string you want to add
	* @param value String value of the information you want to add
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief �w�肵���A�J�E���gID�̕�������̃��X�g�Ɏw�肵���������ǉ����܂�
	* @param name �ǉ���������������̖��O
	* @param value �ǉ���������������̒l
	* @param account_id �Ώۂ̃A�J�E���gID(��: 116324207729009185938)
	*/
	static void addInformationByAccountID(const std::string& name, const std::string& value, const std::string& account_id);
	
	/*!
	* @~english
	* @brief Adds the number specified in the list of account information for the specified id
	* @param name The name of the numerical information you want to add 
	* @param value numeric value of the information you want to add
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief �w�肵���A�J�E���gID�̐��l���̃��X�g�Ɏw�肵���������ǉ����܂�
	* @param name �ǉ����������l���̖��O
	* @param value �ǉ����������l����̒l
	* @param account_id �Ώۂ̃A�J�E���gID(��: 116324207729009185938)
	*/
	static void addInformationByAccountID(const std::string& name, const int value, const std::string& account_id);
	
	/*!
	* @~english
	* @brief Add the string specified in the list of account information for the specified mail address
	* @param name The name of the character string you want to add
	* @param value String value of the information you want to add
	* @param mail_address E-mail address of the target(e.g. hogehoge@gmail.com)
	* @~japanese
	* @brief �w�肵���A�J�E���gID�̕�������̃��X�g�Ɏw�肵���������ǉ����܂�
	* @param name �ǉ���������������̖��O
	* @param value �ǉ���������������̒l
	* @param mail_address �Ώۂ̃��[���A�h���X(��: hogehoge@gmail.com)
	*/
	static void addInformationByMailAddress(const std::string& name, const std::string& value, const std::string& mail_address);
	
	/*!
	* @~english
	* @brief Adds the number specified in the list of account information for the specified mail address
	* @param name The name of the numerical information you want to add 
	* @param value numeric value of the information you want to add
	* @param mail_address E-mail address of the target(e.g. hogehoge@gmail.com)
	* @~japanese
	* @brief �w�肵���A�J�E���gID�̐��l���̃��X�g�Ɏw�肵���������ǉ����܂�
	* @param name �ǉ����������l���̖��O
	* @param value �ǉ����������l����̒l
	* @param mail_address �Ώۂ̃��[���A�h���X(��: hogehoge@gmail.com)
	*/
	static void addInformationByMailAddress(const std::string& name, const int value, const std::string& mail_address);

	/*!
	* @~english
	* @brief Gets the contents of the information with the specified name from the list of string information for the account ID that you specify
	* @param name The name of the character string you want to get
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief �w�肵���A�J�E���gID�̕�������̃��X�g����w�肵�����O�̏��̓��e���擾���܂�
	* @param name �擾��������������̖��O
	* @param account_id �Ώۂ̃A�J�E���gID(��: 116324207729009185938)
	*/
	static std::string getInformationByAccountID(const std::string& name, const std::string& account_id);

	/*!
	* @~english
	* @brief Gets the contents of the information with the specified name from the list of string information for the email address that you specify
	* @param name The name of the character string you want to get
	* @param mail_address E-mail address of the target(e.g. hogehoge@gmail.com)
	* @~japanese
	* @brief �w�肵�����[���A�h���X�̕�������̃��X�g����w�肵�����O�̏��̓��e���擾���܂�
	* @param name �擾��������������̖��O
	* @param mail_address �Ώۂ̃��[���A�h���X(��: hogehoge@gmail.com)
	*/
	static std::string getInformationByMailAddress(const std::string& name, const std::string& mail_address);

	/*!
	* @~english
	* @brief Initialize the list of string information for the specified account id
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief �w�肵���A�J�E���gID�̕�������̃��X�g�����������܂�
	* @param account_id �Ώۂ̃A�J�E���gID(��: 116324207729009185938)
	*/
	static void clearInformationByAccountID(const std::string& account_id);

	/*!
	* @~english
	* @brief Initialize the list of string information for the specified e-mail address
	* @param mail_address E-mail address of the target(e.g. hogehoge@gmail.com)
	* @~japanese
	* @brief �w�肵�����[���A�h���X�̕�������̃��X�g�����������܂�
	* @param mail_address �Ώۂ̃��[���A�h���X(��: hogehoge@gmail.com)
	*/
	static void clearInformationByMailAddress(const std::string& mail_address);

	/*!
	* @~english
	* @brief Initialize the list of string information for all accounts
	* @~japanese
	* @brief ���ׂẴA�J�E���g�̕�������̃��X�g�����������܂�
	*/
	static void clearAllInformation();

	static void bindToScript(lua_State* lua_state);

	virtual ~InformationContainer();

private:

	static std::list<PrivateInformation> information_container;
	static ReadWriteMutex read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
