#pragma once

#include <Json/JsonObject.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class JsonMember
{
public:
	JsonMember();

	JsonMember(const std::wstring& name, const JsonObject& element);

	bool operator<(const JsonMember& rhs) const;

	std::wstring getName() const;

	JsonObject getValue() const;

	std::wstring asWString() const;
	
	virtual ~JsonMember();
private:
	std::wstring name_;
	JsonObject element_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite