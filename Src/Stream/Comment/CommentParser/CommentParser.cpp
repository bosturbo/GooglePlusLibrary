#include <Stream/Comment/CommentParser/CommentParser.hpp>
#include <Stream/Comment/CommentContainer/CommentContainer.hpp>
#include <Utility/Utility.hpp>
#include <Utility/LuaScript.hpp>
#include <Json/JsonObject.hpp>

#include <luabind/luabind.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

queue<Comment> CommentParser::comment_info_queue;

CommentParser::CommentParser()
{
}

void CommentParser::add(JsonObject& json)
{
	LuaScript<CommentSetter(JsonObject*)> lua_script("LuaScript/ParseComment.lua", "parseComment", [](lua_State* lua_state)
	{
		CommentSetter::bindToScript(lua_state);
		Utility::bindToScript(lua_state);
		JsonObject::bindToScript(lua_state);
		bindToScript(lua_state);
	});

	CommentContainer::insert(lua_script(&json).toComment());
}

void CommentParser::erase(const string& comment_id)
{
	CommentContainer::erase(Utility::convertUTF8ToUnicode(comment_id));
}

void CommentParser::erase(const wstring& comment_id)
{
	CommentContainer::erase(comment_id);
}

void CommentParser::bindToScript(lua_State* lua_state)
{
	module(lua_state)
		[
			class_<CommentParser>("CommentParser")
			.def(constructor<>())
			.scope
				[
					def("add", &CommentParser::add)
				]
			.scope
				[
					def("erase", static_cast<void(*)(const string&)>(&CommentParser::erase))
				]
		];
}

CommentParser::~CommentParser()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
