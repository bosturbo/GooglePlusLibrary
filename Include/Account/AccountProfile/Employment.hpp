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
	* @brief 会社名を取得します
	* @return 会社名
	*/
	std::wstring getCompanyName() const;

	/*!
	* @~english
	* @brief Sets the name of the company
	* @param company_name Company name
	* @~japanese
	* @brief 会社名を設定します
	* @param company_name 会社名
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
	* @brief 役職を取得します
	* @return 役職
	*/
	std::wstring getJobTitle() const;

	/*!
	* @~english
	* @brief Sets job title
	* @param job_title Job title
	* @~japanese
	* @brief 役職を設定します
	* @param job_title 役職
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
	* @brief Gets whether the current has been working in the company
	* @return False, true, or not, if you are working
	* @~japanese
	* @brief その会社に現在勤務しているかどうかを取得します
	* @return 勤務している場合true,そうでない場合false
	*/
	bool isCurrent() const;

	/*!
	* @~english
	* @brief Sets whether the current has been working in the company
	* @param is_current Whether you are currently working for the company
	* @~japanese
	* @brief その会社に現在勤務しているかどうかを設定します
	* @param is_current その会社に現在勤務しているかどうか
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