#pragma once

#ifdef _MSC_VER
#pragma warning (disable:4819)
#pragma warning (disable:4996)
#endif

#include <boost/spirit/include/qi.hpp>
#include <boost/any.hpp>

#include <lua.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class JsonMember;
class JsonObjectImpl;

class JsonObject
{
public:
	BOOST_SCOPED_ENUM_START(ObjectType)
	{
		Int, // int
		Real, // double
		String, // std::wstring
		Bool, // bool
		Array, // std::vector<JsonObject>
		Object, // std::vector<JsonMember>
		Null // null
	}; BOOST_SCOPED_ENUM_END
	
public:
	JsonObject();
	JsonObject(const JsonObject& object);
	explicit JsonObject(int value);
	explicit JsonObject(double value);
	JsonObject(const std::wstring& value);
	JsonObject(const std::vector<JsonObject>& value);
	JsonObject(const std::vector<JsonMember>& value);
	explicit JsonObject(bool value);

public:
	BOOST_SCOPED_ENUM(ObjectType) getType() const;

	bool isNull() const;
	
	int asInt() const;
	double asDouble() const;
	std::string asString() const;
	std::wstring asWString() const;
	bool asBool() const;
	std::vector<JsonObject> asArray() const;
	std::vector<JsonMember> asMember() const;
public:
	std::string getTypeAsString() const;
	std::wstring getTypeAsWString() const;
public:
	void show() const;

	JsonObject selectChildNode(const std::string& node_path);

	JsonObject selectChildNode(const std::wstring& node_path);

	JsonObject selectChildNode(int position);

	std::vector<JsonObject> getChildNodes() const;

	int count() const;

	JsonObject operator=(const JsonObject& rhs);
	JsonObject operator[](const std::string& name) const;
	JsonObject operator[](const std::wstring& name) const;
	JsonObject operator[](unsigned int position) const;

	JsonObject operator<<(const JsonObject& rhs) const;

	static std::wstring convertUTF8ToUnicode(std::string source);
	static std::string convertUnicodeToUTF8(std::wstring source);
	static void bindToScript(lua_State* lua_state);

public:
	~JsonObject();
private:
	std::shared_ptr<JsonObjectImpl> impl_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite