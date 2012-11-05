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

#ifdef GOOGLEPLUSLIBRARY_NO_WARNINGS
#ifdef _MSC_VER
#pragma warning (disable:4996)
#endif
#endif

#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <luabind/luabind.hpp>

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class JsonObject;

/*!
* @~english
* @brief class that packed the props in this library useful
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief このライブラリにおける便利な小道具を詰め込んでいるクラス
* @warning このクラスはライブラリ開発者ならびにLuaスクリプト編集者以外利用しないようにしてください
*/
class GOOGLEPLUSLIBRARY_API UtilityImpl
{
public:
	UtilityImpl();
	
	static std::wstring convertUTF8ToUnicode(std::string source);
	static std::string convertUnicodeToUTF8(std::wstring source);
	
	static std::string getRandomValue(int min_value, int max_value, std::string error_value = "");

	static std::string getRandomRequestID();

	static JsonObject convertStringEscapedJson(JsonObject node, const std::string& node_path);

	static JsonObject convertStringEscapedJson(luabind::object node_object, const std::string& node_path);

	static std::string generateRandomString(int min_length, int max_length, std::string key_characters);

	// 例:1338465801
	static long getUnixTime();

	static boost::posix_time::ptime convertUnixTimeFromString(const std::string& unix_time_milliseconds);
	static boost::posix_time::ptime convertUnixTimeFromString(const std::wstring& unix_time_milliseconds);

	virtual ~UtilityImpl();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite