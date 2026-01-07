#ifndef CONFIGS_HPP
#define CONFIGS_HPP

#include "stdIncludes.hpp"
#include "typedefs.hpp"


// yes yes kml its a good idea
struct	virtualServersParsing
{
	uint16_t	port;
	str			host;
	str			root;
	//other directives;
};

class Config
{
	public:
		// DATA
		std::vector<virtualServersParsing>	vServers;

		// contructor
		Config(char *file);

		// functions

};


#endif
