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

#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

/*!
* @~english
* @brief Class to get used to obtain information on cookies
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief �N�b�L�[�̏����擾���邽�߂̎擾���邽�߂̃N���X
* @warning ���̃N���X�̓��C�u�����J���҂Ȃ�т�Lua�X�N���v�g�ҏW�҈ȊO���p���Ȃ��悤�ɂ��Ă�������
*/
class GOOGLEPLUSLIBRARY_API Cookie
{
	friend class WebClient;
	friend class WebClient;
	friend class HttpResponse;
public:
	Cookie();
protected:
	Cookie(const std::string& url, const std::string& raw_information);
	
public:

	/*!
	* @~english
	* @brief Gets the name of the cookie
	* @return The name of the cookie
	* @~japanese
	* @brief �N�b�L�[�����擾���܂�
	* @return �N�b�L�[��
	*/
	std::string getName() const;
private:
	std::string name_;

public:
	/*!
	* @~english
	* @brief Gets the value of the cookie
	* @return The value of the cookie
	* @~japanese
	* @brief �N�b�L�[�l���擾���܂�
	* @return �N�b�L�[�l
	*/
	std::string getValue() const;
private:
	std::string value_;

public:
	/*!
	* @~english
	* @brief Gets the path for this cookie
	* @return Path of the cookie
	* @~japanese
	* @brief �N�b�L�[�̃p�X���擾���܂�
	* @return �N�b�L�[�̃p�X
	*/
	std::string getPath() const;
private:
	std::string path_;

public:
	/*!
	* @~english
	* @brief Gets the domain for this cookie
	* @return Domain of the cookie
	* @~japanese
	* @brief �N�b�L�[�̃h���C�����擾���܂�
	* @return �N�b�L�[�̃h���C��
	*/
	std::string getDomain() const;
private:
	std::string domain_;

public:
	/*!
	* @~english
	* @brief Gets the expiration of the cookie
	* @return Expiration of the cookie
	* @~japanese
	* @brief �N�b�L�[�̗L���������擾���܂�
	* @return �N�b�L�[�̗L������
	*/
	boost::posix_time::ptime getExpireTime() const;
private:
	boost::posix_time::ptime expire_posix_time_;
	
public:
	/*!
	* @~english
	* @brief Gets a string representing the expiration of the cookie
	* @return A string representing the expiration of the cookie(e.g. Fri, 22-Apr-2022 12:11:30 GMT)
	* @~japanese
	* @brief �N�b�L�[�̗L��������\����������擾���܂�
	* @return �N�b�L�[�̗L��������\��������(��: Fri, 22-Apr-2022 12:11:30 GMT)
	*/
	std::string getRawExpireTime() const;
private:
	std::string raw_expire_time_;
	
public:
	/*!
	* @~english
	* @brief Gets whether the cookie has expired
	* @return True if the expiration date of the cookie has expired, false if it has not expired
	* @~japanese
	* @brief �N�b�L�[�̗L���������؂ꂽ���ǂ������擾���܂�
	* @return �N�b�L�[�̗L���������؂ꂽ�ꍇ��true,�؂�ĂȂ��ꍇ��false
	*/
	bool isExpired() const;
private:
	bool is_expired_;
	
public:
	/*!
	* @~english
	* @brief Gets whether the cookie is secure
	* @return If true, otherwise false if the cookie is secure
	* @~japanese
	* @brief �N�b�L�[���Z�L���A���ǂ������擾���܂�
	* @return �N�b�L�[���Z�L���A�Ȃ��true,�����łȂ��ꍇ��false
	*/
	bool isSecure() const;
private:
	bool is_secure_;

public:
	/*!
	* @~english
	* @brief Gets whether the HttpOnly cookies
	* @return If true, otherwise false if the cookie is HttpOnly
	* @~japanese
	* @brief �N�b�L�[��Http�I�����[���ǂ������擾���܂�
	* @return �N�b�L�[��Http�I�����[�Ȃ��true,�����łȂ��ꍇ��false
	*/
	bool isHttpOnly() const;
private:
	bool is_http_only_;

public:
	/*!
	* @~english
	* @brief Gets a string of original cookie when you get the information
	* @return When the original string of cookies to retrieve information
	* @~japanese
	* @brief �N�b�L�[�����擾�����ۂ̃I���W�i����������擾���܂�
	* @return �N�b�L�[�����擾�����ۂ̃I���W�i��������
	*/
	std::string getRawValue() const;
private:
	std::string raw_information_;

public:
	/*!
	* @~english
	* @brief Gets whether the same cookies with this cookie with the specified
	* @return True, false otherwise if the same cookie
	* @~japanese
	* @brief ���̃N�b�L�[�Ǝw�肵���N�b�L�[���������ǂ������擾���܂�
	* @return �����N�b�L�[�Ȃ��true,�����łȂ��Ȃ�false
	*/
	bool isEqual(const Cookie& cookie) const;

	virtual ~Cookie();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
