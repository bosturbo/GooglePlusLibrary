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
* @brief 住んだことのある地域の情報を取得するためのクラス
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
	* @brief 在籍した都市名を取得します
	* @return 都市名
	*/
	std::wstring getCityName() const;
protected:

	/*!
	* @~english
	* @brief Sets the name of the city lived
	* @param city_name City name
	* @~japanese
	* @brief 在籍した都市名を設定します
	* @param city_name 都市名
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
	* @brief その都市に現在住んでいるかどうかを取得します
	* @return 住んでいる場合true,そうでない場合false
	*/
	bool isCurrent() const;
protected:

	/*!
	* @~english
	* @brief Sets whether currently lives in that city
	* @param is_current Whether currently lives in that city
	* @~japanese
	* @brief その都市に現在住んでいるかどうかを設定します
	* @param is_current その都市に現在住んでいるかどうか
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