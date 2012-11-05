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
#pragma warning (disable:4800)
#pragma warning (disable:4996)
#endif
#endif

#include <boost/detail/scoped_enum_emulation.hpp>

#include <boost/thread.hpp>

#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class StreamConnection;

/*!
* @~english
* @brief Class to connect to the talkgadget
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief Talkgadget�ɐڑ����邽�߂̃N���X
* @warning ���̃N���X�̓��C�u�����J���҂Ȃ�т�Lua�X�N���v�g�ҏW�҈ȊO���p���Ȃ��悤�ɂ��Ă�������
*/
class GOOGLEPLUSLIBRARY_API talkgadgetConnection
{
public:

	BOOST_SCOPED_ENUM_START(ConnectionMode)
	{
		Homepage = 0,
		Hangout
	}; BOOST_SCOPED_ENUM_END

	talkgadgetConnection();

public:

	/*!
	* @~english
	* @brief Connect to Talkgadget
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @param connection_mode Modes to connect
	* @~japanese
	* @brief Talkgadget�֐ڑ����܂�
	* @param account_id �Ώۂ̃A�J�E���gID(��: 116324207729009185938)
	* @param connection_mode �ڑ����郂�[�h
	*/
	void connect(const std::wstring& account_id, BOOST_SCOPED_ENUM(ConnectionMode) connection_mode);

	/*!
	* @~english
	* @brief Asynchronous connect to Talkgadget
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @param connection_mode Modes to connect
	* @~japanese
	* @brief Talkgadget�֔񓯊��ڑ����܂�
	* @param account_id �Ώۂ̃A�J�E���gID(��: 116324207729009185938)
	* @param connection_mode �ڑ����郂�[�h
	*/
	void connectAsync(const std::wstring& account_id, BOOST_SCOPED_ENUM(ConnectionMode) connection_mode);

	/*!
	* @~english
	* @brief Wait until initialization is complete asynchronous connection to the talkgadget
	* @~japanese
	* @brief Talkgadget�ւ̐ڑ��̔񓯊�����������������܂őҋ@���܂�
	*/
	void waitConnectAsync();

private:

	/*!
	* @~english
	* @brief A function that initializes the connection to the talkgadget in a separate thread
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @param connection_mode Modes to connect
	* @~japanese
	* @brief �ʃX���b�h��Talkgadget�ւ̐ڑ�������������֐��ł�
	* @param account_id �Ώۂ̃A�J�E���gID(��: 116324207729009185938)
	* @param connection_mode �ڑ����郂�[�h
	*/
	void connectAsyncThreadMethod(const std::wstring& account_id, BOOST_SCOPED_ENUM(ConnectionMode) connection_mode);

	bool is_canceled_;

public:
	int getConnectCount() const;
protected:
	void setConnectCount(int connect_count);
private:
	int connect_count_;

public:
	int getMaximumConnectCount() const;
protected:
	void setMaximumConnectCount(int maximum_connect_count);
private:
	int maximum_connect_count_;

public:
	virtual ~talkgadgetConnection();

private:
	boost::thread connect_thread_;
	std::shared_ptr<StreamConnection> stream_connection_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite