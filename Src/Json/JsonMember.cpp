#include <Json/JsonMember.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

JsonMember::JsonMember()
:name_(),
element_()
{
}

JsonMember::JsonMember(const wstring& name, const JsonObject& element)
:name_(name),
element_(element)
{
}

bool JsonMember::operator<(const JsonMember& rhs) const
{
	return name_ < rhs.name_;
}

wstring JsonMember::getName() const
{
	return name_;
}

JsonObject JsonMember::getValue() const
{
	return element_;
}

wstring JsonMember::asWString() const
{
	wstring result(name_ + L" : " + element_.asWString());
	return result;
}

JsonMember::~JsonMember()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite