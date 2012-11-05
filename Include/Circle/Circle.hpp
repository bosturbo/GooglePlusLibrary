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
#endif
#endif

#include <string>
#include <map>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class ReadWriteMutex;

/*!
* @~english
* @brief Class for operating circle information
* @~japanese
* @brief �T�[�N���𑀍삷�邽�߂̃N���X
*/
class GOOGLEPLUSLIBRARY_API Circle
{
	friend class ShareRangeList;
	friend class std::map<std::wstring, Circle>;

protected:
	Circle();
	Circle(const std::wstring& circle_name, const std::wstring& circle_id);

public:

	/*!
	* @~english
	* @brief Check for the correct format of circle ID
	* @return True if the format is correct, false if properly
	* @~japanese
	* @brief �T�[�N��ID�̃t�H�[�}�b�g�������������ׂ܂�
	* @return �t�H�[�}�b�g�����������true�A�������Ȃ����false
	*/
	static bool verifyCircleID(const std::wstring& circle_id);

	/*!
	* @~english
	* @brief Get circle id
	* @return circle id(e.g. 6e1ff5b889ea6c7e)
	* @~japanese
	* @brief �T�[�N��ID���擾���܂�
	* @return �T�[�N��ID(��: 6e1ff5b889ea6c7e)
	*/
	std::wstring getCircleID() const;
protected:

	/*!
	* @~english
	* @brief Set circle id
	* @param circle_id circle id(e.g. 6e1ff5b889ea6c7e)
	* @~japanese
	* @brief �T�[�N��ID��ݒ肵�܂�
	* @param circle_id �T�[�N��ID(��: 6e1ff5b889ea6c7e)
	*/
	void setCircleID(const std::wstring& circle_id);

private:
	std::wstring circle_id_;

public:

	/*!
	* @~english
	* @brief Gets the name of the circle
	* @return Circle name
	* @~japanese
	* @brief �T�[�N�������擾���܂�
	* @return �T�[�N����
	*/
	std::wstring getCircleName() const;
protected:

	/*!
	* @~english
	* @brief Sets the name of the Circle
	* @param circle_name Circle name
	* @~japanese
	* @brief �T�[�N������ݒ肵�܂�
	* @param circle_name �T�[�N����
	*/
	void setCircleName(const std::wstring& circle_name);
private:
	std::wstring circle_name_;

public:
	virtual ~Circle();

private:
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

} // namespace GooglePlusLibrary
} // namespace Gplusnasite
