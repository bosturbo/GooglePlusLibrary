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
#pragma warning (disable:4275)
#pragma warning (disable:4996)
#endif
#endif

#include <Thread/ReadWriteMutex.hpp>

#include <boost/signals2.hpp>
#include <boost/utility.hpp>
#include <map>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Circle;

/*!
* @~english
* @brief Container class in order to be able to access circle information from anywhere
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @warning Please use the CircleList class if you are the general public
* @see CircleList
* @~japanese
* @brief どこからでもサークル情報にアクセスできるようにするためのコンテナクラス
* @warning このクラスはライブラリ開発者ならびにLuaスクリプト編集者以外利用しないようにしてください
* @warning 一般の方はCircleListクラスをご利用ください
* @see CircleList
*/
class GOOGLEPLUSLIBRARY_API CircleContainer : boost::noncopyable
{
public:
	CircleContainer();

	/*!
	* @~english
	* @brief Add circle in the Container
	* @details This is not a function to create a make_shared<circle>
	* @param circle circle information that add to the Container
	* @~japanese
	* @brief コンテナにサークル情報を追加します
	* @details これはサークルを新規作成する関数ではありません
	* @param circle 追加するサークル情報
	*/
	static bool insert(const Circle& circle);
	static boost::signals2::signal<void (const Circle&)> onCircleinserted;

	static void updateItem(const Circle& circle);
	static boost::signals2::signal<void (const Circle&)> onCircleEdited;

	static bool erase(const std::wstring& comment_id);
	static boost::signals2::signal<void (const std::wstring&)> onCircleDeleted;
	
	static int count();

	/*!
	* @~english
	* @brief Get circle information from the Container
	* @details Returns null if the corresponding circle could not be found
	* @param circle_id ID of the circle information you want to get(e.g. 6e1ff5b889ea6c7e)
	* @return Circle information with the specified circle id
	* @~japanese
	* @brief コンテナからサークル情報を取得します
	* @details 該当するサークルが見つからなかった場合nullを返します
	* @param circle_id 取得したいサークルのID(例: 6e1ff5b889ea6c7e)
	* @return 指定したサークルIDを持つサークルの情報
	*/
	static const Circle* getByCircleID(const std::wstring& circle_id);

	const Circle* operator[](const std::wstring& circle_id);
	
	virtual ~CircleContainer();

private:
	static std::map<std::wstring, Circle> circle_container_;
	static ReadWriteMutex read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite