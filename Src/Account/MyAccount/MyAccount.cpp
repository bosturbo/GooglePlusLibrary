
#include <Account/MyAccount/MyAccount.hpp>

#include <Account/MyAccount/Impl/MyAccountImpl.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

MyAccount::MyAccount()
:impl_(make_shared<MyAccountImpl>())
{
}

void MyAccount::login(const wstring& mail_address, const wstring& password)
{
	loginAsync(mail_address, password);
	waitLoginAsync();
}

void MyAccount::loginAsync(const wstring& mail_address, const wstring& password)
{
	assert(impl_);
	impl_->loginAsync(mail_address, password);
}

void MyAccount::waitLoginAsync()
{
	assert(impl_);
	impl_->waitLoginAsync();
}

void MyAccount::loginAsyncThreadMethod(const wstring& mail_address, const wstring& password)
{
	assert(impl_);
	impl_->loginAsyncThreadMethod(mail_address, password);
}

wstring MyAccount::getMailAddress() const
{
	assert(impl_);
	return impl_->getMailAddress();
}

wstring MyAccount::getAccountID() const
{
	assert(impl_);
	return impl_->getAccountID();
}

wstring MyAccount::getAccountName() const
{
	assert(impl_);
	return impl_->getAccountName();
}

void MyAccount::sharePost(const wstring& message, const ShareRangeList& share_range, 
	shared_ptr<AttachedSearchResult> attached_search_result)
{
	assert(impl_);
	impl_->sharePost(message, share_range, attached_search_result);
}

void MyAccount::sharePost(const wstring& message, const ShareRangeList& share_range, const AttachedAlbum& attached_album, 
	shared_ptr<AttachedSearchResult> attached_search_result)
{
	assert(impl_);
	impl_->sharePost(message, share_range, attached_album, attached_search_result);
}

void MyAccount::sharePost(const wstring& message, const ShareRangeList& share_range, const AttachedCircle& attached_circle,
	shared_ptr<AttachedSearchResult> attached_search_result)
{
	assert(impl_);
	impl_->sharePost(message, share_range, attached_circle, attached_search_result);
}

void MyAccount::sharePost(const wstring& message, const ShareRangeList& share_range, const AttachedImageVideo& attached_image_video,
	shared_ptr<AttachedSearchResult> attached_search_result)
{
	assert(impl_);
	impl_->sharePost(message, share_range, attached_image_video, attached_search_result);
}

void MyAccount::sharePost(const wstring& message, const ShareRangeList& share_range, const AttachedUrl& attached_url,
	shared_ptr<AttachedSearchResult> attached_search_result)
{
	assert(impl_);
	impl_->sharePost(message, share_range, attached_url, attached_search_result);
}

void MyAccount::sharePost(const wstring& message, const ShareRangeList& share_range, const AttachedYouTubePlaylist& attached_youtube_playlist,
	shared_ptr<AttachedSearchResult> attached_search_result)
{
	assert(impl_);
	impl_->sharePost(message, share_range, attached_youtube_playlist, attached_search_result);
}

AddedAccountList* MyAccount::getAddedAccountList() const
{
	if(!impl_)
	{
		return nullptr;
	}
	return impl_->getAddedAccountList();
}

AddedYouAccountList* MyAccount::getAddedYouAccountList() const
{
	if(!impl_)
	{
		return nullptr;
	}
	return impl_->getAddedYouAccountList();
}

Stream* MyAccount::getMainStream() const
{
	if(!impl_)
	{
		return nullptr;
	}
	return impl_->getMainStream();
}

const Account* MyAccount::toAccount()
{
	if(!impl_)
	{
		return nullptr;
	}
	return impl_->toAccount();
}

MyAccount::~MyAccount()
{
}

} // namespace GooglePlusLibrary
} // namespace Gplusnasite
