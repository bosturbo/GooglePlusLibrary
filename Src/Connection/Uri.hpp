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

#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

/*!
* @~english
* @brief Class to get the url information
* @~japanese
* @brief Url�����擾���邽�߂̃N���X
*/
class GOOGLEPLUSLIBRARY_API Uri
{
public:
	Uri(const std::string& url);

	/*!
	* @~english
	* @brief Gets the scheme of the url
	* @return Scheme of the url
	* @~japanese
	* @brief Url�̃X�L�[�����擾���܂�
	* @return Url�̃X�L�[��
	*/
	std::string getScheme() const;

	/*!
	* @~english
	* @brief Gets the Authority(IP address or DNS host name of the server) of the Url
	* @return Authority of the Url
	* @~japanese
	* @brief Url��Authority(�T�[�o�[��DNS�z�X�g���܂���IP�A�h���X)���擾���܂�
	* @return Url��Authority
	*/
	std::string getAuthority() const;

	/*!
	* @~english
	* @brief Gets the user of the Url
	* @return User of Url
	* @~japanese
	* @brief Url�̃��[�U�[���擾���܂�
	* @return Url�̃��[�U�[
	*/
	std::string getUser() const;

	/*!
	* @~english
	* @brief Gets the host of the Url
	* @return Host of Url
	* @~japanese
	* @brief Url�̃z�X�g���擾���܂�
	* @return Url�̃z�X�g
	*/
	std::string getHost() const;

	/*!
	* @~english
	* @brief Gets the port of the Url
	* @todo To be able to get the port number from the scheme even if the port is not listed
	* @return Port of Url
	* @~japanese
	* @brief Url�̃|�[�g���擾���܂�
	* @todo �|�[�g���L�ڂ���Ă��Ȃ��ꍇ�ł��X�L�[������|�[�g�ԍ����擾�ł���悤�ɂ���
	* @return Url�̃|�[�g
	*/
	int getPort() const;

	/*!
	* @~english
	* @brief Gets the path of the Url
	* @return Path of Url
	* @~japanese
	* @brief Url�̃p�X���擾���܂�
	* @return Url�̃p�X
	*/
	std::string getPath() const;

	/*!
	* @~english
	* @brief Gets the query of the Url
	* @return Query of Url
	* @~japanese
	* @brief Url�̃N�G�����擾���܂�
	* @return Url�̃N�G��
	*/
	std::string getQuery() const;

	/*!
	* @~english
	* @brief Gets the fragment of the Url
	* @return Fragment of Url
	* @~japanese
	* @brief Url�̃t���O�����g���擾���܂�
	* @return Url�̃t���O�����g
	*/
	std::string getFragment() const;

	virtual ~Uri();

private:
	std::string scheme;
	std::string authority;
	std::string user;
	std::string host;
	int         port;
	std::string path;
	std::string query;
	std::string fragment;
};

} // namespace GooglePlusLibrary
} // namespace Gplusnasite
