#include <Json/JsonPathParser.hpp>

#include <Json/JsonObject.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

namespace
{
	namespace qi = boost::spirit::qi;
	namespace spc = boost::spirit::standard_wide;
	namespace phoenix = boost::phoenix;
}

using namespace std;

JsonPathParser::JsonPathParser()
{
}

JsonObject JsonPathParser::parse(const JsonObject& object, const wstring& path) const
{
	if(path.empty())
	{
		return object;
	}

	vector<wstring> paths;

	qi::rule<wstring::const_iterator, wstring(), spc::space_type> wstring_rule = qi::as_wstring[qi::lexeme[+(~qi::standard_wide::char_(L"]"))]];

	qi::rule<wstring::const_iterator, wstring(), spc::space_type> path_value_rule = (qi::lit(L"[") > wstring_rule[phoenix::push_back(phoenix::ref(paths), qi::_1)]  > qi::lit(L"]"));

	qi::rule<wstring::const_iterator, wstring(), spc::space_type> expression = path_value_rule >> *(-qi::lit(L".") >> path_value_rule);

	try
	{
		if(!boost::spirit::qi::phrase_parse(path.begin(), path.end(), expression, boost::spirit::standard_wide::space))
		{
#ifdef TRACE
			cout << "PathParser:ParseFailed" << endl; 
#endif
			return JsonObject();
		}
	}
	catch (...)
	{
#ifdef TRACE
		cout << "PathParser:ParseFailed" << endl; 
#endif
		return JsonObject();
	}
	
	JsonObject result_object = object;

	auto it = paths.cbegin();
	while(it != paths.cend())
	{
		int node_position = -1;

		boost::spirit::qi::phrase_parse(it->begin(), it->end(), qi::int_[phoenix::ref(node_position) = qi::_1], boost::spirit::standard_wide::space);

		if(node_position >= 0)
		{
			// path == position
			result_object = result_object[node_position];
		}
		else
		{
			result_object = result_object[*it];
		}
		++it;
	}

	return result_object;
}

JsonPathParser::~JsonPathParser()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite