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

#include <string>

struct lua_State;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class GOOGLEPLUSLIBRARY_API StreamConnectionImpl
{
	friend class StreamConnection;
public:
	StreamConnectionImpl();

	void initialize(const std::wstring& account_id);
	void initializeAsync(const std::wstring& account_id);
	void waitInitializeAsync();

private:
	void initializeAsyncThreadMethod(const std::wstring& account_id);
	boost::thread initialize_thread_;

public:
	boost::signals2::signal<void()> onInitializeSucceed;
	boost::signals2::signal<void()> onInitializeFailed;

	void test();

public:
	void update(const std::wstring& account_id);
protected:
	static void chunkedContentReceieved(const std::string& account_id, const std::string& content);
	
private:
	boost::thread update_thread_;

public:
	void cancelUpdate();
	
	bool isCanceled();

public:
	int getConnectCount() const;
protected:
	void setConnectCount(int connect_count);
private:
	int connect_count_;

public:
	int getMaximumConnectCount() const;
protected:
	void setMaximumConnectCount(int maximum_connect_count);
private:
	int maximum_connect_count_;

public:
	static void bindToScript(lua_State* lua_state);

public:
	virtual ~StreamConnectionImpl();

private:
	bool is_cancellation_pending_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite