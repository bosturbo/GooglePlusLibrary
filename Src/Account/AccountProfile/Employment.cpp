#include <Account/AccountProfile/Employment.hpp>
#include <Thread/ReadWriteMutex.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

Employment::Employment()
:company_name_(L""),
job_title_(L""),
start_year_(L""),
end_year_(L""),
is_current_(false),
read_write_mutex_(make_shared<ReadWriteMutex>())
{
}

wstring Employment::getCompanyName() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return company_name_;
}

void Employment::setCompanyName(const wstring& company_name)
{
	ScopedWriteLock lock(*read_write_mutex_);
	company_name_ = company_name;
}


wstring Employment::getJobTitle() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return job_title_;
}

void Employment::setJobTitle(const wstring& job_title)
{
	ScopedWriteLock lock(*read_write_mutex_);
	job_title_ = job_title;
}

wstring Employment::getStartYear() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return start_year_;
}

void Employment::setStartYear(const wstring& start_year)
{
	ScopedWriteLock lock(*read_write_mutex_);
	start_year_ = start_year;
}

wstring Employment::getEndYear() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return end_year_;
}

void Employment::setEndYear(const wstring& end_year)
{
	ScopedWriteLock lock(*read_write_mutex_);
	end_year_ = end_year;
}

Employment::~Employment()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite