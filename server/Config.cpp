#include "./../inc/Configs.hpp"


Config::Config(char *file)
{
	(void)file;
	virtualServersParsing	vs1;// this are just for testing real ones will come from config file
	srand(time(NULL));
	vs1.port = rand();
	vs1.host = "127.0.0.1";
	vs1.root = "/home/ioulkhir/Desktop/WEBserv";
	vServers.push_back(vs1);


	// virtualServersParsing	vs2;
	// vs2.port = 8080;
	// vs2.host = "localhost";
	// vs2.root = "/home";
	// vServers.push_back(vs2);
}
