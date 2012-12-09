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

#include <boost/scoped_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/signals2.hpp>

#include <string>

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class StreamConnectionImpl;

/*!
* @~english
* @brief Class to connect to the stream and update
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief �X�g���[���ɐڑ����X�V���邽�߂̃N���X
* @warning ���̃N���X�̓��C�u�����J���҂Ȃ�т�Lua�X�N���v�g�ҏW�҈ȊO���p���Ȃ��悤�ɂ��Ă�������
*/
class GOOGLEPLUSLIBRARY_API StreamConnection
{
public:
	StreamConnection();

public:

	/*!
	* @~english
	* @brief Initializes the connection to the stream
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief �X�g���[���ւ̐ڑ������������܂�
	* @param account_id �Ώۂ̃A�J�E���gID(��: 116324207729009185938)
	*/
	void initialize(const std::wstring& account_id);

	/*!
	* @~english
	* @brief Initialize the asynchronous connection to the stream
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief �X�g���[���ւ̐ڑ���񓯊��ŏ��������܂�
	* @param account_id �Ώۂ̃A�J�E���gID(��: 116324207729009185938)
	*/
	void initializeAsync(const std::wstring& account_id);

	/*!
	* @~english
	* @brief Wait until initialization is complete asynchronous connection to the stream
	* @~japanese
	* @brief �X�g���[���ւ̐ڑ��̔񓯊�����������������܂őҋ@���܂�
	*/
	void waitInitializeAsync();

private:

	/*!
	* @~english
	* @brief A function that initializes the connection to the stream in a separate thread
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief �ʃX���b�h�ŃX�g���[���ւ̐ڑ�������������֐��ł�
	* @param account_id �Ώۂ̃A�J�E���gID(��: 116324207729009185938)
	*/
	void initializeAsyncThreadMethod(const std::wstring& account_id);
	boost::thread initialize_thread_;

public:
	boost::signals2::signal<void()> onInitializeSucceed;
	boost::signals2::signal<void()> onInitializeFailed;

public:

	/*!
	* @~english
	* @brief Update the stream
	* @details This function is blocking the thread until logout occurs is called in a separate thread
	* @param account_id Account ID of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief �X�g���[�����X�V���܂�
	* @details ���̊֐��͕ʃX���b�h�ŌĂ΂ꃍ�O�A�E�g���s����܂ł��̃X���b�h���u���b�L���O���܂�
	* @param account_id �Ώۂ̃A�J�E���gID(��: 116324207729009185938)
	*/
	void update(const std::wstring& account_id);
private:
	boost::thread update_thread_;

public:
	/*!
	* @~english
	* @brief Abort the update stream
	* @details Blocking of the Update () will be released in good time this function is called
	* @warning This function is implemented please do not use full for outstanding
	* @~japanese
	* @brief �X�g���[�����X�V�𒆎~���܂�
	* @details ���̊֐����Ă΂��ƃL���̗ǂ��^�C�~���O��update()�̃u���b�L���O����������܂�
	* @warning ���̊֐��͎����������S�̂��ߎg�p���Ȃ��ł�������
	*/
	void cancelUpdate();
	
	/*!
	* @~english
	* @brief Gets whether the stream was aborted update
	* @return If it is discontinued, true, false otherwise
	* @~japanese
	* @brief �X�g���[���̍X�V�����~���ꂽ���ǂ������擾���܂�
	* @return ���~���ꂽ�ꍇ��true,�����łȂ��ꍇ��false
	*/
	bool isCanceled();

public:
	int getConnectCount() const;
protected:
	void setConnectCount(int connect_count);

public:
	int getMaximumConnectCount() const;
protected:
	void setMaximumConnectCount(int maximum_connect_count);

public:
	static void bindToScript(lua_State* lua_state);

public:
	virtual ~StreamConnection();

private:
	boost::scoped_ptr<StreamConnectionImpl> impl_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
