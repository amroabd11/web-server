

#include "./../inc/Server.hpp"

VirtualServer::VirtualServer(str host, int port, int epfd, const Config& config)
{
	int	res;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		somethingWentWrongFunc("socket");

	struct sockaddr_in	addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_aton(host.c_str(), &addr.sin_addr);

	res = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
	if (res < 0)
		somethingWentWrongFunc("bind");

	res = listen(sockfd, 10);
	if (res < 0)
		somethingWentWrongFunc("listen");

	struct epoll_event event;

	event.events = EPOLLIN;
	event.data.fd = sockfd;	

	this->epfd = epfd;
	this->config = &config;

	res = epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
	if (res < 0)
		somethingWentWrongFunc("epoll_ctl");


}

VirtualServer::~VirtualServer()
{

}
