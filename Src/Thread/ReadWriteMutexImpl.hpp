#pragma once

#ifdef _MSC_VER
#ifdef GOOGLEPLUSLIBRARY_EXPORTS
#define GOOGLEPLUSLIBRARY_API __declspec(dllexport)
#else
#define GOOGLEPLUSLIBRARY_API __declspec(dllimport)
#endif
#else
#define GOOGLEPLUSLIBRARY_API
#endif

#ifdef GOOGLEPLUSLIBRARY_NO_WARNINGS
#ifdef _MSC_VER
#pragma warning (disable:4251)
#endif
#endif

#include <boost/thread/condition.hpp>
#include <boost/thread/recursive_mutex.hpp>

// show lock state on standard output
//#define SHOW_LOCK_STATE

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class ReadWriteMutexImpl
{
public:
	ReadWriteMutexImpl(unsigned int max_readers);

	void acquire(boost::recursive_mutex::scoped_lock& lock, unsigned int permits);
	void release(boost::recursive_mutex::scoped_lock& lock, unsigned int permits);

public:
	unsigned int const max_readers_;
	unsigned int available_;
	bool writing_;
	boost::recursive_mutex mutex_;
	boost::condition condition_;
};

class ScopedReadLockImpl
{
public:
	ScopedReadLockImpl(ReadWriteMutexImpl& mutex);
	virtual ~ScopedReadLockImpl();

private:
	ReadWriteMutexImpl& mutex_;
};

class UpgradableLockImpl
{
public:
	UpgradableLockImpl(ReadWriteMutexImpl& mutex, unsigned int permits);
	void upgradeToWriteLock();
	void downgradeToReadLock();

	virtual ~UpgradableLockImpl();

	ReadWriteMutexImpl& mutex_;
	unsigned int permits_;
};

class UpgradableReadLockImpl : public UpgradableLockImpl
{
public:
	UpgradableReadLockImpl(ReadWriteMutexImpl& mutex);
	virtual ~UpgradableReadLockImpl();
};

class ScopedWriteLockImpl : public UpgradableLockImpl
{
public:
	ScopedWriteLockImpl(ReadWriteMutexImpl& mutex);
	virtual ~ScopedWriteLockImpl();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite


