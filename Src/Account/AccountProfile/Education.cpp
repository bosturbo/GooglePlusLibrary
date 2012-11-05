#include <Account/AccountProfile/Education.hpp>
#include <Thread/ReadWriteMutex.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

Education::Education()
:school_name_(L""),
major_or_study_field_(L""),
start_year_(L""),
end_year_(L""),
is_current_(false),
read_write_mutex_(make_shared<ReadWriteMutex>())
{
}

wstring Education::getSchoolName() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return school_name_;
}

void Education::setSchoolName(const wstring& school_name)
{
	ScopedWriteLock lock(*read_write_mutex_);
	school_name_ = school_name;
}


wstring Education::getMajorOrStudyField() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return major_or_study_field_;
}

void Education::setMajorOrStudyField(const wstring& major_or_study_field)
{
	ScopedWriteLock lock(*read_write_mutex_);
	major_or_study_field_ = major_or_study_field;
}

wstring Education::getStartYear() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return start_year_;
}

void Education::setStartYear(const wstring& start_year)
{
	ScopedWriteLock lock(*read_write_mutex_);
	start_year_ = start_year;
}

wstring Education::getEndYear() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return end_year_;
}

void Education::setEndYear(const wstring& end_year)
{
	ScopedWriteLock lock(*read_write_mutex_);
	end_year_ = end_year;
}

Education::~Education()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite