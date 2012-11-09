#include <Stream/Post/PostParser/PostParser.hpp>
#include <Stream/Post/PostContainer/PostContainer.hpp>
#include <Json/JsonObject.hpp>
#include <Utility/Utility.hpp>
#include <Utility/LuaScript.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace ::luabind;

queue<Post> PostParser::post_info_queue;

PostParser::PostParser()
{
}

void PostParser::erase(const string& post_id)
{
	PostContainer::erase(Utility::convertUTF8ToUnicode(post_id));
}

void PostParser::erase(const wstring& post_id)
{
	PostContainer::erase(post_id);
}

void PostParser::bindToScript(lua_State* lua_state)
{
	module(lua_state)
		[
			class_<PostParser>("PostParser")
			.def(constructor<>())
			.scope
				[
					def("add", &PostParser::add)
				]
			.scope
				[
					def("erase", static_cast<void(*)(const string&)>(&PostParser::erase))
				]
		];
}

PostParser::~PostParser()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
