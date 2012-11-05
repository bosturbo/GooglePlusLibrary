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

class JsonObject;
class ReadWriteMutex;

/*!
* @~english
* @brief Class to generate the information when added location information to share post and to get information when the location information has been attached to the post
* @attention This class will be dedicated to Mobile so can no longer post additional location information from the PC on Google+ from around April 2012
* @~japanese
* @brief ���e�ɕt������Ă���ʒu�����擾������A�ʒu���t�����e���V�F�A����Ƃ��̏��𐶐����邽�߂̃N���X
* @attention 2012�N4��������Google+��ł�PC����̈ʒu���t�����e���s���Ȃ��Ȃ����̂ł��̃N���X��Mobile��p�ƂȂ�܂�
*/
class GOOGLEPLUSLIBRARY_API AttachedLocation
{
	friend class AttachedLocationBase;
public:
	AttachedLocation();

public:
	double getLatitude() const;
private:
	double latitude_;

public:
	double getLongitude() const;
private:
	double longitude_;

public:
	std::wstring getLocationName() const;
private:
	std::wstring location_name_;

public:
	std::wstring getAddress() const;
private:
	std::wstring address_;

public:
	std::wstring getGoogleMapPageImageUrl() const;
private:
	std::wstring google_map_page_image_url_;

public:
	bool isCheckined() const;
private:
	bool is_checkined_;
public:
	virtual ~AttachedLocation();

private:
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite


