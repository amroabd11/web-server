#include "./../inc/Configs.hpp"


Config::Config(char *file)
{

	(void)file;
	virtualServersParsing	vs1;// this are just for testing real ones will come from config file
	vs1.port = 8090;
	vs1.host = "10.12.7.3";
	vs1.root = "/";
	virtualServersParsing	vs2;
	vs2.port = 8080;
	vs2.host = "localhost";
	vs2.root = "/home";
	vServers.push_back(vs1);
	vServers.push_back(vs2);
}
