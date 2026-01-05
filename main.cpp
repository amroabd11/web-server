

#include "inc/webserv.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Usage:\n\t./webserv <config_file>\n" << std::endl;
        return EXIT_FAILURE;
    }
    str configFile = str(av[1]);

    std::cout << "project only works on my machine" << std::endl;

    return EXIT_SUCCESS;
}
