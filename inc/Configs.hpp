#ifndef CONFIGS_HPP
#define CONFIGS_HPP

#include "stdIncludes.hpp"
#include "typedefs.hpp"

class Config
{
	public:
		// DATA
		std::vector<virtualServers> vServers;

		// contructor
		Config(char *file);

		// functions

};


#endif
