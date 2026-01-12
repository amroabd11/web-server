#ifndef	PARSE_CONFIG_HPP
#define PARSE_CONFIG_HPP

#include "stdIncludes.hpp"
#include "Configs.hpp"
#include "Server.hpp"

struct	virtualServersParsing;
class	Config;

class	HttpTrafficParse
{
	private:
		std::string		FileData;
		std::vector<str>	headers;
		std::vector<str>	body;
	public:
		//HttpTrafficParse(char* file);
		std::vector<virtualServersParsing>	Vs;
};

#endif
