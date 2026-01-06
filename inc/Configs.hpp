#ifndef CONFIGS_HPP
#define CONFIGS_HPP

#include "stdIncludes.hpp"
#include "typedefs.hpp"

struct	virtualServers
{
	uint16_t	port;
	str			host;
	str			root;
	//other directives;
};

class Config
{
	public:
		Config(char *file);
		std::vector<virtualServers> vservers;
};


#endif
