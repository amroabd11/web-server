#ifndef CONFIGS_HPP
#define CONFIGS_HPP

#include "stdIncludes.hpp"
#include "typedefs.hpp"
#include "ServerDirTokenizer.hpp"
#include "Server.hpp"

class Server;
class TokenizServerDirectives;
// yes yes kml its a good idea
struct	virtualServersParsing
{
	std::vector<str> block;
	uint16_t	port;
	str			host;
	str			root;
	std::vector<std::map<str, str> > locations;
	std::map<str, str>::iterator it;
	//other directives;
};


class Config
{
	public:
		// DATA
		std::vector<virtualServersParsing>	config_vServers;
		//std::map<str, str>::iterator it;

		// contructor
		Config(char *file);

		// functions
		bool	check_syntax_error(std::vector<str>&);
		void	tokenize_file_contents(std::vector<str>&);
		//bool	check_syntax_error(std::string&);
};


#endif
