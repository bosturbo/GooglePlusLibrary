#include <Stream/Stream.hpp>
#include <Stream/StreamImpl.hpp>

#include <boost/bind.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

Stream::Stream()
:impl_(make_shared<StreamImpl>())
{
	//onPostAdded.connect(boost::bind(&StreamImpl::onPostAdded, impl_, _1));
}

wstring Stream::getAccountID() const
{
	assert(impl_);
	return impl_->getAccountID();
}

void Stream::setAccountID(const wstring& account_id)
{
	assert(impl_);
	impl_->setAccountID(account_id);
}

wstring Stream::getTargetCircleID() const
{
	assert(impl_);
	return impl_->getTargetCircleID();
}

void Stream::setTargetCircleID(const wstring& target_circle_id)
{
	assert(impl_);
	impl_->setTargetCircleID(target_circle_id);
}

void Stream::refreshupdate()
{
	assert(impl_);
	impl_->refreshupdate();
}

bool Stream::add(const wstring& post_id)
{
	assert(impl_);
	return impl_->add(post_id);
}

bool Stream::add(const Post& post)
{
	assert(impl_);
	return impl_->add(post);
}

bool Stream::remove(const wstring& post_id)
{
	assert(impl_);
	return impl_->remove(post_id);
}

bool Stream::contain(const wstring& post_id) const
{
	assert(impl_);
	return impl_->contain(post_id);
}

shared_ptr<Post> Stream::getByPostID(const wstring& post_id) const
{
	assert(impl_);
	return impl_->getByPostID(post_id);
}

shared_ptr<Post> Stream::getByIndex(int index) const
{
	assert(impl_);
	return impl_->getByIndex(index);
}

shared_ptr<Post> Stream::operator[](const wstring& post_id) const
{
	return getByPostID(post_id);
}

shared_ptr<Post> Stream::operator[](int index) const
{
	return getByIndex(index);
}

int Stream::count() const
{
	assert(impl_);
	return impl_->count();
}

Stream::~Stream()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite