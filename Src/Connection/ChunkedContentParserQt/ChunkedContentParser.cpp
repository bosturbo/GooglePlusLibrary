#include "ChunkedContentParser.hpp"

#define BOOST_SPIRIT_DEBUG

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/home/classic/core.hpp>
#include <boost/spirit/home/classic/attribute.hpp>
#include <boost/spirit/home/classic/utility.hpp>

#include <utf8.h>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

namespace qi = boost::spirit::qi;
namespace phoenix = boost::phoenix;

ChunkedContentParser::ChunkedContentParser()
:response_("")
{
}

void ChunkedContentParser::readResponse(unsigned int size, const string& response)
{
	unsigned int next_position = size + 2;
	unsigned int response_size = response.size();

	cout << "Parsing Size:" << size << " / " << "Original Size:" << response_size << endl;

	if(next_position >= response.length())
	{
		response_ += response;
		cout << "Parsing Size: Over" << endl;
	}
	else
	{
		response_ += response.substr(0, next_position);
		parse(response.substr(next_position));
	}
}

bool ChunkedContentParser::parse(const string& response)
{
	string::const_iterator it = response.cbegin();

	qi::rule<string::const_iterator, int(), string()> chunked_response_rule = (qi::hex >> (qi::lit("\r") || qi::lit("\n")) >> qi::as_string[+qi::char_])[phoenix::bind(&ChunkedContentParser::readResponse, this, qi::_1, qi::_2)];
	
	bool result = boost::spirit::qi::parse(it, response.cend(), chunked_response_rule);
	return result;
}

string ChunkedContentParser::getResult()
{
	return response_;
}

ChunkedContentParser::~ChunkedContentParser()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite