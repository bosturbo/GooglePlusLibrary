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

#include <boost/thread/recursive_mutex.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class ReadWriteMutexImpl;
class ScopedReadLockImpl;
class UpgradableLockImpl;
class UpgradableReadLockImpl;
class ScopedWriteLockImpl;

/*!
* @~english
* @brief Class to achieve ReadWriteLock
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief ReadWriteLock���������邽�߂̃N���X
* @warning ���̃N���X�̓��C�u�����J���҂Ȃ�т�Lua�X�N���v�g�ҏW�҈ȊO���p���Ȃ��悤�ɂ��Ă�������
*/
class ReadWriteMutex
{
	friend class UpgradableLock;
	friend class UpgradableLockImpl;
	friend class UpgradableReadLock;
	friend class ScopedReadLock;
	friend class ScopedReadLockImpl;
	friend class ScopedWriteLock;
	friend class ScopedWriteLockImpl;

public:
	ReadWriteMutex(unsigned int max_readers = 1000);

private:
	void acquire(boost::recursive_mutex::scoped_lock& lock, unsigned int permits);
	void release(boost::recursive_mutex::scoped_lock& lock, unsigned int permits);

	std::shared_ptr<ReadWriteMutexImpl> impl_;
};

/*!
* @~english
* @brief Class to start automatically ReadLock, to terminate automatically
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief ReadLock�������ŃX�^�[�g���A�����ŏI�������邽�߂̃N���X
* @warning ���̃N���X�̓��C�u�����J���҂Ȃ�т�Lua�X�N���v�g�ҏW�҈ȊO���p���Ȃ��悤�ɂ��Ă�������
*/
class ScopedReadLock
{
public:
	ScopedReadLock(ReadWriteMutex& mutex);
	virtual ~ScopedReadLock();
private:
	std::shared_ptr<ScopedReadLockImpl> impl_;
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
	std::shared_ptr<UpgradableLockImpl> impl_;
};

class UpgradableReadLock
{
public:
	UpgradableReadLock(ReadWriteMutex& mutex);

	void upgradeToWriteLock();
	void downgradeToReadLock();

	virtual ~UpgradableReadLock();
private:
	std::shared_ptr<UpgradableReadLockImpl> impl_;
};

/*!
* @~english
* @brief Class to start automatically WriteLock, to terminate automatically
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief WriteLock�������ŃX�^�[�g���A�����ŏI�������邽�߂̃N���X
* @warning ���̃N���X�̓��C�u�����J���҂Ȃ�т�Lua�X�N���v�g�ҏW�҈ȊO���p���Ȃ��悤�ɂ��Ă�������
*/
class ScopedWriteLock
{
public:
	ScopedWriteLock(ReadWriteMutex& mutex);
	virtual ~ScopedWriteLock();
private:
	std::shared_ptr<ScopedWriteLockImpl> impl_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite


