#include <Thread/ReadWriteMutex.hpp>

#include <iostream>

// show lock state on standard output
//#define SHOW_LOCK_STATE

using namespace std;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

ReadWriteMutex::ReadWriteMutex(unsigned int const max_readers)
: max_readers_(max_readers),
available_(max_readers_),
writing_(false),
mutex_(),
condition_()
{
}

ScopedReadLock::ScopedReadLock(ReadWriteMutex& mutex)
: mutex_(mutex)
{
	boost::recursive_mutex::scoped_lock lock(mutex.mutex_);
	mutex.acquire(lock, 1);
#ifdef SHOW_LOCK_STATE
	cout << "ReadLocked" << endl;
#endif
}

ScopedReadLock::~ScopedReadLock()
{
	boost::recursive_mutex::scoped_lock lock(mutex_.mutex_);
	mutex_.release(lock, 1);
#ifdef SHOW_LOCK_STATE
	cout << "ReadUnlocked" << endl;
#endif
}

void ReadWriteMutex::acquire(boost::recursive_mutex::scoped_lock& lock, unsigned int const permits)
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

void ReadWriteMutex::release(boost::recursive_mutex::scoped_lock& lock, unsigned int const permits)
{
	available_ += permits;
	//cout << "available_:" << available_ << L" max_readers_:" << max_readers_ << endl;
	assert(available_ <= max_readers_ && "unlock ‚ÌŒÄ‚Ño‚µ‚ª•s³‚Å‚·");
	condition_.notify_all();
}


UpgradableLock::UpgradableLock(ReadWriteMutex& mutex, unsigned int const permits)
: mutex_(mutex)
, permits_(permits)
{
	boost::recursive_mutex::scoped_lock lock(mutex.mutex_);
	while (mutex.writing_)
	{
		mutex.condition_.wait(lock);
	}
	mutex.writing_ = true;
	mutex.acquire(lock, permits);
}

UpgradableLock::~UpgradableLock()
{
	boost::recursive_mutex::scoped_lock lock(mutex_.mutex_);
	mutex_.writing_ = false;
	mutex_.release(lock, permits_);
}

void UpgradableLock::upgradeToWriteLock()
{
	if (permits_ == 1)
	{
		boost::recursive_mutex::scoped_lock lock(mutex_.mutex_);
		mutex_.acquire(lock, mutex_.max_readers_ - 1);
		permits_ = mutex_.max_readers_;
#ifdef SHOW_LOCK_STATE
		cout << "UpgradeToWriteLocked" << endl;
#endif
	}
}

void UpgradableLock::downgradeToReadLock()
{
	if (mutex_.max_readers_ == permits_)
	{
		boost::recursive_mutex::scoped_lock lock(mutex_.mutex_);
		mutex_.release(lock, permits_ - 1);
		permits_ = 1;

#ifdef SHOW_LOCK_STATE
		cout << "DowngradeToReadLocked" << endl;
#endif
	}
}

UpgradableReadLock::UpgradableReadLock(ReadWriteMutex& mutex)
: UpgradableLock(mutex, 1)
{
#ifdef SHOW_LOCK_STATE
	cout << "UpgradableReadLocked" << endl;
#endif
}

UpgradableReadLock::~UpgradableReadLock()
{
#ifdef SHOW_LOCK_STATE
	cout << "UpgradableReadUnlocked" << endl;
#endif
}

ScopedWriteLock::ScopedWriteLock(ReadWriteMutex& mutex)
: UpgradableLock(mutex, mutex.max_readers_)
{
#ifdef SHOW_LOCK_STATE
	cout << "WriteLocked" << endl;
#endif
}

ScopedWriteLock::~ScopedWriteLock()
{
#ifdef SHOW_LOCK_STATE
	cout << "WriteUnlocked" << endl;
#endif
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite

