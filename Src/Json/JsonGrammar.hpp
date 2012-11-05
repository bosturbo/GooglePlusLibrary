#pragma once

#include <Json/JsonObject.hpp>
#include <Json/JsonMember.hpp>

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

#define ON_QI_ERROR(tag) \
	qi::on_error<qi::fail>(tag, \
	std::cout << phoenix::val("Error Expecting ") \
	<< qi::labels::_4 \
	<< phoenix::val(" here: \"") \
	<< phoenix::construct<std::string>(qi::labels::_3, qi::labels::_2) \
	<< phoenix::val("\"") \
	<< std::endl \
	)
}

template <typename Iterator>
struct JsonGrammar : qi::grammar<Iterator, JsonObject(), spc::space_type>
{
public:

	JsonGrammar() : JsonGrammar::base_type(expression,"expression")
	{
		wstring_rule = (
			 +(qi::alnum) > qi::eps
			| (qi::lit(L"\"") > qi::lexeme[*(javascript_escape_wchar_t_rule | (qi::standard_wide::char_ - qi::standard_wide::char_(L"\"")))] > qi::lit(L"\"")) 
			| (qi::lit(L"\'") > qi::lexeme[*(javascript_escape_wchar_t_rule | (qi::standard_wide::char_ - qi::standard_wide::char_(L"\'")))] > qi::lit(L"\'"))
		);
		
		json_wstring_rule = wstring_rule[qi::_val = phoenix::construct<JsonObject>(qi::_1)];

		int_rule = qi::int_[qi::_val = phoenix::construct<JsonObject>(qi::_1)];

		real_rule = qi::double_[qi::_val = phoenix::construct<JsonObject>(qi::_1)];

		bool_rule = bool_wchar_t_rule[qi::_val = phoenix::construct<JsonObject>(qi::_1)];

		null_rule = (qi::lit(L"null") | qi::eps);

		element_rule = (real_rule | int_rule | bool_rule | json_wstring_rule | array_rule | object_rule | null_rule);

		array_inner_rule = element_rule[phoenix::push_back(qi::_val, qi::_1)] > *(qi::lit(L",") > element_rule[phoenix::push_back(qi::_val, qi::_1)]);

		member_rule = (wstring_rule > qi::lit(L":") > element_rule)[qi::_val = phoenix::construct<JsonMember>(qi::_1,qi::_2)];

		object_inner_rule = member_rule[phoenix::push_back(qi::_val, qi::_1)] > *(qi::lit(L",") > member_rule[phoenix::push_back(qi::_val, qi::_1)]);

		object_rule = (qi::lit(L"{") > object_inner_rule > qi::lit(L"}"))[qi::_val = phoenix::construct<JsonObject>(qi::_1)] 
				 | (qi::lit(L"{") > qi::lit(L"}"));	// Same as (-object_rule_inner)

		array_rule = (qi::lit(L"[") > array_inner_rule > qi::lit(L"]"))[qi::_val = phoenix::construct<JsonObject>(qi::_1)] 
					 // Force to create zero length array. (Nor null_rule)
					 | (qi::lit(L"[") > qi::lit(L"]"))[qi::_val = phoenix::construct<JsonObject>(zero_array)];
		
		json_rule = object_rule | array_rule;

		hex_rule = qi::hex;

		expression = qi::omit[hex_rule ^ qi::lit(L")]}'")] || json_rule;

		wstring_rule.name("wstring");
		int_rule.name("int");
		real_rule.name("real");
		bool_rule.name("bool");
		null_rule.name("null");
		element_rule.name("element");
		array_inner_rule.name("array_inner");
		member_rule.name("member");
		object_inner_rule.name("object_inner");
		object_rule.name("object");
		array_rule.name("array");

		ON_QI_ERROR(wstring_rule);
		ON_QI_ERROR(int_rule);
		ON_QI_ERROR(real_rule);
		ON_QI_ERROR(bool_rule);
		ON_QI_ERROR(null_rule);
		ON_QI_ERROR(element_rule);
		ON_QI_ERROR(array_inner_rule);
		ON_QI_ERROR(member_rule);
		ON_QI_ERROR(object_inner_rule);
		ON_QI_ERROR(object_rule);
	}
	
private:
	struct bool_wchar_t_ : qi::symbols<wchar_t const,bool>
	{
		bool_wchar_t_()
		{
			add
				(L"true" , true)
				(L"false", false)
		;
		}
	} bool_wchar_t_rule;
	
	struct javascript_escape_wchar_t_ : qi::symbols<wchar_t const,wchar_t>
	{
		javascript_escape_wchar_t_()
		{
			add
				(L"\\b", '\b')
				(L"\\t", '\t')
				(L"\\v", '\v')
				(L"\\n", '\n')
				(L"\\r", '\r')
				(L"\\f", '\f')
				(L"\\\'", '\'')
				(L"\\\"", '\"')
				(L"\\\\", '\'')
				(L"\\0", '\0')
			;
		}
	} javascript_escape_wchar_t_rule;

	qi::rule<Iterator, std::wstring(), spc::space_type> wstring_rule;
	qi::rule<Iterator, std::wstring(), spc::space_type> hex_rule;
	qi::rule<Iterator, JsonObject(), spc::space_type> json_wstring_rule;
	qi::rule<Iterator, JsonObject(), spc::space_type> int_rule;
	qi::rule<Iterator, JsonObject(), spc::space_type> real_rule;
	qi::rule<Iterator, std::vector<JsonObject>(), spc::space_type>	array_inner_rule;
	qi::rule<Iterator, JsonObject(), spc::space_type> array_rule;
	qi::rule<Iterator, JsonObject(), spc::space_type> element_rule;
	qi::rule<Iterator, JsonMember(), spc::space_type> member_rule;
	qi::rule<Iterator, std::vector<JsonMember>(), spc::space_type> object_inner_rule;
	qi::rule<Iterator, JsonObject(), spc::space_type> object_rule;
	qi::rule<Iterator, JsonObject(), spc::space_type> bool_rule;
	qi::rule<Iterator, JsonObject(), spc::space_type> null_rule;
	qi::rule<Iterator, JsonObject(), spc::space_type> json_rule;
	qi::rule<Iterator, JsonObject(), spc::space_type> expression;
	std::vector<JsonObject> zero_array;
};


}// namespace GooglePlusLibrary
}// namespace Gplusnasite