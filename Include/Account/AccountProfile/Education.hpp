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
	* @brief 学校名を取得します
	* @return 学校名
	*/
	std::wstring getSchoolName() const;

	/*!
	* @~english
	* @brief Sets the name of the school
	* @param school_name School name
	* @~japanese
	* @brief 学校名を設定します
	* @param school_name 学校名
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
	* @brief 専攻・研究分野を取得します
	* @return 専攻・研究分野
	*/
	std::wstring getMajorOrStudyField() const;

	/*!
	* @~english
	* @brief Sets major or field of study
	* @param major_or_study_field Major or field of study
	* @~japanese
	* @brief 専攻・研究分野を設定します
	* @param major_or_study_field 専攻・研究分野
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
	* @brief 開始年を取得します
	* @return 開始年
	*/
	std::wstring getStartYear() const;

	/*!
	* @~english
	* @brief Sets the starting year
	* @param start_year Start year
	* @~japanese
	* @brief 開始年を設定します
	* @param start_year 開始年
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
	* @brief 終了年を取得します
	* @return 終了年
	*/
	std::wstring getEndYear() const;

	/*!
	* @~english
	* @brief Sets the end year
	* @param end_year End year
	* @~japanese
	* @brief 開始年を設定します
	* @param end_year 開始年
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
	* @brief その学校に現在在学しているかどうかを取得します
	* @return 在学している場合true,そうでない場合false
	*/
	bool isCurrent() const;

	/*!
	* @~english
	* @brief Sets whether or not currently enrolled at the school
	* @param is_current Whether you are currently enrolled at the school
	* @~japanese
	* @brief その学校に現在在学しているかどうかを設定します
	* @param is_current その学校に現在在学しているかどうか
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