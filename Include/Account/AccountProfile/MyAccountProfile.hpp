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
* @brief アカウントの詳細情報を取得するためのクラス
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
	* @brief このプロフィールの対象アカウントのIDを取得します
	* @return このプロフィールの対象アカウントのID
	*/
	std::wstring getTargetAccountID() const;

	/*!
	* @~english
	* @brief Sets the ID of the target account of this profile
	* @param target_account_id Target Account ID of this profile
	* @~japanese
	* @brief このプロフィールの対象アカウントのIDを設定します
	* @param target_account_id このプロフィールの対象アカウントのID
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
	* @brief アカウントの名を取得します
	* @return アカウントの名
	*/
	std::wstring getFirstName() const;

	/*!
	* @~english
	* @brief Sets the first name of the account
	* @param first_name First name of the account
	* @~japanese
	* @brief アカウントの名を設定します
	* @param first_name アカウントの名
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
	* @brief アカウントの姓を取得します
	* @return アカウントの姓
	*/
	std::wstring getLastName() const;

	/*!
	* @~english
	* @brief Sets the last name of the account
	* @param last_name Last name of the account
	* @~japanese
	* @brief アカウントの姓を設定します
	* @param last_name アカウントの姓
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
	* @brief アカウントのニックネームを取得します
	* @return アカウントのニックネーム
	*/
	std::wstring getNickname() const;

	/*!
	* @~english
	* @brief Sets the nickname of the account
	* @param nickname Nickname of the account
	* @~japanese
	* @brief アカウントのニックネームを設定します
	* @param nickname アカウントのニックネーム
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
	* @brief ニックネームの表示タイプを取得します
	* @return ニックネームの表示タイプ
	*/
	NicknameDisplayType getNicknameDisplayType() const;

	/*!
	* @~english
	* @brief Sets the display type of a nickname
	* @param nick_name_display_type Display type of a nickname
	* @~japanese
	* @brief ニックネームの表示タイプを設定します
	* @param nick_name_display_type ニックネームの表示タイプ
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
	* @brief アカウントのキャッチフレーズを取得します
	* @return アカウントのキャッチフレーズ
	*/
	std::wstring getTaglineMessage() const;

	/*!
	* @~english
	* @brief Sets the tagline of the account
	* @param tagline_message Tagline of the account
	* @~japanese
	* @brief アカウントのキャッチフレーズを設定します
	* @param tagline_message アカウントのキャッチフレーズ
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
	* @brief アカウントの紹介文を取得します
	* @return アカウントの紹介文
	*/
	std::wstring getIntroductionMessage() const;

	/*!
	* @~english
	* @brief Sets the message introduction of account
	* @param introduction_message Introduction of account message
	* @~japanese
	* @brief アカウントの紹介メッセージを設定します
	* @param introduction_message アカウントの紹介メッセージ
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
	* @brief 自慢できることを取得します
	* @return 自慢できること
	*/
	std::wstring getBraggingRights() const;

	/*!
	* @~english
	* @brief Sets the bragging rights
	* @param bragging_rights the bragging rights
	* @~japanese
	* @brief 自慢できることを設定します
	* @param bragging_rights 自慢できること
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
	* @brief 職業を取得します
	* @return 職業
	*/
	std::wstring getOccupation() const;

	/*!
	* @~english
	* @brief Sets the occupation
	* @param occupation The occupation
	* @~japanese
	* @brief 職業を設定します
	* @param occupation 職業
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
	* @brief 職歴を取得します
	* @return 職歴
	*/
	std::list<Employment> getEmployments() const;

	/*!
	* @~english
	* @brief Sets the employments
	* @param employments The employments
	* @~japanese
	* @brief 職歴を設定します
	* @param employments 職歴
	*/
	void setEmployments(const std::list<Employment>& employments);

	/*!
	* @~english
	* @brief Adds the employment
	* @param employment The employment
	* @~japanese
	* @brief 職歴を追加します
	* @param employment 職歴
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
	* @brief 学歴を取得します
	* @return 学歴
	*/
	std::list<Education> getEducations() const;

	/*!
	* @~english
	* @brief Sets the education
	* @param educations The education
	* @~japanese
	* @brief 学歴を設定します
	* @param educations 学歴
	*/
	void setEducations(const std::list<Education>& educations);

	/*!
	* @~english
	* @brief Adds the education
	* @param education The education
	* @~japanese
	* @brief 学歴を追加します
	* @param education 学歴
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
	* @brief 住んだことのある地域を取得します
	* @return 住んだことのある地域
	*/
	std::list<LivedPlace> getLivedPlaces() const;

	/*!
	* @~english
	* @brief Sets the areas that have lived
	* @param lived_places Areas that have lived
	* @~japanese
	* @brief 住んだことのある地域を設定します
	* @param lived_places 住んだことのある地域
	*/
	void setLivedPlaces(const std::list<LivedPlace>& lived_places);

	/*!
	* @~english
	* @brief Adds the areas that have lived
	* @param lived_place Areas that have lived
	* @~japanese
	* @brief 住んだことのある地域を追加します
	* @param lived_place 住んだことのある地域
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
	* @brief 連絡先(自宅)を取得します
	* @return 連絡先(自宅)
	*/
	std::list<ContactAddress> getHomeContactAddress() const;

	/*!
	* @~english
	* @brief Sets the (home) ContactAddresses
	* @param home_contact_addresses ContactAddresses(home)
	* @~japanese
	* @brief 連絡先(自宅)を設定します
	* @param home_contact_addresses 連絡先(自宅)
	*/
	void setHomeContactAddress(const std::list<ContactAddress>& home_contact_addresses);

	/*!
	* @~english
	* @brief Adds the (home) ContactAddress
	* @param home_contact_address ContactAddresses(home)
	* @~japanese
	* @brief 連絡先(自宅)を追加します
	* @param home_contact_address 連絡先(自宅)
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
	* @brief 連絡先(仕事)を取得します
	* @return 連絡先(仕事)
	*/
	std::list<ContactAddress> getWorkContactAddress() const;

	/*!
	* @~english
	* @brief Sets the (work) ContactAddresses
	* @param work_contact_addresses ContactAddresses(work)
	* @~japanese
	* @brief 連絡先(仕事)を設定します
	* @param work_contact_addresses 連絡先(仕事)
	*/
	void setWorkContactAddress(const std::list<ContactAddress>& work_contact_addresses);

	/*!
	* @~english
	* @brief Adds the (work) ContactAddress
	* @param work_contact_address ContactAddress(work)
	* @~japanese
	* @brief 連絡先(仕事)を追加します
	* @param work_contact_address 連絡先(仕事)
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
	* @brief パートナー関係を取得します
	* @return パートナー関係
	*/
	PartnershipType getPartnershipType() const;

	/*!
	* @~english
	* @brief Sets the partner relationship
	* @param partnership_type Partnership
	* @~japanese
	* @brief パートナー関係を設定します
	* @param partnership_type パートナー関係
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
	* @brief 広げたい関係を取得します
	* @return 広げたい関係
	*/
	RelationshipType getRelationshipType() const;

	/*!
	* @~english
	* @brief Set the relationship that you want expanded
	* @param relationship_type The relationship that you want expanded
	* @~japanese
	* @brief 広げたい関係を設定します
	* @param relationship_type 広げたい関係
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
	* @brief 性別を取得します
	* @return 性別
	*/
	Gender getGender() const;

	/*!
	* @~english
	* @brief Sets the gender
	* @param gender Gender
	* @~japanese
	* @brief 性別を設定します
	* @param gender 性別
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
	* @brief 他の名前を取得します
	* @return 他の名前
	*/
	std::list<std::wstring> getOtherNames() const;

	/*!
	* @~english
	* @brief Sets the name of the other
	* @param other_names Other name
	* @~japanese
	* @brief 他の名前を設定します
	* @param other_names 他の名前
	*/
	void setOtherNames(const std::list<std::wstring>& other_names);

	/*!
	* @~english
	* @brief Sets the name of the other
	* @param other_name Other name
	* @~japanese
	* @brief 他の名前を設定します
	* @param other_name 他の名前
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
	* @brief 他のプロフィールページを取得します
	* @return 他のプロフィールページ
	*/
	std::list<LabeledLink> getOtherProfilePages() const;

	/*!
	* @~english
	* @brief Set the other profile page
	* @param other_profile_pages Other profile page
	* @~japanese
	* @brief 他のプロフィールページを設定します
	* @param other_profile_pages 他のプロフィールページ
	*/
	void setOtherProfilePages(const std::list<LabeledLink>& other_profile_pages);

	/*!
	* @~english
	* @brief Add the other profile page
	* @param other_profile_page Other profile page
	* @~japanese
	* @brief 他のプロフィールページを追加します
	* @param other_profile_page 他のプロフィールページ
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
	* @brief 対象のアカウントの投稿が掲載されているページを取得します
	* @return 対象のアカウントの投稿が掲載されているページ
	*/
	std::list<LabeledLink> getYourPostPages() const;

	/*!
	* @~english
	* @brief Sets the target page account posts have been posted
	* @param your_post_pages Post subject page of the account have been posted
	* @~japanese
	* @brief 対象のアカウントの投稿が掲載されているページを設定します
	* @param your_post_pages 対象のアカウントの投稿が掲載されているページ
	*/
	void setYourPostPages(const std::list<LabeledLink>& your_post_pages);

	/*!
	* @~english
	* @brief Adds the target page account posts have been posted
	* @param your_post_page Post subject page of the account have been posted
	* @~japanese
	* @brief 対象のアカウントの投稿が掲載されているページを追加します
	* @param your_post_page 対象のアカウントの投稿が掲載されているページ
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
	* @brief おすすめのリンクのリストを取得します
	* @return おすすめのリンクのリスト
	*/
	std::list<LabeledLink> getRecommendedLinks() const;

	/*!
	* @~english
	* @brief Sets the list of links recommended
	* @param recommended_links A list of links recommended
	* @~japanese
	* @brief おすすめのリンクのリストを設定します
	* @param recommended_links おすすめのリンクのリスト
	*/
	void setRecommendedLinks(const std::list<LabeledLink>& recommended_links);

	/*!
	* @~english
	* @brief Adds the link recommendation
	* @param label Label attached to the link you want to add
	* @param url The Url of the link you want to add
	* @~japanese
	* @brief おすすめのリンクを追加します
	* @param label 追加したいリンクにつけるラベル
	* @param url 追加したいリンクのUrl
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