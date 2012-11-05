#include <Stream/Post/Post.hpp>

#include <Share/ShareRangeList.hpp>
#include <Stream/Comment/CommentList/CommentList.hpp>

#include <Stream/Post/PostImpl.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

Post::Post()
:impl_(make_shared<PostImpl>())
{
}

Post::Post(const Post& post)
:impl_(post.impl_)
{
}

wstring Post::getPostType() const
{
	assert(impl_);
	return impl_->getPostType();
}

wstring Post::getAuthorName() const
{
	assert(impl_);
	return impl_->getAuthorName();
}

wstring Post::getAccountID() const
{
	assert(impl_);
	return impl_->getAccountID();
}

wstring Post::getAccountImageUrl() const
{
	assert(impl_);
	return impl_->getAccountImageUrl();
}

bool Post::isResharedPost() const
{
	assert(impl_);
	return impl_->isResharedPost();
}

wstring Post::getOriginalPostID() const
{
	assert(impl_);
	return impl_->getOriginalPostID();
}

wstring Post::getOriginalPostMessage() const
{
	assert(impl_);
	return impl_->getOriginalpostMessage();
}

wstring Post::getOriginalPostUrl() const
{
	assert(impl_);
	return impl_->getOriginalPostUrl();
}

wstring Post::getPostID() const
{
	assert(impl_);
	return impl_->getPostID();
}

wstring Post::getPostUrl() const
{
	assert(impl_);
	return impl_->getPostUrl();
}

wstring Post::getPlusOneID() const
{
	assert(impl_);
	return impl_->getPlusOneID();
}

boost::posix_time::ptime Post::getPostTime() const
{
	assert(impl_);
	return impl_->getPostTime();
}

bool Post::isPublicPost() const
{
	assert(impl_);
	return impl_->isPublicPost();
}

wstring Post::getMessage() const
{
	assert(impl_);
	return impl_->getMessage();
}

bool Post::isMobilePost() const
{
	assert(impl_);
	return impl_->isMobilePost();
}

bool Post::isCommentDisabled() const
{
	assert(impl_);
	return impl_->isCommentDisabled();
}

bool Post::isLockdPost() const
{
	assert(impl_);
	return impl_->isLockdPost();
}

bool Post::isMyPost() const
{
	assert(impl_);
	return impl_->isMyPost();
}

bool Post::isEdited() const
{
	assert(impl_);
	return impl_->isEdited();
}

boost::posix_time::ptime Post::getLastEditedTime() const
{
	assert(impl_);
	return impl_->getLastEditedTime();
}

void Post::mutePost(bool is_mute)
{
	assert(impl_);
	impl_->mutePost(is_mute);
}

void Post::reshare(const wstring& my_account_id, const wstring& message, const ShareRangeList& share_range)
{
	assert(impl_);
	impl_->reshare(my_account_id, message, share_range);
}

CommentList* Post::getCommentList() const
{
	assert(impl_);
	return impl_->getCommentList();
}

Post& Post::operator=(const Post& rhs)
{
	assert(rhs.impl_);
	impl_ = rhs.impl_;
	assert(impl_);
	return *this;
}

Post::~Post()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
