#include <Information/InformationContainer.hpp>

#include <boost/scope_exit.hpp>
#include <boost/lexical_cast.hpp>

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include <iostream>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

list<PrivateInformation> InformationContainer::information_container;
ReadWriteMutex InformationContainer::read_write_mutex_;

InformationContainer::InformationContainer()
{
}

void InformationContainer::setConnectID(const string& target_mail_address, const string& account_id)
{
	ScopedWriteLock lock(read_write_mutex_);
	
	auto it = information_container.begin();
	while(it != information_container.end())
	{
		if((*it).mail_address == target_mail_address)
		{
			(*it).account_id = account_id;
			return;
		}
		++it;
	}
}

void InformationContainer::addInformationByAccountID(const string& name, const string& value, const string& account_id)
{
	ScopedWriteLock lock(read_write_mutex_);
	
	auto it = information_container.begin();
	while(it != information_container.end())
	{
		if((*it).account_id == account_id)
		{
			(*it).informations[name] = value;
			return;
		}
		++it;
	}

	// not found
	PrivateInformation private_information;
	private_information.informations.insert(map<string, string>::value_type(name, value));
	private_information.account_id = account_id;
	information_container.push_back(private_information);
}

void InformationContainer::addInformationByAccountID(const string& name, const int value, const string& account_id)
{
	string value_string("");
	
	try
	{
		value_string = boost::lexical_cast<string>(value);
	}
	catch (boost::bad_lexical_cast& e)
	{
		value_string = "";
		cout << e.what() << endl;
	}
	
	addInformationByAccountID(name, value_string, account_id);
}

void InformationContainer::addInformationByMailAddress(const string& name, const string& value, const string& mail_address)
{
	ScopedWriteLock lock(read_write_mutex_);
	
	auto it = information_container.begin();
	while(it != information_container.end())
	{
		if((*it).mail_address == mail_address)
		{
			//(*it).informations.insert(map<string, string>::value_type(name, value));
			(*it).informations[name] = value;
			return;
		}
		++it;
	}

	// not found
	PrivateInformation private_information;
	private_information.informations.insert(map<string, string>::value_type(name, value));
	private_information.mail_address = mail_address;
	information_container.push_back(private_information);
}

void InformationContainer::addInformationByMailAddress(const string& name, const int value, const string& mail_address)
{
	string value_string("");

	try
	{
		value_string = boost::lexical_cast<string>(value);
	}
	catch (boost::bad_lexical_cast& e)
	{
		value_string = "";
		cout << e.what() << endl;
	}

	addInformationByMailAddress(name, value_string, mail_address);
}

string InformationContainer::getInformationByAccountID(const string& name, const string& account_id)
{
	ScopedReadLock lock(read_write_mutex_);

	auto it = information_container.begin();
	while(it != information_container.end())
	{
		if((*it).account_id == account_id)
		{
			auto map_it = (*it).informations.begin();
			while(map_it != (*it).informations.end())
			{
				if((*map_it).first == name)
				{
					return (*map_it).second;
				}
				++map_it;
			}
		}
		++it;
	}
	return "";
}

string InformationContainer::getInformationByMailAddress(const string& name, const string& mail_address)
{
	ScopedReadLock lock(read_write_mutex_);

	auto it = information_container.begin();
	while(it != information_container.end())
	{
		if((*it).mail_address == mail_address)
		{
			auto map_it = (*it).informations.begin();
			while(map_it != (*it).informations.end())
			{
				if((*map_it).first == name)
				{
					return (*map_it).second;
				}
				++map_it;
			}
		}
		++it;
	}
	return "";
}

void InformationContainer::clearInformationByAccountID(const string& account_id)
{
	ScopedWriteLock lock(read_write_mutex_);
	
	auto it = information_container.begin();
	while(it != information_container.end())
	{
		if((*it).account_id == account_id)
		{
			(*it).informations.clear();
			return;
		}
		++it;
	}
}

void InformationContainer::clearInformationByMailAddress(const string& mail_address)
{
	ScopedWriteLock lock(read_write_mutex_);
	
	auto it = information_container.begin();
	while(it != information_container.end())
	{
		if((*it).mail_address == mail_address)
		{
			(*it).informations.clear();
			return;
		}
		++it;
	}
}

void InformationContainer::clearAllInformation()
{
	ScopedWriteLock lock(read_write_mutex_);
	information_container.clear();
}

void InformationContainer::bindToScript(lua_State* lua_state)
{
	module(lua_state)
		[
			class_<InformationContainer>("InformationContainer")
			.def(constructor<>())
			.scope
			[
				def("setConnectID", &InformationContainer::setConnectID)
			]
			.scope
				[
					def("addInformationByAccountID", static_cast<void(*)(const string&, const string&, const string&)>(&InformationContainer::addInformationByAccountID))
				]
			.scope
				[
					def("addInformationByAccountID", static_cast<void(*)(const string&, const int, const string&)>(&InformationContainer::addInformationByAccountID))
				]
			.scope
				[
					def("addInformationByMailAddress", static_cast<void(*)(const string&, const string&, const string&)>(&InformationContainer::addInformationByMailAddress))
				]
			.scope
				[
					def("addInformationByMailAddress", static_cast<void(*)(const string&, const int, const string&)>(&InformationContainer::addInformationByMailAddress))
				]
			.scope
				[
					def("getInformationByAccountID", &InformationContainer::getInformationByAccountID)
				]
			.scope
				[
					def("getInformationByMailAddress", &InformationContainer::getInformationByMailAddress)
				]
		];
}

InformationContainer::~InformationContainer()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
