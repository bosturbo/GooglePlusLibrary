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

#include <string>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API GroupChat
{
public:
	GroupChat();

	void startEditing();

	void postMessage(const std::wstring& message);

	virtual ~GroupChat();
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite