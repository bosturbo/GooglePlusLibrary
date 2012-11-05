#include <Thread/ReadWriteMutex.hpp>
#include <Thread/ReadWriteMutexImpl.hpp>

#include <iostream>

using namespace std;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

ReadWriteMutex::ReadWriteMutex(unsigned int const max_readers)
:impl_(make_shared<ReadWriteMutexImpl>(max_readers))
{
	assert(impl_);
}

ScopedReadLock::ScopedReadLock(ReadWriteMutex& mutex)
:impl_(make_shared<ScopedReadLockImpl>(*(mutex.impl_)))
{
	assert(impl_);
}

ScopedReadLock::~ScopedReadLock()
{
}

void ReadWriteMutex::acquire(boost::recursive_mutex::scoped_lock& lock, unsigned int const permits)
{
	assert(impl_);
	impl_->acquire(lock, permits);
}

void ReadWriteMutex::release(boost::recursive_mutex::scoped_lock& lock, unsigned int const permits)
{
	assert(impl_);
	impl_->release(lock, permits);
}


UpgradableLock::UpgradableLock(ReadWriteMutex& mutex, unsigned int const permits)
:impl_(make_shared<UpgradableLockImpl>(*(mutex.impl_), permits))
{
	assert(impl_);
}

UpgradableLock::~UpgradableLock()
{
}

void UpgradableLock::upgradeToWriteLock()
{
	assert(impl_);
	impl_->upgradeToWriteLock();
}

void UpgradableLock::downgradeToReadLock()
{
	assert(impl_);
	impl_->downgradeToReadLock();
}

UpgradableReadLock::UpgradableReadLock(ReadWriteMutex& mutex)
:impl_(make_shared<UpgradableReadLockImpl>(*(mutex.impl_)))
{
	assert(impl_);
}

void UpgradableReadLock::upgradeToWriteLock()
{
	assert(impl_);
	impl_->upgradeToWriteLock();
}
void UpgradableReadLock::downgradeToReadLock()
{
	assert(impl_);
	impl_->downgradeToReadLock();
}

UpgradableReadLock::~UpgradableReadLock()
{
}

ScopedWriteLock::ScopedWriteLock(ReadWriteMutex& mutex)
:impl_(make_shared<ScopedWriteLockImpl>(*(mutex.impl_)))
{
	assert(impl_);
}

ScopedWriteLock::~ScopedWriteLock()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite

