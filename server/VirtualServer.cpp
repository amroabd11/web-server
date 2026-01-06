

#include "./../inc/Server.hpp"

void	somethingWentWrong(const char *syscall)
{
	perror(syscall);
	throw std::runtime_error();
}

VirtualServer::VirtualServer(str host, int port)
{
	int	res;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		somethingWentWrong("socket");

	struct sockaddr_in	addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_aton(host.c_str(), &addr.sin_addr);

	res = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr))
	if (res < 0)
		somethingWentWrong("bind");

	res = listen(sockfd, 10);
	if (res < 0)
		somethingWentWrong("listen");

}


