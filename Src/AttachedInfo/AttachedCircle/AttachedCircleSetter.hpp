#pragma once

#ifdef _MSC_VER
#ifdef GOOGLEPLUSLIBRARY_EXPORTS
#define GOOGLEPLUSLIBRARY_API __declspec(dllexport)
#else
#define GOOGLEPLUSLIBRARY_API __declspec(dllimport)
#endif
#else
#define GOOGLEPLUSLIBRARY_API
#endif

#include <AttachedInfo/AttachedCircle/AttachedCircleBase.hpp>

#include <luabind/luabind.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API AttachedCircleSetter : public AttachedCircleBase
{
public:
	AttachedCircleSetter();

	static AttachedCircleSetter parse(JsonObject& json);
	static AttachedCircleSetter parse(luabind::object json);

	void addAccount(const std::wstring& account_id);

	AttachedCircle toAttachedCircle();

	static void bindToScript(lua_State* lua_state);

	virtual ~AttachedCircleSetter();

private:
	AttachedCircle attached_circle_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite