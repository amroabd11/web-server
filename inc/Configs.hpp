#ifndef CONFIGS_HPP
#define CONFIGS_HPP

#include "stdIncludes.hpp"
#include "typedefs.hpp"
#include "Server.hpp"
#include "SyntaxError.hpp"
#include "Parser.hpp"

class Server;

struct	location
{
//	str	route;
//	std::vector<str> index;
//	str	root;
//	uint16_t	port;
	str		route;
	str		root;
	bool	autoindex;
	std::vector<str>	error;
	std::vector<str> index;
	std::vector<str> methods;
	std::string redir;
	size_t	body_size;
//	std::vector<str> cgi;
};

struct	virtualServersParsing
{
	std::vector<Token> block;
	uint16_t	port;
	str		host;
	str		root;
	bool	autoindex;
	std::vector<str>	error;
	std::vector<str> index;
	std::vector<str> methods;
	std::string redir;
	size_t	body_size;
	std::vector<str> cgi;
	std::vector<location> locations;
};


class Config
{
	private:
		std::vector<virtualServersParsing>	config_vServers;
		std::vector<str>	file_contents;
		virtualServersParsing vser_struct;
	public:
		Config();
		Config& operator=(const Config& other);
		Config(char *file);
		//typedef void(*handler_t)(virtualServersParsing&, size_t &);
		

		//bool	check_syntax_error(std::vector<str>&);
		//void	tokenize_file_contents(std::vector<str>&);
		std::vector<str>	getContents();
		const std::vector<virtualServersParsing> getVservers() const;
		//static void	setVservers(virtualServersParsing&);
		//virtualServersParsing getTokensBlock();
};


#endif
