#include <Circle/Circle.hpp>
#include <Thread/ReadWriteMutex.hpp>

#ifdef GOOGLEPLUSLIBRARY_NO_WARNINGS
#ifdef _MSC_VER
#pragma warning (disable:4819)
#endif
#endif

#include <boost/spirit/include/qi.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
namespace qi = boost::spirit::qi;

Circle::Circle()
:circle_id_(L""),
read_write_mutex_(make_shared<ReadWriteMutex>())
{
}

Circle::Circle(const wstring& circle_name, const wstring& circle_id)
:circle_name_(circle_name),
circle_id_(circle_id),
read_write_mutex_(make_shared<ReadWriteMutex>())
{
}

bool Circle::verifyCircleID(const wstring& circle_id)
{
	qi::rule<wstring::const_iterator, wstring()> id_rule = qi::char_('0','9') | qi::char_('a','z') | qi::char_('A','Z');

	if(qi::parse(circle_id.cbegin(), circle_id.cend(), +id_rule))
	{
		return true;
	}
	else
	{
		return false;
	}
}

wstring Circle::getCircleID() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return circle_id_;
}

void Circle::setCircleID(const wstring& circle_id)
{
	ScopedWriteLock lock(*read_write_mutex_);
	circle_id_ = circle_id;
}

wstring Circle::getCircleName() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return circle_name_;
}

void Circle::setCircleName(const wstring& circle_name)
{
	ScopedWriteLock lock(*read_write_mutex_);
	circle_name_ = circle_name;
}

Circle::~Circle()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite