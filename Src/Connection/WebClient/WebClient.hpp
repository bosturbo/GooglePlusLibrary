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

//#define BOOST_ASIO_ENABLE_HANDLER_TRACKING

#include <string>
#include <map>

#include <boost/asio.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <iosfwd>

typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> asio_ssl_stream;
typedef boost::asio::streambuf asio_streambuf;
typedef boost::system::error_code boost_error_code;
typedef boost::asio::ip::tcp::resolver asio_resolver;

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

class Cookie;
class HttpResponse;

class GOOGLEPLUSLIBRARY_API WebClient
{
public:
	WebClient(const std::string& url);

	void setCurrentMailAddress(const std::string& mail_address);
	void setCurrentAccountID(const std::string& account_id);
private:
	std::string current_mail_address_;
	std::string current_account_id_;

public:
	HttpResponse get();
	HttpResponse post(const std::string& parameter);
	HttpResponse put(std::ifstream& file_stream);

	void setRequestCookies();
	void setResponseCookies();

	void setMethod(const std::string& method);

	std::string getMethod() const;

	void setUserAgent(const std::string& user_agent);

	std::string getUserAgent() const;

	void setContentType(const std::string& content_type);

	std::string getContentType() const;

	void addHeader(const std::string& name, const std::string& value);
	void addHeader(const std::map<std::string, std::string>& name_value_pairs);

	std::string escapeString(std::string source_text);
	std::string escapeParameter(const std::map<std::string, std::string>& post_parameter);

	void addRequestCookie(const Cookie& cookie);

	void setRequestCookies(const std::list<Cookie>& cookies);

	std::list<Cookie> getResponseCookies() const;
	
	void setContent(const std::map<std::string, std::string>& parameter_pairs);

	void setContent(const std::string& parameter);

	void setContent(std::ifstream& file_stream);

	void setTimeOut(boost::posix_time::seconds time);

	void sendRequest();

	int getStatusCode();
private:
	int status_code_;

public:
	std::map<std::string, std::string> getResponseHeader() const;

	std::string getResponseHeaderValue(const std::string& name) const;

	std::string getResponseBody() const;

	void cancelConnect();

	~WebClient();

protected:

	std::string setRequestStream();
	
	void checkDeadLine();

	void handleConnectTimeout(const boost_error_code& error);

	void handleResolve(const boost_error_code& error, boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

	void startConnect(boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

	void handleConnect(const boost_error_code& error, boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

	void handleHandshake(const boost_error_code& error);

	void startWrite();

	void handleWrite(const boost_error_code& error);

	void handleReadStatusLine(const boost_error_code& error);

	void handleReadHeaders(const boost_error_code& error);

	void handleReadContent(const boost_error_code& error, size_t bytes_transferred);

	void startReadChunkedContent();
	void handleReadChunkSize(const boost_error_code& error, size_t bytes_transferred);
	void handleReadChunkData(const boost_error_code& error, size_t bytes_transferred);
private:
	std::shared_ptr<boost::asio::io_service> io_service_ptr_;
	boost::asio::io_service& io_service_;
	boost::asio::ssl::context ssl_context_;
	asio_ssl_stream socket_;
	asio_resolver resolver_;
	asio_streambuf response_;
	boost::asio::deadline_timer connect_timer_;
	boost::asio::deadline_timer heartbeat_timer_;

	boost::posix_time::seconds time_out_;

	std::string method_;
	std::map<std::string, std::string> response_headers_;
	std::size_t chunk_remain_;
	std::string response_body_;
	std::string url_;
	std::string path_;
	std::string request_;

	//size_t content_length_;
	std::string content_;
	std::string content_type_;

	std::map<std::string, std::string> request_headers_;
	std::list<Cookie> request_cookies_;
	std::list<Cookie> response_cookies_;
	int read_size_;
	int read_end_size_;

	enum ReadMode
	{
		ReadChunkSize,
		ReadEndSize,
		ReadChunkedContent
	};
	ReadMode read_mode_;

	bool is_cancellation_pending_;
};

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
