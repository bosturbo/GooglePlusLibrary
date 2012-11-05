#include <Hangout/HangoutList.hpp>

#include <Utility/Utility.hpp>
#include <Connection/Connection.hpp>
#include <Connection/Cookie/Cookie.hpp>
#include <Connection/HttpResponse.hpp>
#include <Information/InformationContainer.hpp>
#include <Hangout/HangoutConnection.hpp>
#include <Json/JsonObject.hpp>

#include <lua.hpp>
#include <luabind/luabind.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

HangoutList::HangoutList()
{
}

wstring HangoutList::getAccountID() const
{
	return my_account_id_;
}

void HangoutList::setAccountID(const wstring& my_account_id)
{
	my_account_id_ = my_account_id;
}

void HangoutList::create()
{
}

void HangoutList::update()
{

}

HangoutList::~HangoutList()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite