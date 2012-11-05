#include <Thread/ReadWriteMutexImpl.hpp>

#include <iostream>

using namespace std;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

ReadWriteMutexImpl::ReadWriteMutexImpl(unsigned int const max_readers)
: max_readers_(max_readers),
available_(max_readers_),
writing_(false),
mutex_(),
condition_()
{
}

void ReadWriteMutexImpl::acquire(boost::recursive_mutex::scoped_lock& lock, unsigned int const permits)
{
	unsigned int acquired = 0;
	while (true)
	{
		unsigned int const num = min(available_, permits);
		acquired += num;
		available_ -= num;
		if (acquired == permits)
		{
			break;
		}
		else
		{
			condition_.wait(lock);
		}
	}
}

void ReadWriteMutexImpl::release(boost::recursive_mutex::scoped_lock& lock, unsigned int const permits)
{
	available_ += permits;
	assert(available_ <= max_readers_ && "unlock ‚ÌŒÄ‚Ño‚µ‚ª•s³‚Å‚·");
	condition_.notify_all();
}

ScopedReadLockImpl::ScopedReadLockImpl(ReadWriteMutexImpl& mutex)
: mutex_(mutex)
{
	boost::recursive_mutex::scoped_lock lock(mutex.mutex_);
	mutex.acquire(lock, 1);
#ifdef SHOW_LOCK_STATE
	cout << "ReadLocked" << endl;
#endif
}

ScopedReadLockImpl::~ScopedReadLockImpl()
{
	boost::recursive_mutex::scoped_lock lock(mutex_.mutex_);
	mutex_.release(lock, 1);
#ifdef SHOW_LOCK_STATE
	cout << "ReadUnlocked" << endl;
#endif
}

UpgradableLockImpl::UpgradableLockImpl(ReadWriteMutexImpl& mutex, unsigned int const permits)
:mutex_(mutex)
,permits_(permits)
{
	boost::recursive_mutex::scoped_lock lock(mutex.mutex_);
	while (mutex.writing_)
	{
		mutex.condition_.wait(lock);
	}
	mutex.writing_ = true;
	mutex.acquire(lock, permits);
}

UpgradableLockImpl::~UpgradableLockImpl()
{
	boost::recursive_mutex::scoped_lock lock(mutex_.mutex_);
	mutex_.writing_ = false;
	mutex_.release(lock, permits_);
}

void UpgradableLockImpl::upgradeToWriteLock()
{
	if (permits_ == 1)
	{
		boost::recursive_mutex::scoped_lock lock(mutex_.mutex_);
		mutex_.acquire(lock, mutex_.max_readers_ - 1);
		permits_ = mutex_.max_readers_;
#ifdef SHOW_LOCK_STATE
		cout << "upgradeToWriteLocked" << endl;
#endif
	}
}

void UpgradableLockImpl::downgradeToReadLock()
{
	if (mutex_.max_readers_ == permits_)
	{
		boost::recursive_mutex::scoped_lock lock(mutex_.mutex_);
		mutex_.release(lock, permits_ - 1);
		permits_ = 1;

#ifdef SHOW_LOCK_STATE
		cout << "downgradeToReadLocked" << endl;
#endif
	}
}

UpgradableReadLockImpl::UpgradableReadLockImpl(ReadWriteMutexImpl& mutex)
:UpgradableLockImpl(mutex, 1)
{
#ifdef SHOW_LOCK_STATE
	cout << "UpgradableReadLockImpled" << endl;
#endif
}

UpgradableReadLockImpl::~UpgradableReadLockImpl()
{
#ifdef SHOW_LOCK_STATE
	cout << "UpgradableReadUnlocked" << endl;
#endif
}

ScopedWriteLockImpl::ScopedWriteLockImpl(ReadWriteMutexImpl& mutex)
:UpgradableLockImpl(mutex, mutex.max_readers_)
{
#ifdef SHOW_LOCK_STATE
	cout << "WriteLocked" << endl;
#endif
}

ScopedWriteLockImpl::~ScopedWriteLockImpl()
{
#ifdef SHOW_LOCK_STATE
	cout << "WriteUnlocked" << endl;
#endif
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite

