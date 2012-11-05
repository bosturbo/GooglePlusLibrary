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
#pragma warning (disable:4275)
#pragma warning (disable:4996)
#endif
#endif

#include <Thread/ReadWriteMutex.hpp>

#include <boost/signals2.hpp>
#include <boost/utility.hpp>
#include <map>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Circle;

/*!
* @~english
* @brief Container class in order to be able to access circle information from anywhere
* @warning Please do not use use this class other than the editor of the Lua script and library developer
* @warning Please use the CircleList class if you are the general public
* @see CircleList
* @~japanese
* @brief �ǂ�����ł��T�[�N�����ɃA�N�Z�X�ł���悤�ɂ��邽�߂̃R���e�i�N���X
* @warning ���̃N���X�̓��C�u�����J���҂Ȃ�т�Lua�X�N���v�g�ҏW�҈ȊO���p���Ȃ��悤�ɂ��Ă�������
* @warning ��ʂ̕���CircleList�N���X�������p��������
* @see CircleList
*/
class GOOGLEPLUSLIBRARY_API CircleContainer : boost::noncopyable
{
public:
	CircleContainer();

	/*!
	* @~english
	* @brief Add circle in the Container
	* @details This is not a function to create a make_shared<circle>
	* @param circle circle information that add to the Container
	* @~japanese
	* @brief �R���e�i�ɃT�[�N������ǉ����܂�
	* @details ����̓T�[�N����V�K�쐬����֐��ł͂���܂���
	* @param circle �ǉ�����T�[�N�����
	*/
	static bool insert(const Circle& circle);
	static boost::signals2::signal<void (const Circle&)> onCircleinserted;

	static void updateItem(const Circle& circle);
	static boost::signals2::signal<void (const Circle&)> onCircleEdited;

	static bool erase(const std::wstring& comment_id);
	static boost::signals2::signal<void (const std::wstring&)> onCircleDeleted;
	
	static int count();

	/*!
	* @~english
	* @brief Get circle information from the Container
	* @details Returns null if the corresponding circle could not be found
	* @param circle_id ID of the circle information you want to get(e.g. 6e1ff5b889ea6c7e)
	* @return Circle information with the specified circle id
	* @~japanese
	* @brief �R���e�i����T�[�N�������擾���܂�
	* @details �Y������T�[�N����������Ȃ������ꍇnull��Ԃ��܂�
	* @param circle_id �擾�������T�[�N����ID(��: 6e1ff5b889ea6c7e)
	* @return �w�肵���T�[�N��ID�����T�[�N���̏��
	*/
	static const Circle* getByCircleID(const std::wstring& circle_id);

	const Circle* operator[](const std::wstring& circle_id);
	
	virtual ~CircleContainer();

private:
	static std::map<std::wstring, Circle> circle_container_;
	static ReadWriteMutex read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite