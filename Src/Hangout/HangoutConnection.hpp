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
#include <boost/thread.hpp>

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API HangoutConnection
{
public:
	HangoutConnection();

	void initialize(const std::wstring& account_id);

	void initializeAsync(const std::wstring& account_id);

	void waitInitializeAsync();

private:

	void initializeAsyncThreadMethod(const std::wstring& account_id);
	boost::thread initialize_thread_;

public:

	void update(const std::wstring& account_id);
private:
	boost::thread update_thread_;

public:
	static void bindToScript(lua_State* lua_state);

public:
	virtual ~HangoutConnection();

private:
	bool is_cancellation_pending_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite