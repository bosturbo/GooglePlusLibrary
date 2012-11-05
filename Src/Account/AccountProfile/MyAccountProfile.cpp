#include <Account/AccountProfile/MyAccountProfile.hpp>
#include <Thread/ReadWriteMutex.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

MyAccountProfile::MyAccountProfile()
:target_account_id_(L""),
first_name_(L""),
last_name_(L""),
nickname_(L""),
nick_name_display_type_(NicknameDisplayType::None),
tagline_message_(L""),
introduction_message_(L""),
bragging_rights_(L""),
occupation_(L""),
employments_(),
educations_(),
lived_places_(),
home_contact_addresses_(),
work_contact_addresses_(),
partnership_type_(PartnershipType::Private),
relationship_type_(),
gender_(Gender::Male),
other_names_(),
other_profile_pages_(),
your_post_pages_(),
recommended_links_(),
read_write_mutex_(make_shared<ReadWriteMutex>())
{
}

wstring MyAccountProfile::getTargetAccountID() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return target_account_id_;
}

void MyAccountProfile::setTargetAccountID(const wstring& target_account_id)
{
	ScopedWriteLock lock(*read_write_mutex_);
	target_account_id_ = target_account_id;
}

wstring MyAccountProfile::getFirstName() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return first_name_;
}

void MyAccountProfile::setFirstName(const wstring& first_name)
{
	ScopedWriteLock lock(*read_write_mutex_);
	first_name_ = first_name;
}

wstring MyAccountProfile::getLastName() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return last_name_;
}

void MyAccountProfile::setLastName(const wstring& last_name)
{
	ScopedWriteLock lock(*read_write_mutex_);
	last_name_ = last_name;
}

wstring MyAccountProfile::getNickname() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return nickname_;
}

void MyAccountProfile::setNickname(const wstring& nickname)
{
	ScopedWriteLock lock(*read_write_mutex_);
	nickname_ = nickname;
}

NicknameDisplayType MyAccountProfile::getNicknameDisplayType() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return nick_name_display_type_;
}

void MyAccountProfile::setNicknameDisplayType(const NicknameDisplayType& nick_name_display_type)
{
	ScopedWriteLock lock(*read_write_mutex_);
	nick_name_display_type_ = nick_name_display_type;
}

wstring MyAccountProfile::getTaglineMessage() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return tagline_message_;
}

void MyAccountProfile::setTaglineMessage(const wstring& tagline_message)
{
	ScopedWriteLock lock(*read_write_mutex_);
	tagline_message_ = tagline_message;
}

wstring MyAccountProfile::getIntroductionMessage() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return introduction_message_;
}

void MyAccountProfile::setIntroductionMessage(const wstring& introduction_message)
{
	ScopedWriteLock lock(*read_write_mutex_);
	introduction_message_ = introduction_message;
}

wstring MyAccountProfile::getBraggingRights() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return bragging_rights_;
}

void MyAccountProfile::setBraggingRights(const wstring& bragging_rights)
{
	ScopedWriteLock lock(*read_write_mutex_);
	bragging_rights_ = bragging_rights;
}

wstring MyAccountProfile::getOccupation() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return occupation_;
}

void MyAccountProfile::setOccupation(const wstring& occupation)
{
	ScopedWriteLock lock(*read_write_mutex_);
	occupation_ = occupation;
}

list<Employment> MyAccountProfile::getEmployments() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return employments_;
}

void MyAccountProfile::setEmployments(const list<Employment>& employments)
{
	ScopedWriteLock lock(*read_write_mutex_);
	employments_ = employments;
}

void MyAccountProfile::addEmployments(const Employment& employment)
{
	ScopedWriteLock lock(*read_write_mutex_);
	employments_.push_back(employment);
}

list<Education> MyAccountProfile::getEducations() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return educations_;
}

void MyAccountProfile::setEducations(const list<Education>& educations)
{
	ScopedWriteLock lock(*read_write_mutex_);
	educations_ = educations;
}

void MyAccountProfile::addEducation(const Education& education)
{
	ScopedWriteLock lock(*read_write_mutex_);
	educations_.push_back(education);
}

list<LivedPlace> MyAccountProfile::getLivedPlaces() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return lived_places_;
}

void MyAccountProfile::setLivedPlaces(const list<LivedPlace>& lived_places)
{
	ScopedWriteLock lock(*read_write_mutex_);
	lived_places_ = lived_places;
}

void MyAccountProfile::addLivedPlaces(const LivedPlace& lived_place)
{
	ScopedWriteLock lock(*read_write_mutex_);
	if(lived_place.isCurrent())
	{
		// change current city
		auto it = lived_places_.begin();
		while(it != lived_places_.end())
		{
			(*it).setIsCurrent(false);
			++it;
		}
	}
	lived_places_.push_back(lived_place);
}

list<ContactAddress> MyAccountProfile::getHomeContactAddress() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return home_contact_addresses_;
}

void MyAccountProfile::setHomeContactAddress(const list<ContactAddress>& home_contact_addresses)
{
	ScopedWriteLock lock(*read_write_mutex_);
	home_contact_addresses_ = home_contact_addresses;
}

void MyAccountProfile::addHomeContactAddress(const ContactAddress& home_contact_address)
{
	ScopedWriteLock lock(*read_write_mutex_);
	home_contact_addresses_.push_back(home_contact_address);
}

list<ContactAddress> MyAccountProfile::getWorkContactAddress() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return work_contact_addresses_;
}

void MyAccountProfile::setWorkContactAddress(const list<ContactAddress>& work_contact_addresses)
{
	ScopedWriteLock lock(*read_write_mutex_);
	work_contact_addresses_ = work_contact_addresses;
}

void MyAccountProfile::addWorkContactAddress(const ContactAddress& work_contact_address)
{
	ScopedWriteLock lock(*read_write_mutex_);
	work_contact_addresses_.push_back(work_contact_address);
}

PartnershipType MyAccountProfile::getPartnershipType() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return partnership_type_;
}

void MyAccountProfile::setPartnershipType(const PartnershipType& partnership_type)
{
	ScopedWriteLock lock(*read_write_mutex_);
	partnership_type_ = partnership_type;
}

RelationshipType MyAccountProfile::getRelationshipType() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return relationship_type_;
}

void MyAccountProfile::setRelationshipType(const RelationshipType& relationship_type)
{
	ScopedWriteLock lock(*read_write_mutex_);
	relationship_type_ = relationship_type;
}

Gender MyAccountProfile::getGender() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return gender_;
}

void MyAccountProfile::setGender(const Gender& gender)
{
	ScopedWriteLock lock(*read_write_mutex_);
	gender_ = gender;
}

list<wstring> MyAccountProfile::getOtherNames() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return other_names_;
}

void MyAccountProfile::setOtherNames(const list<wstring>& other_names)
{
	ScopedWriteLock lock(*read_write_mutex_);
	other_names_ = other_names;
}

void MyAccountProfile::addOtherNames(const wstring& other_name)
{
	ScopedWriteLock lock(*read_write_mutex_);
	other_names_.push_back(other_name);
}

list<LabeledLink> MyAccountProfile::getOtherProfilePages() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return other_profile_pages_;
}

void MyAccountProfile::setOtherProfilePages(const list<LabeledLink>& other_profile_pages)
{
	ScopedWriteLock lock(*read_write_mutex_);
	other_profile_pages_ = other_profile_pages;
}

void MyAccountProfile::addOtherProfilePages(const LabeledLink& other_profile_page)
{
	ScopedWriteLock lock(*read_write_mutex_);
	other_profile_pages_.push_back(other_profile_page);
}

list<LabeledLink> MyAccountProfile::getYourPostPages() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return your_post_pages_;
}

void MyAccountProfile::setYourPostPages(const list<LabeledLink>& your_post_pages)
{
	ScopedWriteLock lock(*read_write_mutex_);
	your_post_pages_ = your_post_pages;
}

void MyAccountProfile::addYourPostPages(const LabeledLink& your_post_page)
{
	ScopedWriteLock lock(*read_write_mutex_);
	your_post_pages_.push_back(your_post_page);
}

list<LabeledLink> MyAccountProfile::getRecommendedLinks() const
{
	ScopedReadLock lock(*read_write_mutex_);
	return recommended_links_;
}

void MyAccountProfile::setRecommendedLinks(const list<LabeledLink>& recommended_links)
{
	ScopedWriteLock lock(*read_write_mutex_);
	recommended_links_ = recommended_links;
}

void MyAccountProfile::addRecommendedLinks(const wstring& label, const wstring& url)
{
	if(label.empty())
	{
		return;
	}
	if(url.empty())
	{
		return;
	}

	LabeledLink recommended_link(label, url);
	ScopedWriteLock lock(*read_write_mutex_);
	recommended_links_.push_back(recommended_link);
}

MyAccountProfile::~MyAccountProfile()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite