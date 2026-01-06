


/*
 *
 * First we Parse the config file
 * Then we setup services listening on diff ports
 * Then each service handles its request
 * 	CGI {Python3, fast-cgi}
 * Done
 *
 * */

#include "inc/Configs.hpp"
#include "inc/Server.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Usage:\n\t./webserv <config_file>\n" << std::endl;
        return EXIT_FAILURE;
    }

	Config configFile(av[1]);
	Server server(configFile);



    std::cout << "project only works on my machine" << std::endl;

    return EXIT_SUCCESS;
}
