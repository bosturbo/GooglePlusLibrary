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
#include <map>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class ReadWriteMutex;

/*!
* @~english
* @brief Class for operating circle information
* @~japanese
* @brief サークルを操作するためのクラス
*/
class GOOGLEPLUSLIBRARY_API Circle
{
	friend class ShareRangeList;
	friend class std::map<std::wstring, Circle>;

protected:
	Circle();
	Circle(const std::wstring& circle_name, const std::wstring& circle_id);

public:

	/*!
	* @~english
	* @brief Check for the correct format of circle ID
	* @return True if the format is correct, false if properly
	* @~japanese
	* @brief サークルIDのフォーマットが正しいか調べます
	* @return フォーマットが正しければtrue、正しくなければfalse
	*/
	static bool verifyCircleID(const std::wstring& circle_id);

	/*!
	* @~english
	* @brief Get circle id
	* @return circle id(e.g. 6e1ff5b889ea6c7e)
	* @~japanese
	* @brief サークルIDを取得します
	* @return サークルID(例: 6e1ff5b889ea6c7e)
	*/
	std::wstring getCircleID() const;
protected:

	/*!
	* @~english
	* @brief Set circle id
	* @param circle_id circle id(e.g. 6e1ff5b889ea6c7e)
	* @~japanese
	* @brief サークルIDを設定します
	* @param circle_id サークルID(例: 6e1ff5b889ea6c7e)
	*/
	void setCircleID(const std::wstring& circle_id);

private:
	std::wstring circle_id_;

public:

	/*!
	* @~english
	* @brief Gets the name of the circle
	* @return Circle name
	* @~japanese
	* @brief サークル名を取得します
	* @return サークル名
	*/
	std::wstring getCircleName() const;
protected:

	/*!
	* @~english
	* @brief Sets the name of the Circle
	* @param circle_name Circle name
	* @~japanese
	* @brief サークル名を設定します
	* @param circle_name サークル名
	*/
	void setCircleName(const std::wstring& circle_name);
private:
	std::wstring circle_name_;

public:
	virtual ~Circle();

private:
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

} // namespace GooglePlusLibrary
} // namespace Gplusnasite
