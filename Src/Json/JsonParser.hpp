#pragma once

#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class JsonObject;

class JsonParser
{
public:
	JsonParser();

	JsonObject parse(const std::wstring& json) const;

	virtual ~JsonParser();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite