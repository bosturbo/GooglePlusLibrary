#include <Stream/StreamConnection.hpp>

#include <Stream/StreamConnectionImpl.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

StreamConnection::StreamConnection()
:impl_(new StreamConnectionImpl())
{
}

void StreamConnection::initialize(const wstring& account_id)
{
	if(!impl_)
	{
		return;
	}
	impl_->initialize(account_id);
}

void StreamConnection::initializeAsync(const wstring& account_id)
{
	if(!impl_)
	{
		return;
	}
	impl_->initializeAsync(account_id);
}

void StreamConnection::waitInitializeAsync()
{
	if(!impl_)
	{
		return;
	}
	impl_->waitInitializeAsync();
}

void StreamConnection::initializeAsyncThreadMethod(const wstring& account_id)
{
	if(!impl_)
	{
		return;
	}
	impl_->initializeAsyncThreadMethod(account_id);
}

void StreamConnection::update(const wstring& account_id)
{
	if(!impl_)
	{
		return;
	}
	impl_->update(account_id);
}

void StreamConnection::scriptSleep(long milliseconds)
{
	if(!impl_)
	{
		return;
	}
	impl_->scriptSleep(milliseconds);
}

void StreamConnection::cancelUpdate()
{
	if(!impl_)
	{
		return;
	}
	impl_->cancelUpdate();
}

bool StreamConnection::isCanceled()
{
	if(!impl_)
	{
		return true;
	}
	return impl_->isCanceled();
}


int StreamConnection::getConnectCount() const
{
	if(!impl_)
	{
		return -1;
	}
	return impl_->getConnectCount();
}

void StreamConnection::setConnectCount(int connect_count)
{
	if(!impl_)
	{
		return;
	}
	impl_->setConnectCount(connect_count);
}

int StreamConnection::getMaximumConnectCount() const
{
	if(!impl_)
	{
		return -1;
	}
	return impl_->getMaximumConnectCount();
}

void StreamConnection::setMaximumConnectCount(int maximum_connect_count)
{
	if(!impl_)
	{
		return;
	}
	impl_->setMaximumConnectCount(maximum_connect_count);
}

void StreamConnection::bindToScript(lua_State* lua_state)
{
	StreamConnectionImpl::bindToScript(lua_state);
}

StreamConnection::~StreamConnection()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
