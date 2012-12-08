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
#pragma warning (disable:4819)
#pragma warning (disable:4996)
#endif
#endif

#include <string>
#include <map>
#include <list>

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Cookie;

/*!
* @~english
* @brief Class of connection to get the results
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief �ʐM���ʂ��擾���邽�߂̃N���X
* @warning ���̃N���X�̓��C�u�����J���҂Ȃ�т�Lua�X�N���v�g�ҏW�҈ȊO���p���Ȃ��悤�ɂ��Ă�������
*/
class GOOGLEPLUSLIBRARY_API HttpResponse
{
	friend class Connection;
	friend class WebClient;
	friend class WebClientCppNetlib;

public:
	HttpResponse();

protected:
	HttpResponse(const std::string& url, int status_code, const std::map<std::string, std::string>& response_header, 
		const std::list<Cookie>& response_cookie, 
		const std::string& response_body);
	
public:
	std::string getUrl() const;
private:
	std::string url_;

public:
	int getStatusCode();

private:
	int status_code_;

public:
	/*!
	* @~english
	* @brief Gets the response body
	* @return The response body string has been set
	* @~japanese
	* @brief ���X�|���X�{�f�B���擾���܂�
	* @return �ݒ肳�ꂽ���X�|���X�{�f�B������
	*/
	std::string getResponseBody() const;
protected:

	/*!
	* @~english
	* @brief Sets the response body
	* @param response_body Response body string you want to set
	* @~japanese
	* @brief ���X�|���X�{�f�B��ݒ肵�܂�
	* @param response_body �ݒ肵�������X�|���X�{�f�B������
	*/
	void setResponseBody(const std::string& response_body);
private:
	std::string response_body_;

public:

	/*!
	* @~english
	* @brief Displays to standard output a list of response cookies names and values 
	* @~japanese
	* @brief ���X�|���X�N�b�L�[�ɂ��Ė��O�ƒl�̈ꗗ��W���o�͂ɕ\�����܂�
	*/
	void showResponseCookies();
	
public:
	/*!
	* @~english
	* @brief Gets a list of response cookies
	* @return List of response cookies
	* @~japanese
	* @brief ���X�|���X�N�b�L�[�̃��X�g���擾���܂�
	* @return ���X�|���X�N�b�L�[�̃��X�g
	*/
	std::list<Cookie> getResponseCookies() const;

	/*!
	* @~english
	* @brief Gets the value of the cookie from the response cookie with the specified name
	* @details Returns the empty string if the cookie the same as the name specified was not found
	* @return The same as the value of the cookie with the given name
	* @~japanese
	* @brief ���X�|���X�N�b�L�[����w�肵�����O�̃N�b�L�[�̒l���擾���܂�
	* @details �w�肵�����O�Ɠ����N�b�L�[��������Ȃ������ꍇ�󕶎���Ԃ��܂�
	* @return �w�肵�����O�Ɠ����N�b�L�[�̒l
	*/
	std::string getResponseCookie(const std::string& name);
protected:

	/*!
	* @~english
	* @brief Sets the list of cookies in the response cookie
	* @param cookies List of cookies you want to set
	* @~japanese
	* @brief ���X�|���X�N�b�L�[�ɃN�b�L�[�̃��X�g��ݒ肵�܂�
	* @param cookies �ݒ肵�����N�b�L�[�̃��X�g
	*/
	void setResponseCookies(const std::list<Cookie>& cookies);
private:
	std::list<Cookie> response_cookie_;

public:

	/*!
	* @~english
	* @brief Gets the map of the response header
	* @return Map of the response header is set
	* @~japanese
	* @brief ���X�|���X�w�b�_�̃}�b�v���擾���܂�
	* @return �ݒ肳�ꂽ���X�|���X�w�b�_�̃}�b�v
	*/
	std::map<std::string, std::string> getResponseHeaderValues() const;

	/*!
	* @~english
	* @brief Gets the value of the header from the response header with the specified name
	* @details Returns the empty string if the header the same as the name specified was not found
	* @param name The name of the header you want to get
	* @return The same as the value of the header with the given name
	* @~japanese
	* @brief ���X�|���X�w�b�_����w�肵�����O�̃w�b�_�̒l���擾���܂�
	* @details �w�肵�����O�Ɠ����w�b�_��������Ȃ������ꍇ�󕶎���Ԃ��܂�
	* @param name �擾�������w�b�_�̖��O
	* @return �w�肵�����O�Ɠ����w�b�_�̒l
	*/
	std::string getResponseHeaderValue(const std::string& name) const;
protected:

	/*!
	* @~english
	* @brief Sets the list of headers in the response header
	* @param headers List of headers you want to set
	* @~japanese
	* @brief ���X�|���X�w�b�_�Ƀw�b�_�̃��X�g��ݒ肵�܂�
	* @param headers �ݒ肵�����w�b�_�̃��X�g
	*/
	void setResponseHeader(std::map<std::string, std::string> headers);
private:
	std::map<std::string, std::string> response_header_;

public:
	std::string getRedirectUrl();
private:
	std::string redirect_url_;

public:
	static void bindToScript(lua_State* lua_state);

public:
	virtual ~HttpResponse();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite