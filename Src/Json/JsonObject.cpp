#include <Json/JsonObject.hpp>
#include <Json/JsonObjectImpl.hpp>
#include <Json/JsonMember.hpp>
#include <Json/JsonPathParser.hpp>

#include <luabind/luabind.hpp>

#include <utf8.h>

#include <cassert>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

JsonObject::JsonObject()
:impl_(make_shared<JsonObjectImpl>(JsonObjectImpl::ObjectImplType::Null))
{
#ifdef TRACE
	cout << "JsonObject()" << endl; 
#endif
	assert(impl_);
}

JsonObject::JsonObject(const JsonObject& object)
:impl_(object.impl_)
{
#ifdef TRACE
	cout << "JsonObject(JsonObject)" << endl;

	cout << "object.type_" << object.getTypeAsWString() << endl;
	cout << "type_" << getTypeAsWString() << endl;
#endif
	assert(impl_);
}

JsonObject::JsonObject(int value)
:impl_(make_shared<JsonObjectImpl>(JsonObjectImpl::ObjectImplType::Int, value))
{
#ifdef TRACE
	cout << "JsonObject(int)" << endl;
#endif
	assert(impl_);
}

JsonObject::JsonObject(double value)
:impl_(make_shared<JsonObjectImpl>(JsonObjectImpl::ObjectImplType::Real, value))
{
#ifdef TRACE
	cout << "JsonObject(double)" << endl;
#endif
	assert(impl_);
}

JsonObject::JsonObject(const wstring& value)
:impl_(make_shared<JsonObjectImpl>(JsonObjectImpl::ObjectImplType::String, value))
{
#ifdef TRACE
	cout << "JsonObject(wstring)" << endl;
#endif
	assert(impl_);
}

JsonObject::JsonObject(const vector<JsonObject>& value)
:impl_(make_shared<JsonObjectImpl>(JsonObjectImpl::ObjectImplType::Array, value))
{
#ifdef TRACE
	cout << "JsonObject(vector<JsonObject>)" << endl;
#endif
	assert(impl_);
}

JsonObject::JsonObject(const vector<JsonMember>& value)
:impl_(make_shared<JsonObjectImpl>(JsonObjectImpl::ObjectImplType::Object, value))
{
#ifdef TRACE
	cout << "JsonObject(vector<JsonMember>)" << endl;
#endif
	assert(impl_);
}

JsonObject::JsonObject(bool value)
:impl_(make_shared<JsonObjectImpl>(JsonObjectImpl::ObjectImplType::Bool, value))
{
#ifdef TRACE
	cout << "JsonObject(bool)" << endl;
#endif
	assert(impl_);
}

JsonObject JsonObject::operator=(const JsonObject& rhs)
{
#ifdef TRACE
	cout << "JsonObject operator = " << endl;
#endif
	impl_ = rhs.impl_;
	assert(impl_);
	return *this;
}

JsonObject JsonObject::operator[](const string& name) const
{
	assert(impl_);
	return impl_->getByName(convertUTF8ToUnicode(name));
}

JsonObject JsonObject::operator[](const wstring& name) const
{
	assert(impl_);
	return impl_->getByName(name);
}

JsonObject JsonObject::operator[](unsigned int position) const
{
	assert(impl_);
	return impl_->getByPosition(position);
}

JsonObject JsonObject::operator<<(const JsonObject& rhs) const
{
	assert(impl_);
	impl_->pushBack(rhs);
	return *this;
}

JsonObject::BOOST_SCOPED_ENUM(ObjectType) JsonObject::getType() const
{
	assert(impl_);
	switch(impl_->type_)
	{
	case JsonObjectImpl::ObjectImplType::Null: return ObjectType::Null;
	case JsonObjectImpl::ObjectImplType::Int: return ObjectType::Int;
	case JsonObjectImpl::ObjectImplType::Real: return ObjectType::Real;
	case JsonObjectImpl::ObjectImplType::Bool: return ObjectType::Bool;
	case JsonObjectImpl::ObjectImplType::Array: return ObjectType::Array;
	case JsonObjectImpl::ObjectImplType::Object: return ObjectType::Object;
	case JsonObjectImpl::ObjectImplType::String: return ObjectType::String;
	}
	return ObjectType::Null;
}

bool JsonObject::isNull() const
{
	switch(getType())
	{
	case ObjectType::Null:
		return true;
	default:
		return false;
		break;
	}
	return false;
}

int JsonObject::asInt() const
{
	assert(impl_);
	return impl_->asInt();
}

double JsonObject::asDouble() const
{
	assert(impl_);
	return impl_->asDouble();
}

string JsonObject::asString() const
{
	assert(impl_);
	return convertUnicodeToUTF8(impl_->asWString());
}

wstring JsonObject::asWString() const
{
	assert(impl_);
	return impl_->asWString();
}

bool JsonObject::asBool() const
{
	assert(impl_);
	return impl_->asBool();
}

vector<JsonObject> JsonObject::asArray() const
{
	assert(impl_);
	return impl_->asArray();
}

vector<JsonMember> JsonObject::asMember() const
{
	assert(impl_);
	return impl_->asMember();
}

string JsonObject::getTypeAsString() const
{
	return convertUnicodeToUTF8(getTypeAsWString());
}
	
wstring JsonObject::getTypeAsWString() const
{
	assert(impl_);
	switch(impl_->type_)
	{
	case JsonObjectImpl::ObjectImplType::Null: return L"Null";
	case JsonObjectImpl::ObjectImplType::Int: return L"Int";
	case JsonObjectImpl::ObjectImplType::Real: return L"Real";
	case JsonObjectImpl::ObjectImplType::Bool: return L"Bool";
	case JsonObjectImpl::ObjectImplType::Array: return L"Array";
	case JsonObjectImpl::ObjectImplType::Object: return L"Object";
	case JsonObjectImpl::ObjectImplType::String: return L"String";
	}
	return L"Unknown";
}

void JsonObject::show() const
{
	cout << asString() << endl;
}

JsonObject JsonObject::selectChildNode(const string& node_path)
{
	return selectChildNode(convertUTF8ToUnicode(node_path));
}

JsonObject JsonObject::selectChildNode(const wstring& node_path)
{
	JsonPathParser path_parser;
	return path_parser.parse(*this, node_path);
}

JsonObject JsonObject::selectChildNode(int position)
{
	assert(impl_);
	return impl_->getByPosition(position);
}

vector<JsonObject> JsonObject::getChildNodes() const
{
	assert(impl_);
	return impl_->getChildNodes();
}

int JsonObject::count() const
{
	assert(impl_);
	return impl_->count();
}

wstring JsonObject::convertUTF8ToUnicode(string source)
{
	wstring result(L"");

	string::iterator end_it = utf8::find_invalid(source.begin(), source.end());

	if (end_it != source.end())
	{
		cout << "Invalid UTF-8 encoding detected\n";
		cout << "This part is fine: " << string(source.begin(), end_it) << "\n";
	}

	vector<unsigned short> utf16line;
	utf8::utf8to16(source.begin(), end_it, back_inserter(utf16line));

	auto it = utf16line.begin();
	while(it != utf16line.end())
	{
		result += wchar_t(*it);
		++it;
	}

	if(!result.empty())
	{
		// Remove Bom
		if(result[0] == (wchar_t)65279)
		{
			result = result.substr(1);
		}
	}

	return result;
}

string JsonObject::convertUnicodeToUTF8(wstring source)
{
	string utf8line;
	utf8::utf16to8(source.begin(), source.end(), back_inserter(utf8line));
	return utf8line;
}

void JsonObject::bindToScript(lua_State* lua_state)
{
	module(lua_state)
		[
			class_<JsonObject>("JsonObject")
			.def(constructor<>())
			.def("isNull", &JsonObject::isNull)
			.def("asInt", &JsonObject::asInt)
			.def("asDouble", &JsonObject::asDouble)
			.def("asString", &JsonObject::asString)
			.def("asBool", &JsonObject::asBool)
			.def("asArray", &JsonObject::asArray)
			.def("asMember", &JsonObject::asMember)
			.def("getTypeAsString", &JsonObject::getTypeAsString)
			.def("show", &JsonObject::show)
			.def("selectChildNode", static_cast<JsonObject(JsonObject::*)(const string&)>(&JsonObject::selectChildNode))
			.def("selectChildNode", static_cast<JsonObject(JsonObject::*)(int)>(&JsonObject::selectChildNode))
			.def("count", &JsonObject::count)

		];
}

JsonObject::~JsonObject()
{
#ifdef TRACE
	cout << "JsonObjectのデストラクタが呼ばれました" << endl;
	cout << "type:" << getTypeAsWString() << endl;
#endif
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite