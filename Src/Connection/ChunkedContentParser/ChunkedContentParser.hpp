#pragma once

#ifdef GOOGLEPLUSLIBRARY_NO_WARNINGS
#ifdef _MSC_VER
#pragma warning (disable:4819)
#endif
#endif

#include <string>
#include <sstream>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class ChunkedContentParser
{
public:
	ChunkedContentParser();

	inline void readResponse(unsigned int size, const std::string& response);

	bool parse(const std::string& response);

	std::string getResult();

	virtual ~ChunkedContentParser();
private:
	std::stringstream response_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite