#include <Stream/StreamConnectionImpl.hpp>

#include <Connection/Connection.hpp>
#include <Connection/Cookie/Cookie.hpp>
#include <Connection/HttpResponse.hpp>
#include <Information/InformationContainer.hpp>
#include <Stream/StreamObserver.hpp>
#include <Utility/LuaScript.hpp>
#include <Utility/Utility.hpp>
#include <Json/JsonObject.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

void StreamConnectionImpl::initializeAsyncThreadMethod(const wstring& account_id)
{
	if(getConnectCount() > getMaximumConnectCount())
	{
		return;
	}
	
	LuaScript<bool(string)> lua_script("LuaScript/StreamInitialize.lua", "streamInitialize", [this](lua_State* lua_state)
	{
		Connection::bindToScript(lua_state);
		HttpResponse::bindToScript(lua_state);
		Utility::bindToScript(lua_state);
		InformationContainer::bindToScript(lua_state);
		JsonObject::bindToScript(lua_state);
		bindToScript(lua_state);
	});

	lua_script.onLoadingScriptFailed.connect([&](string message)
	{
		cout << "StreamInitialize.lua‚ðŽÀs‚Å‚«‚Ü‚¹‚ñ‚Å‚µ‚½\n" << endl;
		cout << "error : " << message << "\n" << endl;

		onInitializeFailed();

		setConnectCount(getConnectCount() + 1);
		initializeAsyncThreadMethod(account_id);
	});

	lua_script.onRunningScriptFailed.connect([&](string message)
	{
		cout << "error : " << message << "\n" << endl;

		onInitializeFailed();

		setConnectCount(getConnectCount() + 1);
		initializeAsyncThreadMethod(account_id);
	});

	auto result = lua_script(Utility::convertUnicodeToUTF8(account_id));
	if(result == false)
	{
		// stream initialize failed
		onInitializeFailed();

		setConnectCount(getConnectCount() + 1);
		initializeAsyncThreadMethod(account_id);
	}

	onInitializeSucceed();

	update_thread_.interrupt();
	boost::thread update_thread(boost::bind(&StreamConnectionImpl::update, this, account_id));
	update_thread_ = boost::move(update_thread);
}

void StreamConnectionImpl::test()
{
	cout << "test" << endl;
}

void StreamConnectionImpl::update(const wstring& account_id)
{
	//std::function<void(void)> func = std::bind(&StreamConnectionImpl::test, this);

	LuaScript<bool(string)> lua_script("LuaScript/StreamLoopUpdate.lua", "streamLoopUpdate", [&](lua_State* lua_state)
	{
		Connection::bindToScript(lua_state);
		HttpResponse::bindToScript(lua_state);
		Utility::bindToScript(lua_state);
		InformationContainer::bindToScript(lua_state);
		JsonObject::bindToScript(lua_state);
		StreamObserver::bindToScript(lua_state);
		bindToScript(lua_state);
	});
	
	while(!is_cancellation_pending_)
	{
		boost::this_thread::disable_interruption di;
		auto result = lua_script(Utility::convertUnicodeToUTF8(account_id));
		if(result == false)
		{
			// stream looping failed
			//is_cancellation_pending_ = true;
			initializeAsyncThreadMethod(account_id);
			return;
		}
	}
}

void StreamConnectionImpl::chunkedContentReceieved(const string& account_id, const string& content)
{
	int a = 3;
}

void StreamConnectionImpl::bindToScript(lua_State* lua_state)
{
	module(lua_state)
		[
			class_<StreamConnectionImpl>("StreamConnectionImpl")
			.def(constructor<>())
			.def("update", &StreamConnectionImpl::update)
			.def("test", &StreamConnectionImpl::test)

			.scope
			[
				def("chunkedContentReceieved", &StreamConnectionImpl::chunkedContentReceieved)
			]
		];
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite