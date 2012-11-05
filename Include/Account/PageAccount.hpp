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
* @brief Class to retrieve the information of Google+ Page
* @~japanese
* @brief Google+ Page‚Ìî•ñ‚ğæ“¾‚·‚é‚½‚ß‚ÌƒNƒ‰ƒX
*/
class GOOGLEPLUSLIBRARY_API PageAccount
{
public:
	PageAccount();
	virtual ~PageAccount();
};

} // namespace GooglePlusLibrary
} // namespace Gplusnasite