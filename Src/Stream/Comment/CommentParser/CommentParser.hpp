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
#pragma warning (disable:4251)
#pragma warning (disable:4996)
#endif
#endif

#include <Stream/Comment/CommentSetter.hpp>

#include <string>
#include <queue>

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class JsonObject;

/*!
* @~english
* @brief Class to convert a Json to a Comment
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @~japanese
* @brief Json���R�����g�N���X�ɕϊ����邽�߂̃N���X
* @warning ���̃N���X�̓��C�u�����J���҂Ȃ�т�Lua�X�N���v�g�ҏW�҈ȊO���p���Ȃ��悤�ɂ��Ă�������
*/
class GOOGLEPLUSLIBRARY_API CommentParser
{
public:
	CommentParser();
	
	/*!
	* @~english
	* @brief Converts Json to Comment and update the comment list of all applicable
	* @param json Json comment information is stored
	* @~japanese
	* @brief Json��Comment�N���X�ɕϊ����A�Y�����邷�ׂẴR�����g���X�g���X�V���܂�
	* @param json �R�����g��񂪊i�[����Ă���Json
	*/
	static void add(JsonObject& json);

	/*!
	* @~english
	* @brief removes the specified ID from the comment list of all applicable
	* @param comment_id ID of the comment has been deleted(e.g. z12jxbmyulblgnudc232srv5iw3futrdp#1335189462073143)
	* @~japanese
	* @brief �w�肳�ꂽID�̃R�����g���Y�����邷�ׂẴR�����g���X�g����폜���܂�
	* @param comment_id �폜���ꂽ�R�����g��ID(��: z12jxbmyulblgnudc232srv5iw3futrdp#1335189462073143)
	*/
	static void erase(const std::string& comment_id);
	static void erase(const std::wstring& comment_id);

public:
	static void bindToScript(lua_State* lua_state);

public:
	virtual ~CommentParser();

private:
	static std::queue<Comment> comment_info_queue;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
