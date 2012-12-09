#include <Stream/StreamConnectionImpl.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

StreamConnectionImpl::StreamConnectionImpl()
:is_cancellation_pending_(false),
connect_count_(0),
maximum_connect_count_(5)
{
}

void StreamConnectionImpl::initialize(const wstring& account_id)
{
	if(account_id.empty())
	{
		return;
	}

	initializeAsync(account_id);
	waitInitializeAsync();
}

void StreamConnectionImpl::initializeAsync(const wstring& account_id)
{
	if(account_id.empty())
	{
		return;
	}

	boost::thread connect_thread(boost::bind(&StreamConnectionImpl::initializeAsyncThreadMethod, this, account_id));
	initialize_thread_ = boost::move(connect_thread);
}

void StreamConnectionImpl::waitInitializeAsync()
{
	initialize_thread_.join();
}

void StreamConnectionImpl::cancelUpdate()
{
	is_cancellation_pending_ = true;
}

bool StreamConnectionImpl::isCanceled()
{
	return is_cancellation_pending_;
}

int StreamConnectionImpl::getConnectCount() const
{
	return connect_count_;
}

void StreamConnectionImpl::setConnectCount(int connect_count)
{
	connect_count_ = connect_count;
}

int StreamConnectionImpl::getMaximumConnectCount() const
{
	return maximum_connect_count_;
}

void StreamConnectionImpl::setMaximumConnectCount(int maximum_connect_count)
{
	maximum_connect_count_ = maximum_connect_count;
}

StreamConnectionImpl::~StreamConnectionImpl()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite