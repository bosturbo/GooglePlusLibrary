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
#pragma warning (disable:4996)
#endif
#endif

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API NotificationList
{
protected:
	NotificationList();

public:
	void update();

public:
	static void bindToScript(lua_State* lua_state);

public:
	virtual ~NotificationList();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite