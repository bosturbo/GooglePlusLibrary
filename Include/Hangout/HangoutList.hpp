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

#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API HangoutList
{
public:
	HangoutList();

	std::wstring getAccountID() const;

	void setAccountID(const std::wstring& my_account_id);
private:
	std::wstring my_account_id_;
public:
	void create();

	void update();

	virtual ~HangoutList();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite