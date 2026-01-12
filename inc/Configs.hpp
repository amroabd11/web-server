#ifndef CONFIGS_HPP
#define CONFIGS_HPP

#include "stdIncludes.hpp"
#include "typedefs.hpp"
#include "ConfigParser.hpp"
#include "Server.hpp"

class Server;
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
		std::vector<virtualServersParsing>	config_vServers;

		// contructor
		Config(char *file);

		// functions
		bool	check_syntax_error(std::vector<str>&);
		//bool	check_syntax_error(std::string&);
};


#endif
