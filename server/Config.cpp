#include "./../inc/Configs.hpp"


Config::Config(char *file)
{
	(void)file;
	vServers[0].port = 8090;
	vServers[0].host = "10.12.7.3";
	vServers[0].root = "/";
	vServers[1].port = 9097;
	vServers[1].host = "localhost";
	vServers[1].root = "/home";
}
