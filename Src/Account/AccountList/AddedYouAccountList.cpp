#include <Account/AccountList/AddedYouAccountList.hpp>
#include <Account/AccountList/AccountList.hpp>
#include <Account/AccountList/AccountContainer.hpp>
#include <Account/Account/Account.hpp>

#include <Connection/Connection.hpp>
#include <Connection/Cookie/Cookie.hpp>
#include <Connection/HttpResponse.hpp>
#include <Utility/Utility.hpp>
#include <Information/InformationContainer.hpp>

#include <Utility/LuaScript.hpp>

#include <Json/JsonObject.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

AddedYouAccountList::AddedYouAccountList()
:account_list_(make_shared<AccountList>())
{
}

void AddedYouAccountList::update()
{
	updateAsync();
	waitupdateAsync();
}

void AddedYouAccountList::updateAsync()
{
	boost::thread update_thread(boost::bind(&AddedYouAccountList::updateAsyncThreadMethod, this));
	update_thread_ = boost::move(update_thread);
}

void AddedYouAccountList::waitupdateAsync()
{
	update_thread_.join();
}

void AddedYouAccountList::updateAsyncThreadMethod()
{
	LuaScript<bool(string)> lua_script("LuaScript/UpdateAddedYouAccountList.lua", "updateAddedYouAccountList", [](lua_State* lua_state)
	{
		Connection::bindToScript(lua_state);
		HttpResponse::bindToScript(lua_state);
		Utility::bindToScript(lua_state);
		InformationContainer::bindToScript(lua_state);
		JsonObject::bindToScript(lua_state);
	});

	auto result = lua_script(Utility::convertUnicodeToUTF8(getMyAccountID()));
	if(result == true)
	{
		// update added account list failed
		return;
	}

	onUpdateCompleted();
}

wstring AddedYouAccountList::getMyAccountID() const
{
	return account_list_->getMyAccountID();
}

void AddedYouAccountList::setMyAccountID(const wstring& my_account_id)
{
	account_list_->setMyAccountID(my_account_id);
}

const Account* AddedYouAccountList::getByAccountID(const wstring& account_id) const
{
	return account_list_->getByAccountID(account_id);
}

const Account* AddedYouAccountList::getByIndex(int index) const
{
	return account_list_->getByIndex(index);
}

const Account* AddedYouAccountList::operator[](const wstring& account_id) const
{
	return account_list_->getByAccountID(account_id);
}

const Account* AddedYouAccountList::operator[](int index) const
{
	return account_list_->getByIndex(index);
}

AddedYouAccountList::~AddedYouAccountList()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite