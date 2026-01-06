#include "./../inc/Configs.hpp"


Config::Config(char *file)
{
	(void)file;
	vservers[0].port = 8090;
	vservers[0].host = "10.12.7.3";
	vservers[0].root = "/";
	vservers[1].port = 9097;
	vservers[1].host = "localhost";
	vservers[1].root = "/home";
}
