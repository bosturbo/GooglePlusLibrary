#include <Connection/WebClient/WebClient.hpp>
#include <Connection/HttpResponse.hpp>
#include <Connection/Cookie/Cookie.hpp>

#include <boost/bind.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/lexical_cast.hpp>

#include <iostream>
#include <fstream>
#include <algorithm>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace boost::asio::ssl;
using namespace boost::asio::ip;

#if defined DEBUG_WITH_HEXDUMP
static void hexdump(const char *buf, size_t len)
{
        //             xxxxxxx aa aa aa aa aa aa aa aa:aa aa aa aa aa aa aa aa|aaaaaaaaaaaaaaaa
        char line[] = "0000000                        :                       |                ";
        static const char hc[] = "0123456789abcdef";
        for (size_t i = 0; i < len; ++i) {
                int c = (unsigned char)buf[i];
                size_t offset = i % 16;
                if (offset == 0) {
                        if (i != 0)
                                puts(line);
                        sprintf(line, "%07x", (unsigned int)i);
                        memset(line + 7, ' ', sizeof line - 8);
                        line[31] = ':';
                        line[55] = '|';
                }
				char *p = line + 8 + offset * 3;
				p[0] = hc[(c >> 4) & 0xfU];
				p[1] = hc[c & 0xfU];
                line[56 + offset] = isprint(c) ? c : ' ';
        }
        puts(line);
}
#endif //DEBUG_WITH_HEXDUMP

void WebClient::handleConnectTimeout(const boost_error_code& error)
{
	if(error)
	{
		cout << "Error: " << error.message() << endl;
		return;
	}
	socket_.lowest_layer().close();
	io_service_.stop();
}

void WebClient::handleResolve(const boost_error_code& error, asio_resolver::iterator endpoint_iterator)
{
	if(error)
	{
		cout << "Error: " << error.message() << endl;
		return;
	}
	startConnect(endpoint_iterator);
}

void WebClient::startConnect(tcp::resolver::iterator endpoint_iterator)
{
	if (endpoint_iterator != tcp::resolver::iterator())
	{
		connect_timer_.expires_from_now(boost::posix_time::seconds(60));

		socket_.lowest_layer().async_connect(endpoint_iterator->endpoint(),
			boost::bind(&WebClient::handleConnect,
			this, boost::asio::placeholders::error, endpoint_iterator));
	}
	else
	{
		cancelConnect();
	}
}

void WebClient::handleConnect(const boost_error_code& error, tcp::resolver::iterator endpoint_iterator)
{
	if(is_cancellation_pending_)
	{
		cancelConnect();
		return;
	}

	if (endpoint_iterator != tcp::resolver::iterator())
	{
		if (!socket_.lowest_layer().is_open())
		{
			cout << "Connect timed out" << endl;
			startConnect(++endpoint_iterator);
		}
		else if(error)
		{
			cout << "Connect error: " << error.message() << endl;

			socket_.lowest_layer().close();
			startConnect(++endpoint_iterator);
		}
		else
		{
			socket_.async_handshake(stream_base::client, 
				boost::bind(&WebClient::handleHandshake, this, 
				boost::asio::placeholders::error));
		}
	}
	else
	{
		cancelConnect();
		return;
	}
}

string WebClient::setRequestStream()
{
	stringstream request_stream;

	cout << "method: " << method_ << ", path: " << path_ << endl; //XXX
	request_stream << method_ << " " << path_ << " HTTP/1.1\r\n";

	auto request_header_it = request_headers_.cbegin();
	while(request_header_it != request_headers_.cend())
	{
		request_stream << request_header_it->first << ": " << request_header_it->second << "\r\n";
		++request_header_it;
	}

	string cookie_parameter("");
	bool first = true;
	auto it = request_cookies_.cbegin();
	while(it != request_cookies_.cend())
	{
		if(first == true)
		{
			first = false;
		}
		else
		{
			cookie_parameter += ";";
		}

		Cookie cookie = (*it);
		cookie_parameter += (cookie.getName() + "=" + cookie.getValue());
		//cout << "Request Cookie:" << cookie.getName() << "=" << cookie.getValue() << endl;
		++it;
	}
	
	if(!cookie_parameter.empty())
	{
		request_stream << "Cookie: " << cookie_parameter << "\r\n";
	}

	if(content_.size() > 0)
	{
		request_stream << "Content-Type: " << content_type_ << "\r\n";
		request_stream << "Content-Length: " << content_.size() << "\r\n";
	}
	
	request_stream << "\r\n";

	if(content_.size() > 0)
	{
		request_stream << content_;
	}
	return request_stream.str();
}

void WebClient::handleHandshake(const boost_error_code& error)
{
	boost::asio::async_read_until(socket_, response_, "\r\n", 
		boost::bind(&WebClient::handleReadStatusLine, this, boost::asio::placeholders::error));

	startWrite();
}

void WebClient::startWrite()
{
	if (is_cancellation_pending_)
	{
		return;
	}

	boost::asio::async_write(socket_, 
		boost::asio::buffer(request_.c_str(), strlen(request_.c_str())), 
		boost::bind(&WebClient::handleWrite, this, boost::asio::placeholders::error));		
}

void WebClient::handleWrite(const boost_error_code& error)
{
	if (is_cancellation_pending_)
	{
		return;
	}

	if (error)
	{
		cout << "Error on heartbeat: " << error.message() << endl;
		cancelConnect();
		return;
	}
}

void WebClient::handleReadStatusLine(const boost_error_code& error)
{
	if (is_cancellation_pending_)
	{
		return;
	}

	if (error)
	{
		cout << "Error: " << error.message() << endl;
		cancelConnect();
		return;
	}
	istream response_stream(&response_);
	string http_version;
	response_stream >> http_version;

	response_stream >> status_code_;
	string status_message;
	getline(response_stream, status_message);

	if (!response_stream || http_version.substr(0, 5) != "HTTP/")
	{
		cout << "Invalid response";
		return;
	}

	boost::asio::async_read_until(socket_, response_, "\r\n\r\n", 
		boost::bind(&WebClient::handleReadHeaders, this, 
		boost::asio::placeholders::error));
}

void WebClient::handleReadHeaders(const boost_error_code& error)
{
	if (error)
	{
		cout << "Error: " << error.message() << endl;
		cancelConnect();
		return;
	}
	istream response_stream(&response_);

	string header;

	list<Cookie> cookies;

	response_headers_.clear();
	response_cookies_.clear();

	string line = string(boost::asio::buffer_cast<const char*>(response_.data()), response_.size());

	while (getline(response_stream, header) && header != "\r")
	{
		int position = header.find(":");
		if(position <= 0)
		{
			continue;
		}
		// "name":"value"
		string name = header.substr(0, position);
		string value = header.substr(position + 2);

		boost::algorithm::trim(name);
		boost::algorithm::trim(value);

		if(name == "Set-Cookie")
		{
			Cookie cookie(url_, value);
			cookies.push_back(cookie);
		}
		response_headers_.insert(make_pair(name, value));
cout << "header:" << name << "=" << value << endl; //XXX
		//cout << "header:" << name << "=" << value << endl;
	}

	response_cookies_ = cookies;

	if(getResponseHeaderValue("Transfer-Encoding") == "chunked")
	{
		startReadChunkedContent();
	}
	else
	{
		//cout << "Chunked ContentˆÈŠO" << endl;
		string length = getResponseHeaderValue("Content-Length");

		if(!length.empty())
		{
			size_t size = boost::lexical_cast<size_t>(length);
			boost::asio::async_read(socket_, response_,
				boost::asio::transfer_exactly(size - response_.size()),
				boost::bind(&WebClient::handleReadContent, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred)
				);
		}
		else
		{
			boost::asio::async_read(socket_, response_,
				boost::asio::transfer_all(),
				boost::bind(&WebClient::handleReadContent, this,
				boost::asio::placeholders::error, 
				boost::asio::placeholders::bytes_transferred));
		}
	}
}

void WebClient::startReadChunkedContent()
{
	boost::asio::async_read_until(socket_, response_, "\r\n",
		boost::bind(&WebClient::handleReadChunkSize, this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));

}

static size_t hex2size_t(const std::string str)
{
	size_t size = 0;
	for (const char *p = str.c_str(); *p; ++p) {
		switch (*p) {
		// case '0': break; // nothing to do
		case '1':
			size += 1;
			break;
		case '2':
			size += 2;
			break;
		case '3':
			size += 3;
			break;
		case '4':
			size += 4;
			break;
		case '5':
			size += 5;
			break;
		case '6':
			size += 6;
			break;
		case '7':
			size += 7;
			break;
		case '8':
			size += 8;
			break;
		case '9':
			size += 9;
			break;
		case 'A':
		case 'a':
			size += 10;
			break;
		case 'B':
		case 'b':
			size += 11;
			break;
		case 'C':
		case 'c':
			size += 12;
			break;
		case 'D':
		case 'd':
			size += 13;
			break;
		case 'E':
		case 'e':
			size += 14;
			break;
		case 'F':
		case 'f':
			size += 15;
			break;
		default:
			// nothing to do
			break;
		}
		if ('\0' == p[1])
			break;
		size <<= 4;
	}

	return size;
}

void WebClient::handleReadChunkSize(const boost_error_code& error, size_t bytes_transferred)
{
	if (is_cancellation_pending_)
		return;
#if defined DEBUG_WITH_HEXDUMP
hexdump(boost::asio::buffer_cast<const char*>(response_.data()),
	bytes_transferred);
#endif /* DEBUG_WITH_HEXDUMP */

	if (error) {
		cout << "error on receive: " << error.message() << endl;
		cancelConnect();
		return;
	}

	std::string response(boost::asio::buffer_cast<const char*>(response_.data()), response_.size());
	std::string eol("\r\n");
	std::size_t pos_eol = response.find(eol);
	if (std::string::npos == pos_eol) {
		cout << " error on receive: bad chunk format." << endl;
		cancelConnect();
		return;
	}
	std::size_t line_length = pos_eol + eol.size();

	string chunk_size_line(boost::asio::buffer_cast<const char*>(response_.data()), line_length);
	response_.consume(line_length);
	chunk_size_line.resize(chunk_size_line.length() - 2 /* drop "\r\n" */);
	if (0 == chunk_size_line.length()) {
		// no more chunk.
		cancelConnect();
	}
	size_t chunk_size = hex2size_t(chunk_size_line);
	if (0 == chunk_size) {
		// wait next chunk.
		startReadChunkedContent();
		return;
	}

	chunk_size += 2; // for trailing CRLF
	chunk_remain_  = chunk_size;

	std::size_t size_to_need = 0;
	if (response_.size() < chunk_size)
		size_to_need = chunk_size - response_.size();

	boost::asio::async_read(socket_,
		response_,
		boost::asio::transfer_exactly(size_to_need),
		boost::bind(&WebClient::handleReadChunkData, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void WebClient::handleReadChunkData(const boost_error_code& error, size_t bytes_transferred)
{
	if (is_cancellation_pending_)
		return;
#if defined DEBUG_WITH_HEXDUMP
hexdump(boost::asio::buffer_cast<const char*>(response_.data()),
	response_.size());
#endif /* DEBUG_WITH_HEXDUMP */

	if (error) {
		cout << "error on receive: " << error.message() << endl;
		cancelConnect();
	}

	std::size_t eat_size = std::min(chunk_remain_, response_.size());
	response_body_.append(
		boost::asio::buffer_cast<const char*>(response_.data()),
		// response_.size() - 2 /* drop trailing "\r\n" */);
		eat_size);
	response_.consume(eat_size);
	chunk_remain_ -= eat_size;

	if (chunk_remain_ > 0) {
		boost::asio::async_read(socket_,
			response_,
			boost::asio::transfer_exactly(chunk_remain_),
			boost::bind(&WebClient::handleReadChunkData, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		return;
	}

	response_body_.resize(response_body_.size() - 2 /* drop trailing "\r\n" */);

	if (response_.size() > 0) {
		boost::asio::async_read(socket_, response_,
			boost::asio::transfer_exactly(0),
			boost::bind(&WebClient::handleReadChunkSize, this,
			boost::asio::placeholders::error, 
			boost::asio::placeholders::bytes_transferred));
		return;
	}

	// will be trying to read some chunks remaining.
	startReadChunkedContent();
}

void WebClient::handleReadContent(const boost_error_code& error, size_t bytes_transferred)
{
	if (error)
	{
		if(error != boost::asio::error::eof)
		{
			cout << "Error: " << error.message() << endl;
		}
	}
	else
	{
		response_body_ = string(boost::asio::buffer_cast<const char*>(response_.data()), bytes_transferred);
		response_.consume(bytes_transferred);
	}
	
	cancelConnect();
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite