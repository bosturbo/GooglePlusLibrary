#pragma once

#include <boost/detail/scoped_enum_emulation.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

BOOST_SCOPED_ENUM_START(PartnershipType)
{
	Private,
	Single,
	InRelationship,
	Engaged,
	Married,
	Iffy,
	InOpenRelationship,
	Widowed,
	InDomesticPartnership,
	InCivilUnion
}; BOOST_SCOPED_ENUM_END

}// namespace GooglePlusLibrary
}// namespace Gplusnasite