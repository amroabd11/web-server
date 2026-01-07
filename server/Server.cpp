
#include "../inc/Server.hpp"

void	somethingWentWrongFunc(const char *syscall)
{
	perror(syscall);
	throw Server::somethingWentWrong();
}

// === EXCEPTIONS ===
const char*	Server::somethingWentWrong::what() const throw()
{
	return "(runtime error)";
}

Server::Server(const Config& config)
{
	this->epfd = epoll_create1(0);
	if (epfd < 0)
		somethingWentWrongFunc("epoll_create1");

	for (unsigned long i = 0; i < vServers.size(); i++)
	{
		int port = config.vServers[i].port;
		str host = config.vServers[i].host;
		
		VirtualServer	vServ(host, port, epfd, config);
		vServers.push_back(vServ);
	}


}
