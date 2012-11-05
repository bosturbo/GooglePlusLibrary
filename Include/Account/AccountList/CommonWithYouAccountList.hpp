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

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

/*!
* @~english
* @brief Class in order to get a list of common friends
* @~japanese
* @brief 共通の友達のリストを取得するためのクラス
*/
class GOOGLEPLUSLIBRARY_API CommonWithYouAccountList
{
public:
	CommonWithYouAccountList();
	virtual ~CommonWithYouAccountList();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite