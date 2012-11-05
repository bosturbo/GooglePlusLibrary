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

class GOOGLEPLUSLIBRARY_API Education
{
public:
	Education();

public:
	/*!
	* @~english
	* @brief Gets the name of the school
	* @return School name
	* @~japanese
	* @brief �w�Z�����擾���܂�
	* @return �w�Z��
	*/
	std::wstring getSchoolName() const;

	/*!
	* @~english
	* @brief Sets the name of the school
	* @param school_name School name
	* @~japanese
	* @brief �w�Z����ݒ肵�܂�
	* @param school_name �w�Z��
	*/
	void setSchoolName(const std::wstring& school_name);
private:
	std::wstring school_name_;

public:
	/*!
	* @~english
	* @brief Gets major or field of study
	* @return Major or field of study
	* @~japanese
	* @brief ��U�E����������擾���܂�
	* @return ��U�E��������
	*/
	std::wstring getMajorOrStudyField() const;

	/*!
	* @~english
	* @brief Sets major or field of study
	* @param major_or_study_field Major or field of study
	* @~japanese
	* @brief ��U�E���������ݒ肵�܂�
	* @param major_or_study_field ��U�E��������
	*/
	void setMajorOrStudyField(const std::wstring& major_or_study_field);
private:
	std::wstring major_or_study_field_;

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
	* @brief Gets whether currently enrolled at the school
	* @return False, true, or not, if you are enrolled
	* @~japanese
	* @brief ���̊w�Z�Ɍ��ݍ݊w���Ă��邩�ǂ������擾���܂�
	* @return �݊w���Ă���ꍇtrue,�����łȂ��ꍇfalse
	*/
	bool isCurrent() const;

	/*!
	* @~english
	* @brief Sets whether or not currently enrolled at the school
	* @param is_current Whether you are currently enrolled at the school
	* @~japanese
	* @brief ���̊w�Z�Ɍ��ݍ݊w���Ă��邩�ǂ�����ݒ肵�܂�
	* @param is_current ���̊w�Z�Ɍ��ݍ݊w���Ă��邩�ǂ���
	*/
	void setIsCurrent(bool is_current);
private:
	bool is_current_;

public:
	virtual ~Education();
private:
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite