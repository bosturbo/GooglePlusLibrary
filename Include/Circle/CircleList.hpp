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

#include <boost/thread.hpp>
#include <boost/signals2.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Circle;
class ReadWriteMutex;

/*!
* @~english
* @brief Class in order to obtain a list of circle information or to create a make_shared<circle>
* @~japanese
* @brief �T�[�N���̈ꗗ���擾������T�[�N����V�K�쐬�����肷�邽�߂̃N���X
*/
class GOOGLEPLUSLIBRARY_API CircleList
{
	friend class ShareRangeList;

public:
	CircleList();

public:

	/*!
	* @~english
	* @brief Update the list
	* @~japanese
	* @brief ���X�g���X�V���܂�
	*/
	void update();

	/*!
	* @~english
	* @brief Asynchronous update the list
	* @~japanese
	* @brief ���X�g��񓯊��ɍX�V���܂�
	*/
	void updateAsync();

	/*!
	* @~english
	* @brief Wait until you have completed asynchronous update of the list
	* @~japanese
	* @brief ���X�g�̔񓯊��X�V����������܂őҋ@���܂�
	*/
	void waitupdateAsync();

	boost::signals2::signal<void()> onUpdateCompleted;

private:

	/*!
	* @~english
	* @brief A function to update the list in a separate thread
	* @~japanese
	* @brief �ʃX���b�h�Ń��X�g�̍X�V������֐��ł�
	*/
	void updateAsyncThreadMethod();
	boost::thread update_thread_;

	/*!
	* @~english
	* @brief Gets the account id of the target
	* @details Returns the empty wstring if the account id of the target has not been set
	* @return the account id of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief �Ώۂ̃A�J�E���gID���擾���܂�
	* @details �Ώۂ̃A�J�E���gID���ݒ肳��Ă��Ȃ��ꍇ�͋󕶎���Ԃ��܂�
	* @return �Ώۂ̃A�J�E���gID(��: 116324207729009185938)
	*/
	std::wstring getMyAccountID() const;
protected:

	/*!
	* @~english
	* @brief Sets the account id of the target
	* @param my_account_id the account id of the target(e.g. 116324207729009185938)
	* @~japanese
	* @brief �Ώۂ̃A�J�E���gID��ݒ肵�܂�
	* @param my_account_id �Ώۂ̃A�J�E���gID(��: 116324207729009185938)
	*/
	void setMyAccountID(const std::wstring& my_account_id);
private:
	std::wstring my_account_id_;

protected:
	bool add(const std::wstring& circle_id);
	bool add(const Circle& circle);
	boost::signals2::signal<void (const Circle&)> onCircleAdded;

	void updateItem(const Circle& circle);
	boost::signals2::signal<void (const Circle&)> onCircleEdited;
	
	bool remove(const std::wstring& circle_id);
	boost::signals2::signal<void (const std::wstring&)> onCircleDeleted;

public:
	/*!
	* @~english
	* @brief Get circle information
	* @details Returns null if the corresponding circle could not be found
	* @param circle_id ID of the circle information you want to get(e.g. 6e1ff5b889ea6c7e)
	* @return Circle information with the specified circle id
	* @~japanese
	* @brief �T�[�N�������擾���܂�
	* @details �Y������T�[�N����������Ȃ������ꍇnull��Ԃ��܂�
	* @param circle_id �擾�������T�[�N����ID(��: 6e1ff5b889ea6c7e)
	* @return �w�肵���T�[�N��ID�����T�[�N���̏��
	*/
	const Circle* getByCircleID(const std::wstring& circle_id) const;

	const Circle* getByIndex(int index) const;

	/*!
	* @~english
	* @brief Get circle information
	* @details Returns null if the corresponding circle could not be found
	* @details This operator is only internally calls the getByCircleID
	* @param circle_id ID of the circle information you want to get(e.g. 6e1ff5b889ea6c7e)
	* @return Circle information with the specified circle id
	* @~japanese
	* @brief �T�[�N�������擾���܂�
	* @details �Y������T�[�N����������Ȃ������ꍇnull��Ԃ��܂�
	* @details ���̉��Z�q�͓����I��getByCircleID���Ăяo���Ă��邾���ł�
	* @param circle_id �擾�������T�[�N����ID(��: 6e1ff5b889ea6c7e)
	* @return �w�肵���T�[�N��ID�����T�[�N���̏��
	*/
	const Circle* operator[](const std::wstring& circle_id) const;

	const Circle* operator[](int index) const;

	int count() const;

public:
	virtual ~CircleList();

protected:
	struct search_sequence {};
	struct search_by_circle_id {};

	typedef boost::multi_index::multi_index_container<
		std::wstring,
		boost::multi_index::indexed_by<
		boost::multi_index::sequenced<boost::multi_index::tag<search_sequence> >,

		boost::multi_index::ordered_unique<
		boost::multi_index::tag<search_by_circle_id>,
		boost::multi_index::identity<std::wstring>
		>
		>
	> CircleIDList;
private:
	CircleIDList circle_id_list_;

private:
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite