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

#include <Account/AccountProfile/NicknameDisplayType.hpp>
#include <Account/AccountProfile/Employment.hpp>
#include <Account/AccountProfile/Education.hpp>
#include <Account/AccountProfile/LivedPlace.hpp>
#include <Account/AccountProfile/ContactAddress.hpp>
#include <Account/AccountProfile/PartnershipType.hpp>
#include <Account/AccountProfile/RelationshipType.hpp>
#include <Account/AccountProfile/Gender.hpp>
#include <Account/AccountProfile/LabeledLink.hpp>

#include <list>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

/*!
* @~english
* @brief Class in order to obtain more information about the account
* @~japanese
* @brief �A�J�E���g�̏ڍ׏����擾���邽�߂̃N���X
*/
class GOOGLEPLUSLIBRARY_API MyAccountProfile
{
public:
	MyAccountProfile();

	/*!
	* @~english
	* @brief Gets the ID of the target account of this profile
	* @return Target Account ID of this profile
	* @~japanese
	* @brief ���̃v���t�B�[���̑ΏۃA�J�E���g��ID���擾���܂�
	* @return ���̃v���t�B�[���̑ΏۃA�J�E���g��ID
	*/
	std::wstring getTargetAccountID() const;

	/*!
	* @~english
	* @brief Sets the ID of the target account of this profile
	* @param target_account_id Target Account ID of this profile
	* @~japanese
	* @brief ���̃v���t�B�[���̑ΏۃA�J�E���g��ID��ݒ肵�܂�
	* @param target_account_id ���̃v���t�B�[���̑ΏۃA�J�E���g��ID
	*/
	void setTargetAccountID(const std::wstring& target_account_id);
private:
	std::wstring target_account_id_;

public:
	/*!
	* @~english
	* @brief Gets the first name of the account
	* @return First name of the account
	* @~japanese
	* @brief �A�J�E���g�̖����擾���܂�
	* @return �A�J�E���g�̖�
	*/
	std::wstring getFirstName() const;

	/*!
	* @~english
	* @brief Sets the first name of the account
	* @param first_name First name of the account
	* @~japanese
	* @brief �A�J�E���g�̖���ݒ肵�܂�
	* @param first_name �A�J�E���g�̖�
	*/
	void setFirstName(const std::wstring& first_name);
private:
	std::wstring first_name_;

public:
	/*!
	* @~english
	* @brief Gets the last name of the account
	* @return Last name of the account
	* @~japanese
	* @brief �A�J�E���g�̐����擾���܂�
	* @return �A�J�E���g�̐�
	*/
	std::wstring getLastName() const;

	/*!
	* @~english
	* @brief Sets the last name of the account
	* @param last_name Last name of the account
	* @~japanese
	* @brief �A�J�E���g�̐���ݒ肵�܂�
	* @param last_name �A�J�E���g�̐�
	*/
	void setLastName(const std::wstring& last_name);
private:
	std::wstring last_name_;

public:
	/*!
	* @~english
	* @brief Gets the nickname of the account
	* @return Nickname of the account
	* @~japanese
	* @brief �A�J�E���g�̃j�b�N�l�[�����擾���܂�
	* @return �A�J�E���g�̃j�b�N�l�[��
	*/
	std::wstring getNickname() const;

	/*!
	* @~english
	* @brief Sets the nickname of the account
	* @param nickname Nickname of the account
	* @~japanese
	* @brief �A�J�E���g�̃j�b�N�l�[����ݒ肵�܂�
	* @param nickname �A�J�E���g�̃j�b�N�l�[��
	*/
	void setNickname(const std::wstring& nickname);
private:
	std::wstring nickname_;

public:
	/*!
	* @~english
	* @brief Gets the display type of a nickname
	* @return Display type of a nickname
	* @~japanese
	* @brief �j�b�N�l�[���̕\���^�C�v���擾���܂�
	* @return �j�b�N�l�[���̕\���^�C�v
	*/
	NicknameDisplayType getNicknameDisplayType() const;

	/*!
	* @~english
	* @brief Sets the display type of a nickname
	* @param nick_name_display_type Display type of a nickname
	* @~japanese
	* @brief �j�b�N�l�[���̕\���^�C�v��ݒ肵�܂�
	* @param nick_name_display_type �j�b�N�l�[���̕\���^�C�v
	*/
	void setNicknameDisplayType(const NicknameDisplayType& nick_name_display_type);
private:
	NicknameDisplayType nick_name_display_type_;

public:
	/*!
	* @~english
	* @brief Gets the tagline of the account
	* @return Tagline of the account
	* @~japanese
	* @brief �A�J�E���g�̃L���b�`�t���[�Y���擾���܂�
	* @return �A�J�E���g�̃L���b�`�t���[�Y
	*/
	std::wstring getTaglineMessage() const;

	/*!
	* @~english
	* @brief Sets the tagline of the account
	* @param tagline_message Tagline of the account
	* @~japanese
	* @brief �A�J�E���g�̃L���b�`�t���[�Y��ݒ肵�܂�
	* @param tagline_message �A�J�E���g�̃L���b�`�t���[�Y
	*/
	void setTaglineMessage(const std::wstring& tagline_message);
private:
	std::wstring tagline_message_;

public:
	/*!
	* @~english
	* @brief Gets the message introduction of account
	* @return Introduction of account message
	* @~japanese
	* @brief �A�J�E���g�̏Љ���擾���܂�
	* @return �A�J�E���g�̏Љ
	*/
	std::wstring getIntroductionMessage() const;

	/*!
	* @~english
	* @brief Sets the message introduction of account
	* @param introduction_message Introduction of account message
	* @~japanese
	* @brief �A�J�E���g�̏Љ�b�Z�[�W��ݒ肵�܂�
	* @param introduction_message �A�J�E���g�̏Љ�b�Z�[�W
	*/
	void setIntroductionMessage(const std::wstring& introduction_message);
private:
	std::wstring introduction_message_;

public:
	/*!
	* @~english
	* @brief Gets the bragging rights
	* @return the bragging rights
	* @~japanese
	* @brief �����ł��邱�Ƃ��擾���܂�
	* @return �����ł��邱��
	*/
	std::wstring getBraggingRights() const;

	/*!
	* @~english
	* @brief Sets the bragging rights
	* @param bragging_rights the bragging rights
	* @~japanese
	* @brief �����ł��邱�Ƃ�ݒ肵�܂�
	* @param bragging_rights �����ł��邱��
	*/
	void setBraggingRights(const std::wstring& bragging_rights);
private:
	std::wstring bragging_rights_;

public:
	/*!
	* @~english
	* @brief Gets the occupation
	* @return The occupation
	* @~japanese
	* @brief �E�Ƃ��擾���܂�
	* @return �E��
	*/
	std::wstring getOccupation() const;

	/*!
	* @~english
	* @brief Sets the occupation
	* @param occupation The occupation
	* @~japanese
	* @brief �E�Ƃ�ݒ肵�܂�
	* @param occupation �E��
	*/
	void setOccupation(const std::wstring& occupation);
private:
	std::wstring occupation_;

public:
	/*!
	* @~english
	* @brief Gets the employments
	* @return The employments
	* @~japanese
	* @brief �E�����擾���܂�
	* @return �E��
	*/
	std::list<Employment> getEmployments() const;

	/*!
	* @~english
	* @brief Sets the employments
	* @param employments The employments
	* @~japanese
	* @brief �E����ݒ肵�܂�
	* @param employments �E��
	*/
	void setEmployments(const std::list<Employment>& employments);

	/*!
	* @~english
	* @brief Adds the employment
	* @param employment The employment
	* @~japanese
	* @brief �E����ǉ����܂�
	* @param employment �E��
	*/
	void addEmployments(const Employment& employment);
private:
	std::list<Employment> employments_;

public:
	/*!
	* @~english
	* @brief Gets the educations
	* @return The educations
	* @~japanese
	* @brief �w�����擾���܂�
	* @return �w��
	*/
	std::list<Education> getEducations() const;

	/*!
	* @~english
	* @brief Sets the education
	* @param educations The education
	* @~japanese
	* @brief �w����ݒ肵�܂�
	* @param educations �w��
	*/
	void setEducations(const std::list<Education>& educations);

	/*!
	* @~english
	* @brief Adds the education
	* @param education The education
	* @~japanese
	* @brief �w����ǉ����܂�
	* @param education �w��
	*/
	void addEducation(const Education& education);
private:
	std::list<Education> educations_;

public:
	/*!
	* @~english
	* @brief Gets the areas that have lived
	* @return Areas that have lived
	* @~japanese
	* @brief �Z�񂾂��Ƃ̂���n����擾���܂�
	* @return �Z�񂾂��Ƃ̂���n��
	*/
	std::list<LivedPlace> getLivedPlaces() const;

	/*!
	* @~english
	* @brief Sets the areas that have lived
	* @param lived_places Areas that have lived
	* @~japanese
	* @brief �Z�񂾂��Ƃ̂���n���ݒ肵�܂�
	* @param lived_places �Z�񂾂��Ƃ̂���n��
	*/
	void setLivedPlaces(const std::list<LivedPlace>& lived_places);

	/*!
	* @~english
	* @brief Adds the areas that have lived
	* @param lived_place Areas that have lived
	* @~japanese
	* @brief �Z�񂾂��Ƃ̂���n���ǉ����܂�
	* @param lived_place �Z�񂾂��Ƃ̂���n��
	*/
	void addLivedPlaces(const LivedPlace& lived_place);
private:
	std::list<LivedPlace> lived_places_;

public:
	/*!
	* @~english
	* @brief Gets the (home) ContactAddress
	* @return ContactAddress(home)
	* @~japanese
	* @brief �A����(����)���擾���܂�
	* @return �A����(����)
	*/
	std::list<ContactAddress> getHomeContactAddress() const;

	/*!
	* @~english
	* @brief Sets the (home) ContactAddresses
	* @param home_contact_addresses ContactAddresses(home)
	* @~japanese
	* @brief �A����(����)��ݒ肵�܂�
	* @param home_contact_addresses �A����(����)
	*/
	void setHomeContactAddress(const std::list<ContactAddress>& home_contact_addresses);

	/*!
	* @~english
	* @brief Adds the (home) ContactAddress
	* @param home_contact_address ContactAddresses(home)
	* @~japanese
	* @brief �A����(����)��ǉ����܂�
	* @param home_contact_address �A����(����)
	*/
	void addHomeContactAddress(const ContactAddress& home_contact_address);
private:
	std::list<ContactAddress> home_contact_addresses_;

public:
	/*!
	* @~english
	* @brief Gets the (work) ContactAddresses
	* @return ContactAddresses(work)
	* @~japanese
	* @brief �A����(�d��)���擾���܂�
	* @return �A����(�d��)
	*/
	std::list<ContactAddress> getWorkContactAddress() const;

	/*!
	* @~english
	* @brief Sets the (work) ContactAddresses
	* @param work_contact_addresses ContactAddresses(work)
	* @~japanese
	* @brief �A����(�d��)��ݒ肵�܂�
	* @param work_contact_addresses �A����(�d��)
	*/
	void setWorkContactAddress(const std::list<ContactAddress>& work_contact_addresses);

	/*!
	* @~english
	* @brief Adds the (work) ContactAddress
	* @param work_contact_address ContactAddress(work)
	* @~japanese
	* @brief �A����(�d��)��ǉ����܂�
	* @param work_contact_address �A����(�d��)
	*/
	void addWorkContactAddress(const ContactAddress& work_contact_address);
private:
	std::list<ContactAddress> work_contact_addresses_;

public:
	/*!
	* @~english
	* @brief Gets the partner relationship
	* @return Partnership
	* @~japanese
	* @brief �p�[�g�i�[�֌W���擾���܂�
	* @return �p�[�g�i�[�֌W
	*/
	PartnershipType getPartnershipType() const;

	/*!
	* @~english
	* @brief Sets the partner relationship
	* @param partnership_type Partnership
	* @~japanese
	* @brief �p�[�g�i�[�֌W��ݒ肵�܂�
	* @param partnership_type �p�[�g�i�[�֌W
	*/
	void setPartnershipType(const PartnershipType& partnership_type);
private:
	PartnershipType partnership_type_;

public:
	/*!
	* @~english
	* @brief Get the relationship that you want expanded
	* @return The relationship that you want expanded
	* @~japanese
	* @brief �L�������֌W���擾���܂�
	* @return �L�������֌W
	*/
	RelationshipType getRelationshipType() const;

	/*!
	* @~english
	* @brief Set the relationship that you want expanded
	* @param relationship_type The relationship that you want expanded
	* @~japanese
	* @brief �L�������֌W��ݒ肵�܂�
	* @param relationship_type �L�������֌W
	*/
	void setRelationshipType(const RelationshipType& relationship_type);
private:
	RelationshipType relationship_type_;

public:
	/*!
	* @~english
	* @brief Gets the gender
	* @return Gender
	* @~japanese
	* @brief ���ʂ��擾���܂�
	* @return ����
	*/
	Gender getGender() const;

	/*!
	* @~english
	* @brief Sets the gender
	* @param gender Gender
	* @~japanese
	* @brief ���ʂ�ݒ肵�܂�
	* @param gender ����
	*/
	void setGender(const Gender& gender);
private:
	Gender gender_;

public:
	/*!
	* @~english
	* @brief Gets the name of the other
	* @return Other name
	* @~japanese
	* @brief ���̖��O���擾���܂�
	* @return ���̖��O
	*/
	std::list<std::wstring> getOtherNames() const;

	/*!
	* @~english
	* @brief Sets the name of the other
	* @param other_names Other name
	* @~japanese
	* @brief ���̖��O��ݒ肵�܂�
	* @param other_names ���̖��O
	*/
	void setOtherNames(const std::list<std::wstring>& other_names);

	/*!
	* @~english
	* @brief Sets the name of the other
	* @param other_name Other name
	* @~japanese
	* @brief ���̖��O��ݒ肵�܂�
	* @param other_name ���̖��O
	*/
	void addOtherNames(const std::wstring& other_name);
private:
	std::list<std::wstring> other_names_;

public:
	/*!
	* @~english
	* @brief Get the other profile page
	* @return Other profile page
	* @~japanese
	* @brief ���̃v���t�B�[���y�[�W���擾���܂�
	* @return ���̃v���t�B�[���y�[�W
	*/
	std::list<LabeledLink> getOtherProfilePages() const;

	/*!
	* @~english
	* @brief Set the other profile page
	* @param other_profile_pages Other profile page
	* @~japanese
	* @brief ���̃v���t�B�[���y�[�W��ݒ肵�܂�
	* @param other_profile_pages ���̃v���t�B�[���y�[�W
	*/
	void setOtherProfilePages(const std::list<LabeledLink>& other_profile_pages);

	/*!
	* @~english
	* @brief Add the other profile page
	* @param other_profile_page Other profile page
	* @~japanese
	* @brief ���̃v���t�B�[���y�[�W��ǉ����܂�
	* @param other_profile_page ���̃v���t�B�[���y�[�W
	*/
	void addOtherProfilePages(const LabeledLink& other_profile_page);
private:
	std::list<LabeledLink> other_profile_pages_;

public:
	/*!
	* @~english
	* @brief Gets the target page account posts have been posted
	* @return Post subject page of the account have been posted
	* @~japanese
	* @brief �Ώۂ̃A�J�E���g�̓��e���f�ڂ���Ă���y�[�W���擾���܂�
	* @return �Ώۂ̃A�J�E���g�̓��e���f�ڂ���Ă���y�[�W
	*/
	std::list<LabeledLink> getYourPostPages() const;

	/*!
	* @~english
	* @brief Sets the target page account posts have been posted
	* @param your_post_pages Post subject page of the account have been posted
	* @~japanese
	* @brief �Ώۂ̃A�J�E���g�̓��e���f�ڂ���Ă���y�[�W��ݒ肵�܂�
	* @param your_post_pages �Ώۂ̃A�J�E���g�̓��e���f�ڂ���Ă���y�[�W
	*/
	void setYourPostPages(const std::list<LabeledLink>& your_post_pages);

	/*!
	* @~english
	* @brief Adds the target page account posts have been posted
	* @param your_post_page Post subject page of the account have been posted
	* @~japanese
	* @brief �Ώۂ̃A�J�E���g�̓��e���f�ڂ���Ă���y�[�W��ǉ����܂�
	* @param your_post_page �Ώۂ̃A�J�E���g�̓��e���f�ڂ���Ă���y�[�W
	*/
	void addYourPostPages(const LabeledLink& your_post_page);
private:
	std::list<LabeledLink> your_post_pages_;

public:
	/*!
	* @~english
	* @brief Gets the list of links recommended
	* @return A list of links recommended
	* @~japanese
	* @brief �������߂̃����N�̃��X�g���擾���܂�
	* @return �������߂̃����N�̃��X�g
	*/
	std::list<LabeledLink> getRecommendedLinks() const;

	/*!
	* @~english
	* @brief Sets the list of links recommended
	* @param recommended_links A list of links recommended
	* @~japanese
	* @brief �������߂̃����N�̃��X�g��ݒ肵�܂�
	* @param recommended_links �������߂̃����N�̃��X�g
	*/
	void setRecommendedLinks(const std::list<LabeledLink>& recommended_links);

	/*!
	* @~english
	* @brief Adds the link recommendation
	* @param label Label attached to the link you want to add
	* @param url The Url of the link you want to add
	* @~japanese
	* @brief �������߂̃����N��ǉ����܂�
	* @param label �ǉ������������N�ɂ��郉�x��
	* @param url �ǉ������������N��Url
	*/
	void addRecommendedLinks(const std::wstring& label, const std::wstring& url);

private:
	std::list<LabeledLink> recommended_links_;

virtual ~MyAccountProfile();
private:
	std::shared_ptr<ReadWriteMutex> read_write_mutex_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite