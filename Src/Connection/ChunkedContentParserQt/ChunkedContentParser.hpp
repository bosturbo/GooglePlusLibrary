#pragma once

#ifdef GOOGLEPLUSLIBRARY_NO_WARNINGS
#ifdef _MSC_VER
#pragma warning (disable:4819)
#endif
#endif

#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class ChunkedContentParser
{
public:
	ChunkedContentParser();

	void readResponse(unsigned int size, const std::string& response);

	bool parse(const std::string& response);

	std::string getResult();

	virtual ~ChunkedContentParser();
private:
	std::string response_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite