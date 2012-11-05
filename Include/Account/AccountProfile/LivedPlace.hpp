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
* @brief Z‚ñ‚¾‚±‚Æ‚Ì‚ ‚é’nˆæ‚Ìî•ñ‚ğæ“¾‚·‚é‚½‚ß‚ÌƒNƒ‰ƒX
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
	* @brief İĞ‚µ‚½“ss–¼‚ğæ“¾‚µ‚Ü‚·
	* @return “ss–¼
	*/
	std::wstring getCityName() const;
protected:

	/*!
	* @~english
	* @brief Sets the name of the city lived
	* @param city_name City name
	* @~japanese
	* @brief İĞ‚µ‚½“ss–¼‚ğİ’è‚µ‚Ü‚·
	* @param city_name “ss–¼
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
	* @brief ‚»‚Ì“ss‚ÉŒ»İZ‚ñ‚Å‚¢‚é‚©‚Ç‚¤‚©‚ğæ“¾‚µ‚Ü‚·
	* @return Z‚ñ‚Å‚¢‚éê‡true,‚»‚¤‚Å‚È‚¢ê‡false
	*/
	bool isCurrent() const;
protected:

	/*!
	* @~english
	* @brief Sets whether currently lives in that city
	* @param is_current Whether currently lives in that city
	* @~japanese
	* @brief ‚»‚Ì“ss‚ÉŒ»İZ‚ñ‚Å‚¢‚é‚©‚Ç‚¤‚©‚ğİ’è‚µ‚Ü‚·
	* @param is_current ‚»‚Ì“ss‚ÉŒ»İZ‚ñ‚Å‚¢‚é‚©‚Ç‚¤‚©
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