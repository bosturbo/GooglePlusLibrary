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

#include <memory>
#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class ReadWriteMutex;

/*!
* @~english
* @brief Class to retrieve the information of the link that was named
* @~japanese
* @brief ���O�t�����ꂽ�����N�̏����擾���邽�߂̃N���X
*/
class GOOGLEPLUSLIBRARY_API LabeledLink
{
	friend class MyAccountProfile;

protected:
	LabeledLink(const std::wstring& label = L"", const std::wstring& url = L"");

public:

	/*!
	* @~english
	* @brief Get the label of the url
	* @return label Label for the url
	* @~japanese
	* @brief Url�̃��x�����擾����
	* @return Url�̃��x��
	*/
	std::wstring getLabel() const;
protected:

	/*!
	* @~english
	* @brief Set the label of the url
	* @param label Label for the url
	* @~japanese
	* @brief Url�̃��x����ݒ肷��
	* @param label Url�̃��x��
	*/
	void setLabel(const std::wstring& label);
private:
	std::wstring label_;

public:
	/*!
	* @~english
	* @brief Get the url that is set
	* @return url has been set
	* @~japanese
	* @brief �ݒ肳�ꂽUrl���擾����
	* @return �ݒ肳�ꂽUrl
	*/
	std::wstring getUrl() const;
protected:

	/*!
	* @~english
	* @brief Set the url
	* @param url Url you want to set
	* @~japanese
	* @brief Url��ݒ肷��
	* @param url �ݒ肵����Url
	*/
	void setUrl(const std::wstring& url);
private:
	std::wstring url_;

public:
	virtual ~LabeledLink();

private:
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite