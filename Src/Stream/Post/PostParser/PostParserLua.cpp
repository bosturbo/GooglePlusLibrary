#include <Stream/Post/PostParser/PostParser.hpp>
#include <Stream/Post/PostContainer/PostContainer.hpp>
#include <AttachedInfo/AttachedLocation/AttachedLocationSetter.hpp>
#include <AttachedInfo/AttachedSearchResult/AttachedSearchResultSetter.hpp>
#include <AttachedInfo/AttachedUrl/AttachedUrlSetter.hpp>
#include <Utility/Utility.hpp>
#include <Utility/LuaScript.hpp>
#include <Json/JsonObject.hpp>

#include <luabind/luabind.hpp>
#include <Stream/Post/MyPost/MyPost.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

void PostParser::add(JsonObject& json)
{
	LuaScript<PostSetter(JsonObject*)> lua_script("LuaScript/ParsePost.lua", "parsePost", [](lua_State* lua_state)
	{
		PostSetter::bindToScript(lua_state);
		AttachedLocationSetter::bindToScript(lua_state);
		AttachedSearchResultSetter::bindToScript(lua_state);
		AttachedUrlSetter::bindToScript(lua_state);
		Utility::bindToScript(lua_state);
		JsonObject::bindToScript(lua_state);
		bindToScript(lua_state);
	});
	
	PostContainer::insert(lua_script(&json));
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
