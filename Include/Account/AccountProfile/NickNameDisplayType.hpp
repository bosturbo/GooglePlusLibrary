#pragma once

#include <boost/detail/scoped_enum_emulation.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

BOOST_SCOPED_ENUM_START(NicknameDisplayType)
{
	None,
	WithQuotationMarks,
	WithParentheses
}; BOOST_SCOPED_ENUM_END

}// namespace GooglePlusLibrary
}// namespace Gplusnasite