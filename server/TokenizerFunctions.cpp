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

