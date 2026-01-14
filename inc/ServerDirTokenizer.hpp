#ifndef	PARSE_CONFIG_HPP
#define PARSE_CONFIG_HPP

#include "stdIncludes.hpp"
#include "Configs.hpp"
#include "Server.hpp"

struct	virtualServersParsing;
class	Config;

class	TokenizServerDirectives
{
	private:
		std::string		FileData;
		std::vector<str>	headers;
		std::vector<str>	body;
	public:
		//HttpTrafficParse(char* file);
		std::vector<virtualServersParsing>	Vs;
		static std::vector<std::string>	split(std::string, std::string);
		static void	insert_locations(std::map<str, str>, std::string, std::string);
};

#endif
