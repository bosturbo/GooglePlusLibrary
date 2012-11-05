#include <Utility/Utility.hpp>
#include <Utility/UtilityImpl.hpp>

#include <Json/JsonObject.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

Utility::Utility()
{
}

wstring Utility::convertUTF8ToUnicode(string source)
{
	return UtilityImpl::convertUTF8ToUnicode(source);
}

string Utility::convertUnicodeToUTF8(wstring source)
{
	return UtilityImpl::convertUnicodeToUTF8(source);
}

string Utility::getRandomValue(int min_value, int max_value, string error_value)
{
	return UtilityImpl::getRandomValue(min_value, max_value, error_value);
}

string Utility::getRandomRequestID()
{
	return getRandomValue(100000, 9999999, "100000");
}

JsonObject Utility::convertStringEscapedJson(JsonObject node, const string& node_path)
{
	return UtilityImpl::convertStringEscapedJson(node, node_path);
}

string Utility::generateRandomString(int min_length, int max_length, string key_characters)
{
	return UtilityImpl::generateRandomString(min_length, max_length, key_characters);
}

long Utility::getUnixTime()
{
	return UtilityImpl::getUnixTime();
}

boost::posix_time::ptime Utility::convertUnixTimeFromString(const string& unix_time_milliseconds)
{
	return UtilityImpl::convertUnixTimeFromString(unix_time_milliseconds);
}

boost::posix_time::ptime Utility::convertUnixTimeFromString(const wstring& unix_time_milliseconds)
{
	return UtilityImpl::convertUnixTimeFromString(unix_time_milliseconds);
}

Utility::~Utility()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite