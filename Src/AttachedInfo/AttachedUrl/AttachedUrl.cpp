#include <AttachedInfo/AttachedUrl/AttachedUrl.hpp>

#include <Connection/Connection.hpp>
#include <Connection/Cookie/Cookie.hpp>
#include <Connection/HttpResponse.hpp>

#include <Information/InformationContainer.hpp>

#include <Account/MyAccount/MyAccount.hpp>
#include <Account/MyPageAccount.hpp>
#include <Utility/LuaScript.hpp>
#include <Utility/Utility.hpp>
#include <Json/JsonObject.hpp>
#include <Thread/ReadWriteMutex.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

AttachedUrl::AttachedUrl()
:page_title_(L""),
page_description_(L""),
page_favicon_url_(L""),
page_url_(L""),
thumbnail_url_(L""),
thumbnail_position_(-1),
read_write_mutex_(make_shared<ReadWriteMutex>())
{
}

AttachedUrl* AttachedUrl::create(const wstring& account_id, const wstring& url)
{
	return create(account_id, url, -1);
}

AttachedUrl* AttachedUrl::create(const MyAccount& my_account, const wstring& url)
{
	return create(my_account.getAccountID(), url, -1);
}

AttachedUrl* AttachedUrl::create(const MyPageAccount& my_page_account, const wstring& url)
{
	return create(my_page_account.getAccountID(), url, -1);
}

AttachedUrl* AttachedUrl::create(const wstring& account_id, const wstring& url, int thumbnail_number)
{
	LuaScript<bool(string, string, int)> lua_script("LuaScript/CreateAttachedUrl.lua", "createAttachedUrl", [](lua_State* lua_state)
	{
		Connection::bindToScript(lua_state);
		HttpResponse::bindToScript(lua_state);
		Utility::bindToScript(lua_state);
		InformationContainer::bindToScript(lua_state);
		JsonObject::bindToScript(lua_state);
	});

	auto result = lua_script(Utility::convertUnicodeToUTF8(account_id), Utility::convertUnicodeToUTF8(url), thumbnail_number);
	if(result == false)
	{
		// create AttachedUrl failed
		return nullptr;
	}

	shared_ptr<AttachedUrl> attached_url(make_shared<AttachedUrl>());
	return attached_url.get();
}

AttachedUrl* AttachedUrl::create(const MyAccount& my_account, const wstring& url, int thumbnail_number)
{
	return create(my_account.getAccountID(), url, thumbnail_number);
}

AttachedUrl* AttachedUrl::create(const MyPageAccount& my_page_account, const wstring& url, int thumbnail_number)
{
	return create(my_page_account.getAccountID(), url, thumbnail_number);
}

wstring AttachedUrl::getPageTitle() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return page_title_;
}

wstring AttachedUrl::getPageDescription() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return page_description_;
}

wstring AttachedUrl::getPageFaviconUrl() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return page_favicon_url_;
}

wstring AttachedUrl::getPageUrl() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return page_url_;
}

wstring AttachedUrl::getThumbnailUrl() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return thumbnail_url_;
}

void AttachedUrl::setThumbnailPosition(int thumbnail_position)
{
	ScopedWriteLock lock(*read_write_mutex_);
	thumbnail_position_ = thumbnail_position;
}

AttachedUrl::~AttachedUrl()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite