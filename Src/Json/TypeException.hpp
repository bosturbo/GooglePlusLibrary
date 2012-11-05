#pragma once

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class TypeException : public std::exception
{
public:
	const char* what() const throw()
	{
		return "invalid ObjectType";
	}
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite