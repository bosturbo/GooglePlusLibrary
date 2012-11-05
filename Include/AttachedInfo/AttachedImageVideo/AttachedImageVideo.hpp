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

#include <memory>
#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class AttachedAlbum;

/*!
* @~english
* @brief Class to generate the information when added image or video to share post and to get information when the image or video has been attached to the post
* @~japanese
* @brief 投稿に付加されているイメージやビデオの情報を取得したり、イメージやビデオの付加投稿をシェアするときの情報を生成するためのクラス
*/
class GOOGLEPLUSLIBRARY_API AttachedImageVideo
{
	friend class AttachedImageVideoBase;
public:
	AttachedImageVideo();

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

	virtual ~AttachedImageVideo();

private:
	std::shared_ptr<AttachedAlbum> attached_album_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite