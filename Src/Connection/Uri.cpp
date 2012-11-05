#include <Connection/Uri.hpp>

#include <boost/regex.hpp>

namespace Gplusnasite
{
namespace GooglePlusLibrary
{

using namespace std;

Uri::Uri(const string& url)
{
	const char * pattern = "\\A([^:]+)://"   // scheme
			"((?:([^:/@]*)@)?([^:@/]*)(?::(\\d+))?)/"   // authority = [user-info@]host[:port]
			"([^\\?]*)(?:\\?([^#]*))?(?:#(.*))?\\z";    // body = [path?query#fragment]
	
	const boost::regex regex(pattern);
	boost::smatch smatch;
	
	regex_match(url, smatch, regex);
	scheme    = smatch[1].str();
	authority = smatch[2].str();
	user      = smatch[3].str();
	host      = smatch[4].str();
	port      = atoi(smatch[5].str().c_str());
	path      = smatch[6].str();
	query     = smatch[7].str();
	fragment  = smatch[8].str();
}


string Uri::getScheme() const
{
	return scheme;
}

string Uri::getAuthority() const
{
	return authority;
}

string Uri::getUser() const
{
	return user;
}

string Uri::getHost() const
{
	return host;
}

int Uri::getPort() const
{
	return port;
}

string Uri::getPath() const
{
	return path;
}

string Uri::getQuery() const
{
	return query;
}

string Uri::getFragment() const
{
	return fragment;
}

Uri::~Uri()
{
}

} // namespace GooglePlusLibrary
} // namespace Gplusnasite
