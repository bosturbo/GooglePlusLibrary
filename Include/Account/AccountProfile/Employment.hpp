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

class GOOGLEPLUSLIBRARY_API Employment
{
public:
	Employment();

public:
	/*!
	* @~english
	* @brief Gets the name of the company
	* @return Company name
	* @~japanese
	* @brief ��Ж����擾���܂�
	* @return ��Ж�
	*/
	std::wstring getCompanyName() const;

	/*!
	* @~english
	* @brief Sets the name of the company
	* @param company_name Company name
	* @~japanese
	* @brief ��Ж���ݒ肵�܂�
	* @param company_name ��Ж�
	*/
	void setCompanyName(const std::wstring& company_name);
private:
	std::wstring company_name_;

public:
	/*!
	* @~english
	* @brief Gets job title
	* @return Job title
	* @~japanese
	* @brief ��E���擾���܂�
	* @return ��E
	*/
	std::wstring getJobTitle() const;

	/*!
	* @~english
	* @brief Sets job title
	* @param job_title Job title
	* @~japanese
	* @brief ��E��ݒ肵�܂�
	* @param job_title ��E
	*/
	void setJobTitle(const std::wstring& job_title);
private:
	std::wstring job_title_;

public:
	/*!
	* @~english
	* @brief Gets the starting year
	* @return Start year
	* @~japanese
	* @brief �J�n�N���擾���܂�
	* @return �J�n�N
	*/
	std::wstring getStartYear() const;

	/*!
	* @~english
	* @brief Sets the starting year
	* @param start_year Start year
	* @~japanese
	* @brief �J�n�N��ݒ肵�܂�
	* @param start_year �J�n�N
	*/
	void setStartYear(const std::wstring& start_year);
private:
	std::wstring start_year_;

public:
	/*!
	* @~english
	* @brief Gets the end year
	* @return End year
	* @~japanese
	* @brief �I���N���擾���܂�
	* @return �I���N
	*/
	std::wstring getEndYear() const;

	/*!
	* @~english
	* @brief Sets the end year
	* @param end_year End year
	* @~japanese
	* @brief �J�n�N��ݒ肵�܂�
	* @param end_year �J�n�N
	*/
	void setEndYear(const std::wstring& end_year);
private:
	std::wstring end_year_;

public:
	/*!
	* @~english
	* @brief Gets whether the current has been working in the company
	* @return False, true, or not, if you are working
	* @~japanese
	* @brief ���̉�ЂɌ��݋Ζ����Ă��邩�ǂ������擾���܂�
	* @return �Ζ����Ă���ꍇtrue,�����łȂ��ꍇfalse
	*/
	bool isCurrent() const;

	/*!
	* @~english
	* @brief Sets whether the current has been working in the company
	* @param is_current Whether you are currently working for the company
	* @~japanese
	* @brief ���̉�ЂɌ��݋Ζ����Ă��邩�ǂ�����ݒ肵�܂�
	* @param is_current ���̉�ЂɌ��݋Ζ����Ă��邩�ǂ���
	*/
	void setIsCurrent(bool is_current);
private:
	bool is_current_;

public:
	virtual ~Employment();
private:
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite