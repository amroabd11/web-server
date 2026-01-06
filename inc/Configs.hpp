#ifndef CONFIGS_HPP
#define CONFIGS_HPP


#include <iostream>
#include <vector>
#include <cstdint>
#include <exception>
//#include "Server.hpp"

struct	Virtual_servers
{
	uint16_t	port;
	std::string	host;
	std::string	root;
	//other directives;
};

class Config
{
	public:
		Config(char *file);
		std::vector<Virtual_servers> vservers;
};


#endif
