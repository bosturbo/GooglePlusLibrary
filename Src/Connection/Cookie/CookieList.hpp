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
#include <vector>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Cookie;

class GOOGLEPLUSLIBRARY_API CookieList
{
public:
	CookieList();

	std::string escapeCookies() const;

	void clear();

	virtual ~CookieList();
private:
	std::vector<Cookie> cookie_list_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite