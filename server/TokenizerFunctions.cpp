#include "../inc/ServerDirTokenizer.hpp"

std::vector<std::string> TokenizServerDirectives::split(std::string line, std::string del)
{
	std::vector<std::string> tokens;
	std::string::size_type pos=0;
	std::string::size_type prev=0;
	bool keepEmpty = false;

	while((pos = line.find_first_of(del, prev)) != std::string::npos)
	{
		if (keepEmpty || pos > prev)
			tokens.push_back(line.substr(prev , pos- prev));
		prev = pos + 1;
	}
	if (prev < line.length())
		tokens.push_back(line.substr(prev));
	else if (keepEmpty && prev == line.length())
		tokens.push_back("");
	return tokens;
}

void	TokenizServerDirectives::insert_locations(std::map<str,str> locations, std::string token, std::string value)
{
	std::pair<std::map<str,str>::iterator, bool> res =locations.insert(std::make_pair(token, value));
	if (!res.second)
		throw std::runtime_error("Duplicate locations in config file" +token);
	return res;
}

