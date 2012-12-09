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

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class HttpResponse;

class GOOGLEPLUSLIBRARY_API StreamObserver
{
public:
	StreamObserver();
	
public:
	HttpResponse get(const std::string& account_id, const std::string& url);

	void scriptSleep(long milliseconds);

	static void bindToScript(lua_State* lua_state);

	virtual ~StreamObserver();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite