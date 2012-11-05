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

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GroupChat;

class GOOGLEPLUSLIBRARY_API MyHangout
{
public:
	MyHangout();
	virtual ~MyHangout();

private:
	std::shared_ptr<GroupChat> group_chat_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite