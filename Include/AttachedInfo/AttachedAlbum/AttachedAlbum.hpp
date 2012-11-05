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
#include <list>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class ReadWriteMutex;

/*!
* @~english
* @brief Class to generate the information when added album to share post and to get information when the album has been attached to the post
* @~japanese
* @brief 投稿に付加されているアルバム情報を取得したり、アルバム付加投稿をシェアするときの情報を生成するためのクラス
*/
class GOOGLEPLUSLIBRARY_API AttachedAlbum
{
	friend class AttachedAlbumBase;
public:
	AttachedAlbum();
	AttachedAlbum(std::wstring album_name);

public:

	/*!
	* @~english
	* @brief Gets the name of the album
	* @return Album name is set
	* @~japanese
	* @brief アルバム名を取得します
	* @return 設定されたアルバム名
	*/
	std::wstring getAlbumName() const;
private:
	std::wstring album_name_;

public:
	/*!
	* @~english
	* @brief Adds a file to the album
	* @param file_path The path of the file you want to add
	* @~japanese
	* @brief アルバムにファイルを追加します
	* @param file_path 追加したいファイルのパス
	*/
	void addFile(const std::wstring& file_path);

	/*!
	* @~english
	* @brief remove specified file from the album
	* @param file_name The name of the file you want to delete
	* @~japanese
	* @brief 指定したファイルをアルバムから削除します
	* @param file_name 削除したいファイルの名前
	*/
	void removeFile(const std::wstring& file_name);

	/*!
	* @~english
	* @brief Upload the album
	* @param account_id account id(e.g. 116324207729009185938)
	* @~japanese
	* @brief アルバムをアップロードします
	* @param account_id アカウントID(例: 116324207729009185938)
	*/
	void upload(const std::wstring& account_id);

public:
	virtual ~AttachedAlbum();

private:

	std::list<std::wstring> file_list_;
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite