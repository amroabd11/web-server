#include "./../inc/Server.hpp"

Server::Server(const Config& config)
{
	epfd = epoll_create1(0);
	for (int i = 0; i < config.vservers.size() ;i++)
	{
		//here comes the part of server managing, there will be size sockets for each vserver, and i implemeted vector of structors since i will need that to access element of each connection if i needed to;
		std::cout << config.vservers[0].port<<std::endl;
	}
}

Server::~Server()
{
	close (epfd);
}


void	Server::run()
{
	//this function is responsible for waiting on events
}
