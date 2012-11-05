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
#pragma warning (disable:4996)
#endif
#endif

#include <Thread/ReadWriteMutex.hpp>

#include <boost/signals2.hpp>
#include <boost/utility.hpp>
#include <map>

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Account;

/*!
* @~english
* @brief Container class in order to be able to access account information from anywhere
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @warning Please use the AccountList class if you are the general public
* @see AccountList
* @~japanese
* @brief �ǂ�����ł��A�J�E���g���ɃA�N�Z�X�ł���悤�ɂ��邽�߂̃R���e�i�N���X
* @warning ���̃N���X�̓��C�u�����J���҂Ȃ�т�Lua�X�N���v�g�ҏW�҈ȊO���p���Ȃ��悤�ɂ��Ă�������
* @warning ��ʂ̕���AccountList�N���X�������p��������
* @see AccountList
*/
class GOOGLEPLUSLIBRARY_API AccountContainer : boost::noncopyable
{
public:
	AccountContainer();

	/*!
	* @~english
	* @brief Add account in the Container
	* @details This is not a function to add the account to the Circle
	* @param account account information that add to the Container
	* @~japanese
	* @brief �R���e�i�ɃA�J�E���g����ǉ����܂�
	* @details ����̓T�[�N���ɃA�J�E���g��ǉ�����֐��ł͂���܂���
	* @param account �ǉ�����A�J�E���g���
	*/
	static bool insert(const Account& account);
	static boost::signals2::signal<void (const Account&)> onAccountinserted;

	static void updateItem(const Account& account);
	static boost::signals2::signal<void (const Account&)> onAccountEdited;

	static bool erase(const std::wstring& account_id);
	static boost::signals2::signal<void (const std::wstring&)> onAccountDeleted;

	/*!
	* @~english
	* @brief Get account information from the Container
	* @details Returns null if the corresponding account could not be found
	* @param account_id ID of the account information you want to get(e.g. 110903198133008172755)
	* @return Circle information with the specified circle id
	* @~japanese
	* @brief �R���e�i����A�J�E���g�����擾���܂�
	* @details �Y������A�J�E���g��������Ȃ������ꍇnull��Ԃ��܂�
	* @param account_id �擾�������A�J�E���g��ID(��: 110903198133008172755)
	* @return �w�肵���A�J�E���gID�����A�J�E���g�̏��
	*/
	static const Account* getByAccountID(const std::wstring& account_id);

	virtual ~AccountContainer();

public:
	static void bindToScript(lua_State* lua_state);

private:
	static std::map<std::wstring, Account> account_container_;
	static ReadWriteMutex read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite