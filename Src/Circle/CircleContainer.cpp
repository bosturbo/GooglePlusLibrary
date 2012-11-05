#include <Circle/CircleContainer.hpp>
#include <Circle/Circle.hpp>



namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

boost::signals2::signal<void (const Circle&)> CircleContainer::onCircleinserted;
boost::signals2::signal<void (const Circle&)> onCircleEdited;
boost::signals2::signal<void (const wstring&)> CircleContainer::onCircleDeleted;

map<wstring, Circle> CircleContainer::circle_container_;
ReadWriteMutex CircleContainer::read_write_mutex_;

CircleContainer::CircleContainer()
{
}

bool CircleContainer::insert(const Circle& circle)
{
	ScopedWriteLock lock(read_write_mutex_);
	auto result = circle_container_.insert(map<wstring, Circle>::value_type(circle.getCircleID(), circle));
	onCircleinserted(circle);
	return result.second;
}

void CircleContainer::updateItem(const Circle& circle)
{
	ScopedWriteLock lock(read_write_mutex_);
	circle_container_[circle.getCircleID()] = circle;
}

bool CircleContainer::erase(const wstring& circle_id)
{
	ScopedWriteLock lock(read_write_mutex_);
	auto it = circle_container_.find(circle_id);
	if(it == circle_container_.end())
	{
		// not found
		return false;
	}
	// found
	circle_container_.erase(it);
	onCircleDeleted(circle_id);
	return true;
}

int CircleContainer::count()
{
	ScopedReadLock lock(read_write_mutex_);
	return circle_container_.size();
}

const Circle* CircleContainer::getByCircleID(const wstring& circle_id)
{
	ScopedReadLock lock(read_write_mutex_);
	auto it = circle_container_.find(circle_id);
	if(it == circle_container_.end())
	{
		// not found
		return nullptr;
	}
	// found
	return &(it->second);
}

const Circle* CircleContainer::operator[](const wstring& circle_id)
{
	return getByCircleID(circle_id);
}

CircleContainer::~CircleContainer()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite