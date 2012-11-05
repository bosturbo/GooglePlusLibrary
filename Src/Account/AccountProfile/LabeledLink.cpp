#include <Account/AccountProfile/LabeledLink.hpp>
#include <Thread/ReadWriteMutex.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

LabeledLink::LabeledLink(const wstring& label, const wstring& url)
:label_(label),
url_(url),
read_write_mutex_(make_shared<ReadWriteMutex>())
{
}

wstring LabeledLink::getLabel() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return label_;
}

void LabeledLink::setLabel(const wstring& label)
{
	ScopedWriteLock lock(*read_write_mutex_);
	label_ = label;
}

wstring LabeledLink::getUrl() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return url_;
}

void LabeledLink::setUrl(const wstring& url)
{
	ScopedWriteLock lock(*read_write_mutex_);
	url_ = url;
}

LabeledLink::~LabeledLink()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite