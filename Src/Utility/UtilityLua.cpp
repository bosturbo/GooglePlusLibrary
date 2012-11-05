#include <Utility/Utility.hpp>
#include <Utility/UtilityImpl.hpp>
#include <Json/JsonObject.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

void Utility::bindToScript(lua_State* lua_state)
{
	module(lua_state)
		[
			class_<Utility>("Utility")
			.def(constructor<>())
			.scope
				[
					def("getRandomValue", &Utility::getRandomValue)
				]
			.scope
				[
					def("getRandomRequestID", &Utility::getRandomRequestID)
				]
			.scope
				[
					def("convertStringEscapedJson", static_cast<JsonObject(*)(JsonObject, const string&)>(&Utility::convertStringEscapedJson))
				]
			.scope
				[
					def("convertStringEscapedJson", static_cast<JsonObject(*)(luabind::object, const string&)>(&Utility::convertStringEscapedJson))
				]
			.scope
				[
					def("generateRandomString", &Utility::generateRandomString)
				]
			.scope
				[
					def("getUnixTime", &Utility::getUnixTime)
				]
			.scope
				[
					def("convertUnixTimeFromString", static_cast<boost::posix_time::ptime(*)(const string&)>(&Utility::convertUnixTimeFromString))
				]
		];
	
	module(lua_state)
		[
			class_<boost::posix_time::ptime>("ptime")
			.def(constructor<>())
		];
}

JsonObject Utility::convertStringEscapedJson(luabind::object node_object, const string& node_path)
{
	return UtilityImpl::convertStringEscapedJson(node_object, node_path);
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite