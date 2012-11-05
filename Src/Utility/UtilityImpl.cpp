#include <Utility/UtilityImpl.hpp>

#include <Json/JsonObject.hpp>
#include <Json/JsonParser.hpp>

#include <boost/regex.hpp>
#include <boost/random.hpp>

#include <utf8.h>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

UtilityImpl::UtilityImpl()
{
}

wstring UtilityImpl::convertUTF8ToUnicode(string source)
{
	wstring result(L"");
	
	string::iterator end_it = utf8::find_invalid(source.begin(), source.end());

	if (end_it != source.end())
	{
		cout << "Invalid UTF-8 encoding detected\n";
		//cout << "This part is fine: " << string(source.begin(), end_it) << "\n";
	}

	vector<unsigned short> utf16line;
	utf8::utf8to16(source.begin(), end_it, back_inserter(utf16line));

	auto it = utf16line.begin();
	while(it != utf16line.end())
	{
		result += wchar_t(*it);
		++it;
	}

	if(!result.empty())
	{
		// Remove Bom
		if(result[0] == (wchar_t)65279)
		{
			result = result.substr(1);
		}
	}

	return result;
}

string UtilityImpl::convertUnicodeToUTF8(wstring source)
{
	string utf8line;
	utf8::utf16to8(source.begin(), source.end(), back_inserter(utf8line));
	return utf8line;
}

string UtilityImpl::getRandomValue(int min_value, int max_value, string error_value)
{
	boost::mt19937 generator(static_cast<unsigned long>(time(0)));
	boost::uniform_smallint<> distribution(min_value, max_value);
	boost::variate_generator<boost::mt19937&, boost::uniform_smallint<> > rand(generator, distribution);

	try
	{
		return boost::lexical_cast<string>(rand());
	}
	catch (boost::bad_lexical_cast&)
	{   
		return error_value;
	}
}

string UtilityImpl::getRandomRequestID()
{
	return getRandomValue(100000, 9999999, "100000");
}
/*
string UtilityImpl::getJSONNodeValue(JsonObject node, const string& node_path)
{
	JsonObject object = node.selectChildNode(UtilityImpl::convertUTF8ToUnicode(node_path));
	if(object.isNull())
	{
		return "";
	}
	return UtilityImpl::convertUnicodeToUTF8(object.asWString());
}
*/
JsonObject UtilityImpl::convertStringEscapedJson(JsonObject node, const string& node_path)
{
	JsonParser parser;
	return parser.parse(node.selectChildNode(UtilityImpl::convertUTF8ToUnicode(node_path)).asWString());
}

string UtilityImpl::generateRandomString(int min_length, int max_length, string key_characters)
{
	if(min_length <= 0)
	{
		min_length = 1;
	}
	if(max_length <= 1)
	{
		max_length = 2;
	}

	int generate_string_length = 1;

	// Determination of the number of loops
	if(min_length == max_length)
	{
		generate_string_length = max_length;
	}
	else
	{
		static boost::mt19937 generator(static_cast<unsigned long>(time(0)));
		boost::uniform_smallint<> distribution(min_length, max_length);
		boost::variate_generator<boost::mt19937&, boost::uniform_smallint<> > rand(generator, distribution);
		generate_string_length = rand();
	}

	string generated_string("");

	int loop_count = 0;
	while(loop_count < generate_string_length)
	{
		static boost::mt19937 generator(static_cast<unsigned long>(time(0)));
		boost::uniform_smallint<> distribution(0, (key_characters.length() - 1));
		boost::variate_generator<boost::mt19937&, boost::uniform_smallint<> > rand(generator, distribution);

		int position = rand();
		try
		{
			generated_string += boost::lexical_cast<string>(key_characters[position]);
		}
		catch (boost::bad_lexical_cast&)
		{
			continue;
		}
		++loop_count;
	}

	return generated_string;
}

long UtilityImpl::getUnixTime()
{
	return static_cast<long>(time(0));
}

boost::posix_time::ptime UtilityImpl::convertUnixTimeFromString(const string& unix_time_milliseconds)
{
	boost::regex  regex("[0-9]+");
	boost::smatch match;

	boost::gregorian::date epoc(1970, 1, 1);

	if(!boost::regex_search(unix_time_milliseconds, match, regex))
	{
		// not time
		return boost::posix_time::ptime(epoc);
	}

	long long int time = 0;
	try
	{
		time = boost::lexical_cast<long long int>(unix_time_milliseconds);
	}
	catch (boost::bad_lexical_cast)
	{
		return boost::posix_time::ptime(epoc);
	}

	boost::posix_time::milliseconds milliseconds_time(time);
	return boost::posix_time::ptime(epoc, milliseconds_time);
}

boost::posix_time::ptime UtilityImpl::convertUnixTimeFromString(const wstring& unix_time_milliseconds)
{
	boost::wregex  regex(L"[0-9]+");
	boost::wsmatch match;

	boost::gregorian::date epoc(1970, 1, 1);

	if(!boost::regex_search(unix_time_milliseconds, match, regex))
	{
		// not time
		return boost::posix_time::ptime(epoc);
	}

	long long int time = 0;
	try
	{
		time = boost::lexical_cast<long long int>(unix_time_milliseconds);
	}
	catch (boost::bad_lexical_cast)
	{
		return boost::posix_time::ptime(epoc);
	}

	boost::posix_time::milliseconds milliseconds_time(time);
	return boost::posix_time::ptime(epoc, milliseconds_time);
}

UtilityImpl::~UtilityImpl()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite