#include <Connection/WebClient/WebClient.hpp>
#include <Connection/HttpResponse.hpp>
#include <Connection/Cookie/Cookie.hpp>

#include <boost/bind.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/regex.hpp>

#include <iostream>
#include <fstream>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace boost::asio::ssl;
using namespace boost::asio::ip;
namespace qi = boost::spirit::qi;
namespace phoenix = boost::phoenix;

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
	connect_timer_.async_wait(boost::bind(&WebClient::checkDeadLine, this));
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

stringstream WebClient::setRequestStream()
{
	stringstream request_stream;

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
	return request_stream;
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
		boost::asio::buffer(request_stream_.str().c_str(), strlen(request_stream_.str().c_str())), 
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
	heartbeat_timer_.expires_from_now(boost::posix_time::seconds(10));
	heartbeat_timer_.async_wait(boost::bind(&WebClient::startWrite, this));
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
				boost::asio::transfer_exactly(size),
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
	//cout << "LoadHandleReadChunkSize" << endl;

	connect_timer_.expires_from_now(boost::posix_time::seconds(30));
	/*
	boost::asio::async_read_until(socket_, response_, "\n",
		boost::bind(&WebClient::handleReadChunkSize, this, 
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
			*/
	
	boost::asio::async_read_until(socket_, response_, "\n",
		boost::bind(&WebClient::handleReadChunkedContent, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));

}

void WebClient::handleReadChunkSize(const boost_error_code& error, size_t bytes_transferred)
{
	cout << "HandleReadChunkSize" << endl;

	if (is_cancellation_pending_)
	{
		cancelConnect();
		return;
	}

	if (error)
	{
		cout << "Error on receive: " << error.message() << endl;
		cancelConnect();
		return;
	}

	string line = string(boost::asio::buffer_cast<const char*>(response_.data()), bytes_transferred);
	response_.consume(bytes_transferred);

	size_t size = -1;

	if(qi::parse(line.cbegin(), line.cend(), qi::hex[phoenix::ref(size) = qi::_1] >> (qi::lit("\r\n") | qi::lit("\n"))))
	{
		if(size == 0)
		{
			cancelConnect();
		}
		else
		{
			cout << "LoadHandleReadChunkedContent" << endl;
			cout << "Chunk Size:" <<size << endl;

			boost::asio::async_read(socket_, response_, 
				boost::asio::transfer_exactly(size),
				boost::bind(&WebClient::handleReadChunkedContent3, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}
	}
	else
	{
		cancelConnect();
	}
}

void WebClient::handleReadChunkSize2(const boost_error_code& error, size_t bytes_transferred)
{
	//cout << "HandleReadChunkSize" << endl;

	if (is_cancellation_pending_)
	{
		return;
	}

	if (error)
	{
		cout << "Error on receive: " << error.message() << endl;
		cancelConnect();
		return;
	}
	
	string line = string(boost::asio::buffer_cast<const char*>(response_.data()), bytes_transferred);
	response_.consume(bytes_transferred);
	if(line.find("0\r\n") >= 0)
	{
		int a = 3;
	}
	int size = -1;

	if(qi::parse(line.cbegin(), line.cend(), qi::hex[phoenix::ref(size) = qi::_1] >> (qi::lit("\r\n") | qi::lit("\n"))))
	{
		if(size == 0)
		{
			cout << "handleReadChunkSize2 size == 0----------------------------------------------------------------" << endl;
			cancelConnect();
			return;
		}
		read_size_ = size;
		//read_mode_ = ReadEndSize;
		read_mode_ = ReadChunkedContent;
		startReadChunkedContent();
	}
	else
	{
		cout << "handleReadChunkSize2 parse failed----------------------------------------------------------------" << endl;
		cancelConnect();
		return;
	}
	
}

void WebClient::handleReadEndSize(const boost_error_code& error, size_t bytes_transferred)
{
	//cout << "HandleReadEndSize" << endl;

	if (is_cancellation_pending_)
	{
		return;
	}

	if (error)
	{
		cout << "Error on receive: " << error.message() << endl;
		cancelConnect();
		return;
	}

	string line = string(boost::asio::buffer_cast<const char*>(response_.data()), bytes_transferred);
	response_.consume(bytes_transferred);
	if(line.find("0\r\n") >= 0)
	{
		int a = 3;
	}
	read_size_ -= bytes_transferred;

	int end_size = -1;
	/*
	if(qi::parse(line.cbegin(), line.cend(), qi::hex[phoenix::ref(end_size) = qi::_1] >> (qi::lit("\r\n") | qi::lit("\n"))))
	{
		if(end_size > 0)
		{
			read_end_size_ = end_size;
		}
		else
		{
			response_body_ += line;
		}
	}
	else
	{
		response_body_ += line;
	}
	*/
	response_body_ += line;

	read_mode_ = ReadChunkedContent;
	startReadChunkedContent();
}

void WebClient::handleReadEndLine(const boost_error_code& error, size_t bytes_transferred)
{
	cout << "HandleReadChunkSize" << endl;
	string raw_line = string(boost::asio::buffer_cast<const char*>(response_.data()), bytes_transferred);
	if(raw_line != "\r\n")
	{
		cout << "End Line:" << raw_line << endl;
	}
	response_.consume(bytes_transferred);
	/*
	int size = response_.size();
	if(size == 0)
	{
		cancelConnect();
		return;
	}
	*/
	startReadChunkedContent();
}

void WebClient::handleReadChunkedContent2(const boost_error_code& error, size_t bytes_transferred)
{
	if (is_cancellation_pending_)
		return;

	if (!error)
	{
		string line("");
		/*
		istream is(&response_);

		if(!(getline(is, line) && line != "\r"))
		{
			//cout << "-------------------------------------------------------------------" << endl;
			cancelConnect();
			return;
		}
		*/
		string aa = string(boost::asio::buffer_cast<const char*>(response_.data()), response_.size());
		line = string(boost::asio::buffer_cast<const char*>(response_.data()), bytes_transferred);
		int position = line.find("\n");
		if(position < 0)
		{
			cout << "1-------------------------------------------------------------------" << endl;
			cancelConnect();
			return;
		}
		
		line = line.substr(0, position + 1);
		response_.consume(line.size());
		/*
		int size = response_.size();
		if(size <= 0)
		{
			//cout << "response_.size() = 0" << endl;
			cancelConnect();
			return;
		}
		*/
		if((response_.size() <= 0) && (line == "\r\n"))
		{
			cout << "2-------------------------------------------------------------------" << endl;
			cancelConnect();
			return;
		}
		
		if(!qi::parse(line.cbegin(), line.cend(), qi::hex >> (qi::lit("\r\n") | qi::lit("\n"))))
		{
			// line is chunk size
			response_body_ += line;
		}
		/*
		boost::regex regex("([0-9a-zA-Z]+)\\r\\n");
		boost::smatch smatch;

		if(boost::regex_search(line, smatch, regex))
		{
			int position = smatch.position();
			if(smatch.position() != 0)
			{
				response_body_ += line;
			}
			else
			{
				int a = 3;
			}
		}
		else
		{
			response_body_ += line;
		}
		*/
		startReadChunkedContent();
	}
	else
	{
		cout << "Error on receive: " << error.message() << L"\n";
		cancelConnect();
	}
}

void WebClient::handleReadChunkedContent(const boost_error_code& error, size_t bytes_transferred)
{
	if (is_cancellation_pending_)
		return;

	if (!error)
	{
		string line("");
		string aa = string(boost::asio::buffer_cast<const char*>(response_.data()), response_.size());
		line = string(boost::asio::buffer_cast<const char*>(response_.data()), bytes_transferred);
		response_.consume(bytes_transferred);

		if(line == "\r\n")
		{
			cancelConnect();
			return;
		}
		/*
		if((response_.size() <= 0) && (line == "\r\n"))
		{
			cancelConnect();
			return;
		}
		*/
		/*
		if(!qi::parse(line.cbegin(), line.cend(), qi::hex >> (qi::lit("\r\n") | qi::lit("\n"))))
		{
			// line is chunk size
			response_body_ += line;
		}
		*/

		boost::regex regex("([0-9a-zA-Z]+)\\r\\n");
		boost::smatch smatch;

		if(boost::regex_search(line, smatch, regex))
		{
			if(smatch.position() != 0)
			{
				response_body_ += line;
			}
		}
		else
		{
			response_body_ += line;
		}

		startReadChunkedContent();
		/*
		boost::asio::async_read_until(socket_, response_, "\n", 
			boost::bind(&WebClient::handleReadEndLine, this, 
			_1, _2));
			*/
	}
	else
	{
		cout << "Error on receive: " << error.message() << L"\n";
		cancelConnect();
	}
}

void WebClient::handleReadChunkedContent3(const boost_error_code& error, size_t bytes_transferred)
{
	if (is_cancellation_pending_)
	{
		cancelConnect();
		return;
	}

	if (!error)
	{
		string line("");
		string aa = string(boost::asio::buffer_cast<const char*>(response_.data()), response_.size());
		line = string(boost::asio::buffer_cast<const char*>(response_.data()), bytes_transferred);
		response_.consume(bytes_transferred);

		if(line == "\r\n")
		{
			cancelConnect();
			return;
		}
		/*
		if((response_.size() <= 0) && (line == "\r\n"))
		{
			cancelConnect();
			return;
		}
		*/
		
		if(qi::parse(line.cbegin(), line.cend(), qi::hex >> (qi::lit("\r\n") | qi::lit("\n")) >> qi::as_string[*qi::char_][phoenix::ref(response_body_) += qi::_1]))
		{
			// stream response
			cancelConnect();
			return;
		}
		else
		{
			response_body_ += line;
		}
		
		/*
		boost::regex regex("([0-9a-zA-Z]+)\\r\\n");
		boost::smatch smatch;

		if(boost::regex_search(line, smatch, regex))
		{
			if(smatch.position() != 0)
			{
				response_body_ += line;
			}
		}
		else
		{
			response_body_ += line;
		}
		*/
		//startReadChunkedContent();
		
		boost::asio::async_read_until(socket_, response_, "\n", 
			boost::bind(&WebClient::handleReadEndLine, this, 
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}
	else
	{
		cout << "Error on receive: " << error.message() << L"\n";
		cancelConnect();
	}
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