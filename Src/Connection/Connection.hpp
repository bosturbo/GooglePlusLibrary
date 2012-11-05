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

#include <string>
#include <map>
#include <iosfwd>
#include <boost/signals2.hpp>

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class HttpResponse;
class JsonObject;

/*!
* @~english
* @brief class for connect to the Google+ server(Upper layer)
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief Google+�T�[�o�[�ƒʐM���邽�߂̃N���X(��ʑw)
* @warning ���̃N���X�̓��C�u�����J���҂Ȃ�т�Lua�X�N���v�g�ҏW�҈ȊO���p���Ȃ��悤�ɂ��Ă�������
*/
class GOOGLEPLUSLIBRARY_API Connection
{
public:
	Connection();

	/*!
	* @~english
	* @brief Sets the key e-mail address to save the cookie
	* @details you need to call this function, if you want to connect Google+ with the account ID has not been able to get
	* @param mail_address E-mail address associated with a cookie(e.g. hogehoge@gmail.com)
	* @~japanese
	* @brief �N�b�L�[�̕ۑ��L�[�ƂȂ郁�[���A�h���X��ݒ肵�܂�
	* @details �A�J�E���gID���擾�ł��Ă��Ȃ���ԂŒʐM���s���ꍇ�͂��̊֐����Ăяo���K�v������܂�
	* @param mail_address �N�b�L�[�Ɗ֘A�t���郁�[���A�h���X(��: hogehoge@gmail.com)
	*/
	void setCurrentMailAddress(const std::string& mail_address);

	/*!
	* @~english
	* @brief Sets the key account id to save the cookie
	* @param account_id account id associated with a cookie(e.g. 116324207729009185938)
	* @~japanese
	* @brief �N�b�L�[�̕ۑ��L�[�ƂȂ�A�J�E���gID��ݒ肵�܂�
	* @param account_id �N�b�L�[�Ɗ֘A�t����A�J�E���gID(��: 116324207729009185938)
	*/
	void setCurrentAccountID(const std::string& account_id);

	/*!
	* @~english
	* @brief Sets the user agent when perform connection
	* @attention User agent is recommended you set this to what the latest version of Google Chrome
	* @param user_agent The user-agent wstring you want to set(e.g. Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.56 Safari/535.11)
	* @~japanese
	* @brief �ʐM���s���ۂ̃��[�U�[�G�[�W�F���g��ݒ肵�܂�
	* @attention �����ɐݒ肷�郆�[�U�[�G�[�W�F���g��Google Chrome�̍ŐV�o�[�W�����̂��̂𐄏��������܂�
	* @param user_agent �ݒ肵�������[�U�[�G�[�W�F���g������(��: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.56 Safari/535.11)
	*/
	void setUserAgent(const std::string& user_agent);

	/*!
	* @~english
	* @brief Gets the user agent when perform connection
	* @return User-agent wstring is set(e.g. Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.56 Safari/535.11)
	* @~japanese
	* @brief �ʐM���s���ۂ̃��[�U�[�G�[�W�F���g���擾���܂�
	* @return �ݒ肳��Ă��郆�[�U�[�G�[�W�F���g������(��: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.56 Safari/535.11)
	*/
	std::string getUserAgent() const;

	/*!
	* @~english
	* @brief Set the timeout when connecting
	* @param time_seconds Timeout period (in seconds)
	* @~japanese
	* @brief �ʐM����ۂ̃^�C���A�E�g���Ԃ�ݒ肵�܂�
	* @param time_seconds �^�C���A�E�g����(�b)
	*/
	void setTimeOut(long time_seconds);

	/*!
	* @~english
	* @brief Get the timeout when connecting
	* @return Timeout period (in seconds)
	* @~japanese
	* @brief �ʐM����ۂ̃^�C���A�E�g���Ԃ��擾���܂�
	* @return �^�C���A�E�g����(�b)
	*/
	long getTimeOut() const;

	/*!
	* @~english
	* @brief Connect HTTP GET to the specified url
	* @param url Url you want to connect
	* @param auto_redirect Whether or not to auto-redirect
	* @return Connection result
	* @~japanese
	* @brief httpGet�ʐM���s���܂�
	* @param url �ʐM��Url
	* @param auto_redirect �I�[�g���_�C���N�g���s�����ǂ���
	* @return �ʐM����
	*/
	HttpResponse httpGet(const std::string& url, bool auto_redirect = false);
	
	/*!
	* @~english
	* @brief Connect HTTP POST to the specified url
	* @param url Url you want to connect
	* @param parameter_pairs Parameters you want to post
	* @return Connection result
	* @~japanese
	* @brief httpPost�ʐM���s���܂�
	* @param url �ʐM��Url
	* @param parameter_pairs ���e�������p�����[�^�[
	* @return �ʐM����
	*/
	HttpResponse httpPost(const std::string& url, const std::map<std::string, std::string>& parameter_pairs);

	/*!
	* @~english
	* @brief Connect HTTP POST to the specified url
	* @param url Url you want to connect
	* @param parameter Parameters you want to post
	* @return Connection result
	* @~japanese
	* @brief httpPost�ʐM���s���܂�
	* @param url �ʐM��Url
	* @param parameter ���e�������p�����[�^�[
	* @return �ʐM����
	*/
	HttpResponse httpPost(const std::string& url, const std::string& parameter);

	/*!
	* @~english
	* @brief Connect HTTP POST to the specified url
	* @param url Url you want to connect
	* @param file_stream File you want to post
	* @return Connection result
	* @~japanese
	* @brief httpPost�ʐM���s���܂�
	* @param url �ʐM��Url
	* @param file_stream ���e�������t�@�C��
	* @return �ʐM����
	*/
	HttpResponse httpPut(const std::string& url, std::ifstream& file_stream);

public:
	/*!
	* @~english
	* @brief create json from connection result wstring
	* @param response Connection result wstring
	* @param replace_to_valid_json Whether or not to fix the result wstring unauthorized connection(Specify the true in most cases)
	* @return Json
	* @~japanese
	* @brief �ʐM���ʕ����񂩂�Json�𐶐����܂�
	* @param response �ʐM���ʕ�����
	* @param replace_to_valid_json �s���ȒʐM���ʕ�������C�����邩�ǂ���(�قƂ�ǂ̏ꍇtrue���w�肵�܂�)
	* @return Json
	*/
	JsonObject convertResponseToJson(const std::string& response);

	/*!
	* @~english
	* @brief create json from connection result
	* @param response Connection result
	* @param replace_to_valid_json Whether or not to modify the contents of the invalid connection result(Specify the true in most cases)
	* @return Json
	* @~japanese
	* @brief �ʐM���ʕ����񂩂�Json�𐶐����܂�
	* @param response �ʐM����
	* @param replace_to_valid_json �s���ȒʐM���ʂ̓��e���C�����邩�ǂ���(�قƂ�ǂ̏ꍇtrue���w�肵�܂�)
	* @return Json
	*/
	JsonObject convertResponseToJson(const HttpResponse& response);

	static std::string escapeString(std::string source_text);

	static void bindToScript(lua_State* lua_state);

public:
	boost::signals2::signal<void(HttpResponse)> onResponseReceived;

	virtual ~Connection();
private:

	std::string user_agent_;
	long time_out_;
	std::string current_mail_address_;
	std::string current_account_id_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite