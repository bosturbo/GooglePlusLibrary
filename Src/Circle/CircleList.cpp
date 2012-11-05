#include <Circle/CircleList.hpp>
#include <Circle/Circle.hpp>
#include <Circle/CircleContainer.hpp>

#include <Connection/Connection.hpp>
#include <Connection/Cookie/Cookie.hpp>
#include <Connection/HttpResponse.hpp>
#include <Utility/Utility.hpp>
#include <Information/InformationContainer.hpp>

#include <Utility/LuaScript.hpp>
#include <Json/JsonObject.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

CircleList::CircleList()
:my_account_id_(L"")
{
}

void CircleList::update()
{
	updateAsync();
	waitupdateAsync();
}

void CircleList::updateAsync()
{
	boost::thread update_thread(boost::bind(&CircleList::updateAsyncThreadMethod, this));
	update_thread_ = boost::move(update_thread);
}

void CircleList::waitupdateAsync()
{
	update_thread_.join();
}

void CircleList::updateAsyncThreadMethod()
{
	LuaScript<bool(string)> lua_script("LuaScript/UpdateCircleList.lua", "UpdateCircleList", [](lua_State* lua_state)
	{
		Connection::bindToScript(lua_state);
		HttpResponse::bindToScript(lua_state);
		Utility::bindToScript(lua_state);
		InformationContainer::bindToScript(lua_state);
		JsonObject::bindToScript(lua_state);
	});

	auto result = lua_script(Utility::convertUnicodeToUTF8(getMyAccountID()));
	if(result == false)
	{
		// update added account list failed
		return;
	}

	onUpdateCompleted();
}

wstring CircleList::getMyAccountID() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return my_account_id_;
}

void CircleList::setMyAccountID(const wstring& my_account_id)
{
	ScopedWriteLock lock(*read_write_mutex_);
	my_account_id_ = my_account_id;
}

bool CircleList::add(const wstring& circle_id)
{
	if(circle_id.empty())
	{
		return false;
	}
	auto result = circle_id_list_.push_back(circle_id);
	return result.second;
}

bool CircleList::add(const Circle& circle)
{
	if(!add(circle.getCircleID()))
	{
		return false;
	}
	onCircleAdded(circle);
	return true;
}

void CircleList::updateItem(const Circle& circle)
{
	onCircleEdited(circle);
}

bool CircleList::remove(const wstring& circle_id)
{
	typedef CircleIDList::index<search_by_circle_id>::type CircleIndex;

	CircleIndex& circle_index = circle_id_list_.get<search_by_circle_id>();
	auto circle_id_it = circle_index.find(circle_id);
	if(circle_id_it == circle_index.end())
	{
		// not found
		return false;
	}
	circle_index.erase(circle_id_it, circle_index.end());
	onCircleDeleted(circle_id);
	return true;
}

const Circle* CircleList::getByCircleID(const wstring& circle_id) const
{
	typedef CircleIDList::index<search_by_circle_id>::type CircleIndex;

	const CircleIndex& circle_index = circle_id_list_.get<search_by_circle_id>();
	auto circle_id_it = circle_index.find(circle_id);
	if(circle_id_it == circle_index.end())
	{
		// not found
		return nullptr;
	}
	return CircleContainer::getByCircleID(circle_id);
}

const Circle* CircleList::getByIndex(int index) const
{
	typedef CircleIDList::index<search_sequence>::type CircleSequencedIndex;
	const CircleSequencedIndex& circle_index = circle_id_list_.get<search_sequence>();

	auto circle_it = circle_index.begin();

	int count = 0;
	while(circle_it != circle_index.end())
	{
		if(count == index)
		{
			return getByCircleID(*circle_it);
		}
		++count;
	}
	return nullptr;
}

const Circle* CircleList::operator[](const wstring& circle_id) const
{
	return getByCircleID(circle_id);
}

const Circle* CircleList::operator[](int index) const
{
	return getByIndex(index);
}

int CircleList::count() const
{
	typedef CircleIDList::index<search_by_circle_id>::type CircleIndex;
	const CircleIndex& circle_index = circle_id_list_.get<search_by_circle_id>();
	return circle_index.size();
}

CircleList::~CircleList()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite