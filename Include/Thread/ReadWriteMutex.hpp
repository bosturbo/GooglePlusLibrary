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

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

/*!
* @~english
* @brief Class to achieve ReadWriteLock
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief ReadWriteLockを実現するためのクラス
* @warning このクラスはライブラリ開発者ならびにLuaスクリプト編集者以外利用しないようにしてください
*/
class ReadWriteMutex
{
	friend class UpgradableLock;
	friend class ScopedReadLock;
	friend class ScopedWriteLock;

public:
	ReadWriteMutex(unsigned int max_readers = 1000);

private:
	void acquire(boost::recursive_mutex::scoped_lock& lock, unsigned int permits);
	void release(boost::recursive_mutex::scoped_lock& lock, unsigned int permits);

	unsigned int const max_readers_;
	unsigned int available_;
	bool writing_;
	boost::recursive_mutex mutex_;
	boost::condition condition_;
};

/*!
* @~english
* @brief Class to start automatically ReadLock, to terminate automatically
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief ReadLockを自動でスタートし、自動で終了させるためのクラス
* @warning このクラスはライブラリ開発者ならびにLuaスクリプト編集者以外利用しないようにしてください
*/
class ScopedReadLock
{
public:
	ScopedReadLock(ReadWriteMutex& mutex);
	virtual ~ScopedReadLock();

private:
	ReadWriteMutex& mutex_;
};

class UpgradableLock
{
public:
	void upgradeToWriteLock();
	void downgradeToReadLock();

protected:
	UpgradableLock(ReadWriteMutex& mutex, unsigned int permits);
	virtual ~UpgradableLock();

private:
	ReadWriteMutex& mutex_;
	unsigned int permits_;
};

class UpgradableReadLock : public UpgradableLock
{
public:
	UpgradableReadLock(ReadWriteMutex& mutex);
	virtual ~UpgradableReadLock();
};

/*!
* @~english
* @brief Class to start automatically WriteLock, to terminate automatically
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief WriteLockを自動でスタートし、自動で終了させるためのクラス
* @warning このクラスはライブラリ開発者ならびにLuaスクリプト編集者以外利用しないようにしてください
*/
class ScopedWriteLock : public UpgradableLock
{
public:
	ScopedWriteLock(ReadWriteMutex& mutex);
	virtual ~ScopedWriteLock();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite


