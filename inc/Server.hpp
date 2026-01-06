#ifndef SERVER_HPP
#define SERVER_HPP

#include "Configs.hpp"
#include "stdIncludes.hpp"
#include "typedefs.hpp"

struct Listen_sock
{
	int fd;
	uint16_t port;
	std::vector<virtualServers*> vhost;
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
