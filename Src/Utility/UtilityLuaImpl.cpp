#include <Utility/UtilityImpl.hpp>
#include <Json/JsonObject.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

JsonObject UtilityImpl::convertStringEscapedJson(luabind::object node_object, const string& node_path)
{
	if (luabind::type(node_object) != LUA_TLIGHTUSERDATA)
	{
		return JsonObject();
	}
	JsonObject* node_pointer = static_cast<JsonObject*>(lua_touserdata(node_object.interpreter(),1));

	return convertStringEscapedJson(*node_pointer, node_path);
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite