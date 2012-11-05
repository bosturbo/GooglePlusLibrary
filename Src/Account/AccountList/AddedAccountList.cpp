#include <Account/AccountList/AddedAccountList.hpp>
#include <Account/AccountList/AccountList.hpp>
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

AddedAccountList::AddedAccountList()
:account_list_(make_shared<AccountList>())
{
}

void AddedAccountList::update()
{
	updateAsync();
	waitupdateAsync();
}

void AddedAccountList::updateAsync()
{
	boost::thread update_thread(boost::bind(&AddedAccountList::updateAsyncThreadMethod, this));
	update_thread_ = boost::move(update_thread);
}

void AddedAccountList::waitupdateAsync()
{
	update_thread_.join();
}

void AddedAccountList::updateAsyncThreadMethod()
{
	LuaScript<bool(string)> lua_script("LuaScript/UpdateAddedAccountList.lua", "updateAddedAccountList", [](lua_State* lua_state)
	{
		Connection::bindToScript(lua_state);
		HttpResponse::bindToScript(lua_state);
		Utility::bindToScript(lua_state);
		InformationContainer::bindToScript(lua_state);
		JsonObject::bindToScript(lua_state);
	});

	auto result = lua_script(Utility::convertUnicodeToUTF8(getMyAccountID()));
	if(result == false)
	{
		// update added account list failed
		return;
	}

	onUpdateCompleted();
}

wstring AddedAccountList::getMyAccountID() const
{
	return account_list_->getMyAccountID();
}

void AddedAccountList::setMyAccountID(const wstring& my_account_id)
{
	account_list_->setMyAccountID(my_account_id);
}

const Account* AddedAccountList::getByAccountID(const wstring& account_id) const
{
	return account_list_->getByAccountID(account_id);
}

const Account* AddedAccountList::getByIndex(int index) const
{
	return account_list_->getByIndex(index);
}

const Account* AddedAccountList::operator[](const wstring& account_id) const
{
	return account_list_->getByAccountID(account_id);
}

const Account* AddedAccountList::operator[](int index) const
{
	return account_list_->getByIndex(index);
}

AddedAccountList::~AddedAccountList()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite