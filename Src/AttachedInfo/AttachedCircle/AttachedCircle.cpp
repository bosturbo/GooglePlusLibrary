#include <AttachedInfo/AttachedCircle/AttachedCircle.hpp>
#include <Circle/Circle.hpp>
#include <Account/MyAccount/MyAccount.hpp>

#include <Connection/Connection.hpp>
#include <Connection/Cookie/Cookie.hpp>
#include <Connection/HttpResponse.hpp>

#include <Information/InformationContainer.hpp>

#include <Utility/LuaScript.hpp>
#include <Utility/Utility.hpp>

#include <Json/JsonObject.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

AttachedCircle::AttachedCircle()
:account_list_(make_shared<AccountList>()),
read_write_mutex_(make_shared<ReadWriteMutex>())
{
}

AttachedCircle* AttachedCircle::create(const wstring& my_account_id, const wstring& circle_id, bool is_include_yourself)
{
	LuaScript<bool(string, string, bool)> lua_script("LuaScript/CreateAttachedCircle.lua", "createAttachedCircle", [](lua_State* lua_state)
	{
		Connection::bindToScript(lua_state);
		HttpResponse::bindToScript(lua_state);
		Utility::bindToScript(lua_state);
		InformationContainer::bindToScript(lua_state);
		JsonObject::bindToScript(lua_state);
	});

	auto result = lua_script(Utility::convertUnicodeToUTF8(my_account_id), Utility::convertUnicodeToUTF8(circle_id), is_include_yourself);
	if(result == false)
	{
		// create AttachedCircle failed
		return nullptr;
	}

	shared_ptr<AttachedCircle> attached_circle(make_shared<AttachedCircle>());
	return attached_circle.get();
}

AttachedCircle* AttachedCircle::create(const wstring& my_account_id, const Circle& circle, bool is_include_yourself)
{
	return create(my_account_id, circle.getCircleID(), is_include_yourself);
}

AttachedCircle* AttachedCircle::create(const MyAccount& my_account, const wstring& circle_id, bool is_include_yourself)
{
	return create(my_account.getAccountID(), circle_id, is_include_yourself);
}

AttachedCircle* AttachedCircle::create(const MyAccount& my_account, const Circle& circle, bool is_include_yourself)
{
	return create(my_account.getAccountID(), circle.getCircleID(), is_include_yourself);
}

const AccountList* AttachedCircle::getAccountList() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return account_list_.get();
}

AttachedCircle::~AttachedCircle()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite