#pragma once

#ifdef _MSC_VER
#pragma warning (disable:4819)
#endif

#include <boost/spirit/include/qi.hpp>
#include <boost/any.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class JsonObject;
class JsonMember;

class JsonObjectImpl
{
public:
	BOOST_SCOPED_ENUM_START(ObjectImplType)
	{
		Int, // int
		Real, // double
		String, // std::wstring
		Bool, // bool
		Array, // std::vector<JsonObject>
		Object, // std::vector<JsonMember>
		Null // null
	}; BOOST_SCOPED_ENUM_END
	
	BOOST_SCOPED_ENUM(ObjectImplType) type_;
	boost::any value_;

	JsonObjectImpl();
	
	explicit JsonObjectImpl(BOOST_SCOPED_ENUM(ObjectImplType) type, boost::any value = boost::any());

	BOOST_SCOPED_ENUM(ObjectImplType) getType() const;
	
	int asInt() const;
	double asDouble() const;
	std::wstring asWString() const;
	bool asBool() const;
	std::vector<JsonObject> asArray() const;
	std::vector<JsonMember> asMember() const;
	
	JsonObject getByName(const std::wstring& name) const;
	JsonObject getByPosition(unsigned int position) const;

	void pushBack(const JsonObject& rhs);
	
	std::vector<JsonObject> getChildNodes() const;

	int count() const;
	
	virtual ~JsonObjectImpl();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite