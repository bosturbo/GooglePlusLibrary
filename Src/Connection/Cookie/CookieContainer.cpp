#include <Connection/Cookie/CookieContainer.hpp>
#include <Connection/Cookie/Cookie.hpp>

#include <boost/scope_exit.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

list<CookieContainer::CookieInformation> CookieContainer::cookie_container_;
ReadWriteMutex CookieContainer::read_write_mutex_;

CookieContainer::CookieContainer()
{
}

void CookieContainer::setConnectID(const string& target_mail_address, const string& account_id)
{
#ifdef SHOW_UPGRADABLE_READLOCKED_FUNCTION
	cout << "CookieContainer::setConnectID" << endl;
#endif
	
	UpgradableReadLock lock(read_write_mutex_);
	
	auto it = cookie_container_.begin();
	while(it != cookie_container_.end())
	{
		if((*it).mail_address == target_mail_address)
		{
			lock.upgradeToWriteLock();
			(*it).account_id = account_id;
			lock.downgradeToReadLock();
			return;
		}
		++it;
	}
}

void updateCookieList(list<Cookie>& cookie_list, const Cookie& cookie)
{
	bool found = false;

	Cookie target_cookie = cookie;
		
	auto it = (*&cookie_list).begin();
	while(it != (*&cookie_list).end())
	{
		if((*it).isEqual(target_cookie) == true)
		{
			// same cookie
			found = true;
			break;
		}
		
		if((*it).isExpired() == true)
		{
			// deleting
			it = (*&cookie_list).erase(it);
			continue;
		}

		if(((*it).getName() == target_cookie.getName())
			&& ((*it).getDomain() == target_cookie.getDomain())
			&& ((*it).getPath() == target_cookie.getPath()))
		{
			// Updating
			found = true;

			if((*it).getExpireTime() > target_cookie.getExpireTime())
			{
				(*it) = target_cookie;
			}

			if((*it).getExpireTime() == target_cookie.getExpireTime())
			{
				if((*it).getValue() == target_cookie.getValue())
				{
					continue;
				}
				(*it) = target_cookie;
			}
		}
		++it;
	}

	if(found == false)
	{
		// Adding
		(*&cookie_list).push_back(target_cookie);
	}
	
}

void CookieContainer::addCookieByAccountID(const Cookie& cookie, const string& account_id)
{
#ifdef SHOW_UPGRADABLE_READLOCKED_FUNCTION
	cout << "CookieContainer::addCookieByAccountID" << endl;
#endif
	UpgradableReadLock lock(read_write_mutex_);
	
	auto it = cookie_container_.begin();
	while(it != cookie_container_.end())
	{
		if((*it).account_id == account_id)
		{
			lock.upgradeToWriteLock();
			updateCookieList((*it).cookies, cookie);
			lock.downgradeToReadLock();
		}
		++it;
	}
	
	// not found
	CookieInformation cookie_information;
	cookie_information.account_id = account_id;
	cookie_information.cookies.push_back(cookie);
	lock.upgradeToWriteLock();
	cookie_container_.push_back(cookie_information);	
}

void CookieContainer::addCookiesByAccountID(const list<Cookie>& cookie_list, const string& account_id)
{
	auto it = cookie_list.cbegin();
	while(it != cookie_list.cend())
	{
		addCookieByAccountID(*it, account_id);
		++it;
	}
}

void CookieContainer::addCookieByMailAddress(const Cookie& cookie, const string& mail_address)
{
#ifdef SHOW_UPGRADABLE_READLOCKED_FUNCTION
	cout << "CookieContainer::addCookieByMailAddress" << endl;
#endif
	UpgradableReadLock lock(read_write_mutex_);
	
	auto it = cookie_container_.begin();
	while(it != cookie_container_.end())
	{
		if((*it).mail_address == mail_address)
		{
			lock.upgradeToWriteLock();
			updateCookieList((*it).cookies, cookie);
			lock.downgradeToReadLock();
		}
		++it;
	}

	// not found
	CookieInformation cookie_information;
	cookie_information.mail_address = mail_address;
	cookie_information.cookies.push_back(cookie);
	lock.upgradeToWriteLock();
	cookie_container_.push_back(cookie_information);
}

void CookieContainer::addCookiesByMailAddress(const list<Cookie>& cookie_list, const string& mail_address)
{
	auto it = cookie_list.cbegin();
	while(it != cookie_list.cend())
	{
		addCookieByMailAddress(*it, mail_address);
		++it;
	}
}

void CookieContainer::showCookiesByAccountID(const string& account_id)
{
	ScopedReadLock lock(read_write_mutex_);

	auto it = cookie_container_.begin();
	while(it != cookie_container_.end())
	{
		if((*it).account_id == account_id)
		{
			auto cookie_it = (*it).cookies.begin();
			while(cookie_it != (*it).cookies.end())
			{
				cout << "cookie:" << (*cookie_it).getName() << "=" << (*cookie_it).getValue() << endl;
				cout << "" << endl;
				++cookie_it;
			}
			return;
		}
		++it;
	}
}

void CookieContainer::showCookiesByMailAddress(const string& mail_address)
{
	ScopedReadLock lock(read_write_mutex_);

	auto it = cookie_container_.begin();
	while(it != cookie_container_.end())
	{
		if((*it).mail_address == mail_address)
		{
			auto cookie_it = (*it).cookies.begin();
			while(cookie_it != (*it).cookies.end())
			{
				cout << "cookie:" << (*cookie_it).getName() << "=" << (*cookie_it).getValue() << endl;
				cout << "" << endl;
				++cookie_it;
			}
			return;
		}
		++it;
	}
}

list<Cookie> CookieContainer::getCookieByAccountID(const string& account_id)
{
#ifdef SHOW_UPGRADABLE_READLOCKED_FUNCTION
	cout << "CookieContainer::getCookieByAccountID" << endl;
#endif
	UpgradableReadLock lock(read_write_mutex_);
	
	auto it = cookie_container_.begin();
	while(it != cookie_container_.end())
	{
		if((*it).account_id == account_id)
		{
			return (*it).cookies;
		}
		++it;
	}
	
	// not found
	CookieInformation cookie_information;
	cookie_information.account_id = account_id;
	lock.upgradeToWriteLock();
	cookie_container_.push_back(cookie_information);
	return cookie_information.cookies;
}

list<Cookie> CookieContainer::getCookieByMailAddress(const string& mail_address)
{
#ifdef SHOW_UPGRADABLE_READLOCKED_FUNCTION
	cout << "CookieContainer::getCookieByMailAddress" << endl;
#endif
	UpgradableReadLock lock(read_write_mutex_);
	
	auto it = cookie_container_.begin();
	while(it != cookie_container_.end())
	{
		if((*it).mail_address == mail_address)
		{
			return (*it).cookies;
		}
		++it;
	}

	// not found
	CookieInformation cookie_information;
	cookie_information.mail_address = mail_address;

	lock.upgradeToWriteLock();
	cookie_container_.push_back(cookie_information);
	return cookie_information.cookies;
}

void CookieContainer::clearCookieByAccountID(const string& account_id)
{
#ifdef SHOW_UPGRADABLE_READLOCKED_FUNCTION
	cout << "CookieContainer::clearCookieByAccountID" << endl;
#endif
	UpgradableReadLock lock(read_write_mutex_);
	
	auto it = cookie_container_.begin();
	while(it != cookie_container_.end())
	{
		if((*it).account_id == account_id)
		{
			lock.upgradeToWriteLock();
			(*it).cookies.clear();
			return;
		}
		++it;
	}
}

void CookieContainer::clearCookieByMailAddress(const string& mail_address)
{
#ifdef SHOW_UPGRADABLE_READLOCKED_FUNCTION
	cout << "CookieContainer::clearCookieByMailAddress" << endl;
#endif
	UpgradableReadLock lock(read_write_mutex_);
	
	auto it = cookie_container_.begin();
	while(it != cookie_container_.end())
	{
		if((*it).mail_address == mail_address)
		{
			lock.upgradeToWriteLock();
			(*it).cookies.clear();
			return;
		}
		++it;
	}
}

void CookieContainer::clearAllCookie()
{
	ScopedWriteLock lock(read_write_mutex_);
	cookie_container_.clear();
}

CookieContainer::~CookieContainer()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
