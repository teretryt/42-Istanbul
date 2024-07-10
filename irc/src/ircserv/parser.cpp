#include "../../include/ircserv/Server.hpp"
#include "../../include/ircserv/Client.hpp"
#include <sstream>

static std::string trim(const std::string &str, char delimeter) {
    size_t first = str.find_first_not_of(delimeter);
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(delimeter);
    return str.substr(first, (last - first + 1));
}

std::vector<std::string> parser(std::string& buffer)
{
	std::vector<std::string> r;
	std::string	line;
	std::stringstream ss;

	ss << buffer;
	while (std::getline(ss, line))
	{
		line = trim(line, '\r');
		r.push_back(line);
	}
	ss.clear();
	return (r);
}

