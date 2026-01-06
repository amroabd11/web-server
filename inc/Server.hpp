#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <iostream>
#include <vector>
#include <exception>
#include <stdint.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <inet/arpa.h>
#include "Configs.hpp"


struct Listen_sock
{
	int fd;
	uint16_t port;
	std::vector<Virtual_serv*> vhost;
};

class Server
{
	private:
		std::vector <Listen_sock> l_sockets;
		int	epfd;
	public:
		Server(const Config& config);
		~Server();
		void	run();
};



#endif
