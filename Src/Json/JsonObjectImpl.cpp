#include <Json/JsonObjectImpl.hpp>
#include <Json/JsonObject.hpp>
#include <Json/JsonMember.hpp>
#include <Json/TypeException.hpp>
#include <Json/RangeException.hpp>

#include <boost/lexical_cast.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

JsonObjectImpl::JsonObjectImpl()
:type_(ObjectImplType::Null),
value_()
{
}

JsonObjectImpl::JsonObjectImpl(BOOST_SCOPED_ENUM(ObjectImplType) type, boost::any value)
:type_(type),
value_(value)
{
}

JsonObjectImpl::BOOST_SCOPED_ENUM(ObjectImplType) JsonObjectImpl::getType() const
{
	return type_;
}

int JsonObjectImpl::asInt() const
{
	if(ObjectImplType::Int == type_)
	{
		return boost::any_cast<int>(value_);
	}
	return 0;
}

double JsonObjectImpl::asDouble() const
{
	if(ObjectImplType::Real == type_)
	{
		return boost::any_cast<double>(value_);
	}
	return 0;
}

wstring JsonObjectImpl::asWString() const
{
	switch(type_)
	{
	case ObjectImplType::String:
		return boost::any_cast<wstring>(value_);
		break;
	case ObjectImplType::Int:
		{
			int value =  boost::any_cast<int>(value_);
			return boost::lexical_cast<wstring>(value);
		}
		break;
	case ObjectImplType::Real:
		{
			double value =  boost::any_cast<double>(value_);
			return boost::lexical_cast<wstring>(value);
		}
		break;
	case ObjectImplType::Bool:
		if(boost::any_cast<bool>(value_))
		{
			return L"true";
		}
		else
		{
			return L"false";
		}
		break;
	case ObjectImplType::Object:
		{
			vector<JsonMember> value =  boost::any_cast<const vector<JsonMember>&>(value_);

			wstring result(L"{");

			for(unsigned int count = 0; count < value.size(); ++count)
			{
				if(count > 0)
				{
					result += L", ";
				}
				result += value[count].asWString();
			}
			result += L"}";
			return result;
		}
		break;
	case ObjectImplType::Array:
		{
			vector<JsonObject> value =  boost::any_cast<const vector<JsonObject>&>(value_);

			wstring result(L"[");

			for(unsigned int count = 0; count < value.size(); ++count)
			{
				if(count > 0)
				{
					result += L", ";
				}
				result += value[count].asWString();
			}
			result += L"]";
			return result;
		}
		break;
	default:
		return L"null";
	}
}

bool JsonObjectImpl::asBool() const
{
	if(ObjectImplType::Bool == type_)
	{
		return boost::any_cast<bool>(value_);
	}
	return false;
}

vector<JsonObject> JsonObjectImpl::asArray() const
{
	if(ObjectImplType::Array == type_)
	{
		return boost::any_cast<const vector<JsonObject>&>(value_);
	}
	return vector<JsonObject>();
}

vector<JsonMember> JsonObjectImpl::asMember() const
{
	if(ObjectImplType::Object == type_)
	{
		return boost::any_cast<const vector<JsonMember>&>(value_);
	}
	return vector<JsonMember>();
}

JsonObject JsonObjectImpl::getByName(const wstring& name) const
{
	if(ObjectImplType::Object != type_)
	{
		return JsonObject();
	}

	JsonMember key(name, JsonObject());
	const vector<JsonMember>& v = boost::any_cast<const vector<JsonMember>&>(value_);
	vector<JsonMember>::const_iterator f = lower_bound(v.begin(), v.end(), key);
	if(f == v.end())
	{
		return JsonObject();
	}

	if((*f).getName() == name)
	{
		return (*f).getValue();
	}
	return JsonObject();
}

JsonObject JsonObjectImpl::getByPosition(unsigned int position) const
{
	if(ObjectImplType::Array != type_)
	{
		return JsonObject();
	}
	const vector<JsonObject>& v = boost::any_cast<const vector<JsonObject>&>(value_);
	if(position < 0 || v.size() <= position)
	{
		return JsonObject();
	}
	return v[position];
}

void JsonObjectImpl::pushBack(const JsonObject& rhs)
{
	if(ObjectImplType::Array == type_)
	{
		boost::any_cast<vector<JsonObject>&>(value_).push_back(rhs);
	}
	else if(ObjectImplType::Null == type_)
	{
		vector<JsonObject> v;
		v.push_back(rhs);
		value_ = v;
	}
	else
	{
		throw TypeException();
	}
}

vector<JsonObject> JsonObjectImpl::getChildNodes() const
{
	return asArray();
}

int JsonObjectImpl::count() const
{
	if(ObjectImplType::Array != type_)
	{
		return 0;
	}
	const vector<JsonObject>& v = boost::any_cast<const vector<JsonObject>&>(value_);
	return v.size();
}

JsonObjectImpl::~JsonObjectImpl()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite