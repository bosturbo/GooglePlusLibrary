
#include <Account/MyAccount/Impl/MyAccountImpl.hpp>
#include <Account/Account/Account.hpp>
#include <Account/Account/AccountSetter.hpp>
#include <Account/AccountList/AddedAccountList.hpp>
#include <Account/AccountList/AddedYouAccountList.hpp>
// #include <Share/ShareRangeList.hpp>
// #include <AttachedInfo/AttachedAlbum/AttachedAlbum.hpp>
// #include <AttachedInfo/AttachedCircle/AttachedCircle.hpp>
// #include <AttachedInfo/AttachedImageVideo/AttachedImageVideo.hpp>
// #include <AttachedInfo/AttachedSearchResult/AttachedSearchResult.hpp>
// #include <AttachedInfo/AttachedUrl/AttachedUrl.hpp>
// #include <AttachedInfo/AttachedYouTubePlaylist/AttachedYouTubePlaylist.hpp>

#include <Connection/Connection.hpp>
#include <Connection/Cookie/Cookie.hpp>
#include <Connection/HttpResponse.hpp>
#include <Utility/Utility.hpp>

#include <Connection/Talkgadget/TalkgadgetConnection.hpp>
#include <Information/InformationContainer.hpp>
#include <Stream/Stream.hpp>
#include <Stream/Post/PostContainer/PostContainer.hpp>
// 
#include <Utility/LuaScript.hpp>

#include <Json/JsonObject.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

MyAccountImpl::MyAccountImpl()
:account_setter_(make_shared<AccountSetter>()),
main_stream_(make_shared<Stream>()),
read_write_mutex_(make_shared<ReadWriteMutex>())
{
}

void MyAccountImpl::loginAsync(const wstring& mail_address, const wstring& password)
{
	mail_address_ = mail_address;
	boost::thread login_thread(boost::bind(&MyAccountImpl::loginAsyncThreadMethod, this, mail_address, password));

	login_thread_ = boost::move(login_thread);
}

void MyAccountImpl::waitLoginAsync()
{
	login_thread_.join();
}

void MyAccountImpl::loginAsyncThreadMethod(const wstring& mail_address, const wstring& password)
{
	LuaScript<string(string, string)> lua_script("LuaScript/Login.lua", "login", [](lua_State* lua_state)
	{
		Connection::bindToScript(lua_state);
		HttpResponse::bindToScript(lua_state);
		Utility::bindToScript(lua_state);
		InformationContainer::bindToScript(lua_state);
		JsonObject::bindToScript(lua_state);
	});
	
	wstring account_id = Utility::convertUTF8ToUnicode(lua_script(Utility::convertUnicodeToUTF8(mail_address.c_str()), Utility::convertUnicodeToUTF8(password.c_str())));
	if(account_id.empty())
	{
		// login failed
		return;
	}
	account_setter_->setAccountID(account_id);
	
	account_setter_->result()->getAddedYouAccountList()->setMyAccountID(account_id);

	account_setter_->result()->getAddedYouAccountList()->setMyAccountID(account_id);

	PostContainer::onPostInserted.connect([&](const Post& post)
	{
		getMainStream()->add(post);
	});
		
	talkgadget_connection_ = make_shared<talkgadgetConnection>();
	talkgadget_connection_->connect(account_id, talkgadgetConnection::ConnectionMode::Homepage);

	onLoginCompleted();
}

wstring MyAccountImpl::getMailAddress() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return mail_address_;
}

wstring MyAccountImpl::getAccountID() const
{
	return account_setter_->result()->getAccountID();
}

wstring MyAccountImpl::getAccountName() const
{
	return account_setter_->result()->getAccountName();
}

void MyAccountImpl::sharePost(const wstring& message, const ShareRangeList& share_range, 
	shared_ptr<AttachedSearchResult> attached_search_result)
{

}

void MyAccountImpl::sharePost(const wstring& message, const ShareRangeList& share_range, const AttachedAlbum& attached_album, 
	shared_ptr<AttachedSearchResult> attached_search_result)
{

}

void MyAccountImpl::sharePost(const wstring& message, const ShareRangeList& share_range, const AttachedCircle& attached_circle,
	shared_ptr<AttachedSearchResult> attached_search_result)
{

}

void MyAccountImpl::sharePost(const wstring& message, const ShareRangeList& share_range, const AttachedImageVideo& attached_image_video,
	shared_ptr<AttachedSearchResult> attached_search_result)
{

}

void MyAccountImpl::sharePost(const wstring& message, const ShareRangeList& share_range, const AttachedUrl& attached_url,
	shared_ptr<AttachedSearchResult> attached_search_result)
{

}

void MyAccountImpl::sharePost(const wstring& message, const ShareRangeList& share_range, const AttachedYouTubePlaylist& attached_youtube_playlist,
	shared_ptr<AttachedSearchResult> attached_search_result)
{

}

AddedAccountList* MyAccountImpl::getAddedAccountList() const
{
	return account_setter_->result()->getAddedAccountList();
}

AddedYouAccountList* MyAccountImpl::getAddedYouAccountList() const
{
	return account_setter_->result()->getAddedYouAccountList();
}

Stream* MyAccountImpl::getMainStream() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return main_stream_.get();
}

const Account* MyAccountImpl::toAccount()
{
	ScopedReadLock lock(*read_write_mutex_);
	return account_setter_.get()->result().get();
}

MyAccountImpl::~MyAccountImpl()
{
}

} // namespace GooglePlusLibrary
} // namespace Gplusnasite
