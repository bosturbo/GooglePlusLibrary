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
* @brief Class to get the local information that may have lived
* @~japanese
* @brief �Z�񂾂��Ƃ̂���n��̏����擾���邽�߂̃N���X
*/
class GOOGLEPLUSLIBRARY_API LivedPlace
{
	friend class MyAccountProfile;

public:
	LivedPlace(const std::wstring& city_name = L"", bool is_current = false);

public:
	/*!
	* @~english
	* @brief Gets the name of the city lived
	* @return City name
	* @~japanese
	* @brief �ݐЂ����s�s�����擾���܂�
	* @return �s�s��
	*/
	std::wstring getCityName() const;
protected:

	/*!
	* @~english
	* @brief Sets the name of the city lived
	* @param city_name City name
	* @~japanese
	* @brief �ݐЂ����s�s����ݒ肵�܂�
	* @param city_name �s�s��
	*/
	void setCityName(const std::wstring& city_name);
private:
	std::wstring city_name_;

public:
	/*!
	* @~english
	* @brief Gets whether a city where you live
	* @return False, true, or not, If you live in
	* @~japanese
	* @brief ���̓s�s�Ɍ��ݏZ��ł��邩�ǂ������擾���܂�
	* @return �Z��ł���ꍇtrue,�����łȂ��ꍇfalse
	*/
	bool isCurrent() const;
protected:

	/*!
	* @~english
	* @brief Sets whether currently lives in that city
	* @param is_current Whether currently lives in that city
	* @~japanese
	* @brief ���̓s�s�Ɍ��ݏZ��ł��邩�ǂ�����ݒ肵�܂�
	* @param is_current ���̓s�s�Ɍ��ݏZ��ł��邩�ǂ���
	*/
	void setIsCurrent(bool is_current);
private:
	bool is_current_;

public:
	virtual ~LivedPlace();
private:
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite