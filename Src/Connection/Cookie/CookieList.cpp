#include <Connection/Cookie/CookieList.hpp>
#include <Connection/Cookie/Cookie.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

CookieList::CookieList()
{
}

string CookieList::escapeCookies() const
{
	string cookie_parameter("");
	bool first = true;
	auto it = cookie_list_.cbegin();
	while(it != cookie_list_.cend())
	{
		if(first == true)
		{
			first = false;
		}
		else
		{
			cookie_parameter += ";";
		}

		Cookie cookie = (*it);
		cookie_parameter += (cookie.getName() + "=" + cookie.getValue());

		++it;
	}
	return cookie_parameter;
}

void CookieList::clear()
{
	cookie_list_.clear();
}

CookieList::~CookieList()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite