#pragma once

#ifdef _MSC_VER
#pragma warning (disable:4819)
#endif

#include <string>
#include <vector>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class JsonObject;

class JsonPathParser
{
public:
	JsonPathParser();

	JsonObject parse(const JsonObject& object, const std::wstring& path) const;

	virtual ~JsonPathParser();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite