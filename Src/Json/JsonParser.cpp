#include <Json/JsonParser.hpp>
#include <Json/JsonGrammar.hpp>
#include <wchar.h>
#include <sstream>

#include <boost/algorithm/string/replace.hpp>

#define LOGGING

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

JsonParser::JsonParser()
{
}

JsonObject JsonParser::parse(const wstring& json) const
{
	wstring target_json = json;
	if(target_json == L"null")
	{
		return JsonObject();
	}

	boost::algorithm::replace_all(target_json, L"'u", L"\\u");
	boost::algorithm::replace_all(target_json, L"'\"", L"\\\"");
	
	JsonGrammar<wstring::const_iterator> json_grammer;

	JsonObject object;

	static int count = 1;

	try
	{
		bool result = boost::spirit::qi::phrase_parse(target_json.cbegin(), target_json.cend(), json_grammer, boost::spirit::standard_wide::space, object);
		if(!result)
		{
#ifdef TRACE
			cout << "JsonParser:ParseFailed" << endl; 
#endif
			
#ifdef LOGGING
			wstringstream string_stream;
			string_stream << "FailedJson";
			string_stream << count;
			string_stream << ".txt";
			FILE* json_file;
			json_file = _wfopen(string_stream.str().c_str(), L"w, ccs=UTF-16LE");
			fwprintf(json_file, json.c_str());
			fclose(json_file);
#endif
		}
	}
	catch (...)
	{
#ifdef TRACE
		cout << "JsonParser:ParseFailed" << endl; 
#endif

#ifdef LOGGING
		wstringstream string_stream;
		string_stream << "Failed(Exception)Json";
		string_stream << count;
		string_stream << ".txt";

		FILE* json_file;
		json_file = _wfopen(string_stream.str().c_str(), L"w, ccs=UTF-16LE");
		fwprintf(json_file, json.c_str());
		fclose(json_file);
#endif
	}

	++count;

	return object;
}

JsonParser::~JsonParser()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite