#include <AttachedInfo/AttachedSearchResult/AttachedSearchResult.hpp>
#include <Utility/Utility.hpp>
#include <Utility/LuaScript.hpp>

#include <Json/JsonObject.hpp>
#include <Thread/ReadWriteMutex.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

AttachedSearchResult::AttachedSearchResult()
:read_write_mutex_(make_shared<ReadWriteMutex>())
{
}

wstring AttachedSearchResult::getSearchKeyword() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return search_keyword_;
}

wstring AttachedSearchResult::getSearchResultPageUrl() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return search_result_page_url_;
}

AttachedSearchResult::~AttachedSearchResult()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite