#include <Connection/Cookie/Cookie.hpp>

#include <Connection/Uri.hpp>

#include <boost/date_time/local_time/local_time.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;
using namespace boost::local_time;

Cookie::Cookie()
:name_(""), value_(""), path_(""), domain_(""), is_expired_(false), is_secure_(false), is_http_only_(false), 
raw_information_(""), expire_posix_time_(), raw_expire_time_("")
{
	expire_posix_time_ = boost::posix_time::time_from_string("1970-01-01 0:0:0");
}

Cookie::Cookie(const string& url, const string& raw_information)
:name_(""), value_(""), path_(""), domain_(""), is_expired_(false), is_secure_(false), is_http_only_(false), raw_information_(raw_information)
{
	namespace qi = boost::spirit::qi;
	namespace phoenix = boost::phoenix;

	raw_information_ = raw_information;

	string::const_iterator it = raw_information.cbegin();

	qi::rule<string::const_iterator> name_value_rule = qi::as_string[(+(qi::char_ - "="))][phoenix::ref(name_) = qi::_1] >> "=" >> qi::as_string[+(qi::char_ - qi::lit(";"))][phoenix::ref(value_) = qi::_1];

	qi::rule<string::const_iterator> domain_rule = qi::lit("Domain=") >> qi::as_string[+(qi::char_ - qi::lit(";"))][phoenix::ref(domain_) = qi::_1];

	qi::rule<string::const_iterator> path_rule = qi::lit("Path=") >> qi::as_string[+(qi::char_ - qi::lit(";"))][phoenix::ref(path_) = qi::_1];

	qi::rule<string::const_iterator> expires_rule = qi::lit("Expires=") >> qi::as_string[+(qi::char_ - qi::lit(";"))][phoenix::ref(raw_expire_time_) = qi::_1];

	qi::rule<string::const_iterator> secure_rule = qi::lit("Secure")[phoenix::ref(is_secure_) = true];

	qi::rule<string::const_iterator> http_only_rule = qi::lit("HttpOnly")[phoenix::ref(is_http_only_) = true];

	qi::rule<string::const_iterator> attribute_rule = domain_rule | path_rule | expires_rule | secure_rule | http_only_rule;

	qi::rule<string::const_iterator> cookie_rule = name_value_rule >> *(qi::lit(";") >> -qi::lit(" ") >> attribute_rule);

	qi::parse(it, raw_information.cend(), cookie_rule);

	if(!raw_expire_time_.empty())
	{
		// convert string to time
		// example Mon, 24-Mar-2014 08:38:07 GMT

		stringstream time_string_stream;
		local_date_time local_time =  local_sec_clock::local_time(time_zone_ptr());

		time_string_stream.str(raw_expire_time_);
		time_string_stream >> local_time;
		expire_posix_time_ = local_time.local_time();
	}
	Uri uri(url);

	if(domain_.empty())
	{
		domain_ = uri.getHost();
	}
	if(path_.empty())
	{
		path_ = uri.getPath();
	}
}

string Cookie::getName() const
{
	return name_;
}

string Cookie::getValue() const
{
	return value_;
}

string Cookie::getPath() const
{
	return path_;
}

string Cookie::getDomain() const
{
	return domain_;
}

boost::posix_time::ptime Cookie::getExpireTime() const
{
	boost::posix_time::ptime ptime;
	return ptime;
}

string Cookie::getRawExpireTime() const
{
	return raw_expire_time_;
}

bool Cookie::isExpired() const
{
	if(getExpireTime() < boost::posix_time::second_clock::local_time())
	{
		if(expire_posix_time_ == boost::posix_time::time_from_string("1970-01-01 0:0:0"))
		{
			return false;
		}
		// cookie is expired
		return true;
	}
	return false;
	
}

bool Cookie::isSecure() const
{
	return is_secure_;
}

bool Cookie::isHttpOnly() const
{
	return is_http_only_;
}

string Cookie::getRawValue() const
{
	return raw_information_;
}

bool Cookie::isEqual(const Cookie& cookie) const
{
	Cookie target_cookie = cookie;
	if(getRawValue() != target_cookie.getRawValue())
	{
		return false;
	}
	return true;
}

Cookie::~Cookie()
{
}

}// namespace GooglePlusLibrary
}// namespace Gplusnasite
