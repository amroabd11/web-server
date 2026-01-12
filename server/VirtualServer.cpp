

#include "./../inc/Server.hpp"

VirtualServer::VirtualServer(str host, int port, int epfd, const Config& config)
{
	int	res;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
		somethingWentWrongFunc("socket");

	struct sockaddr_in	addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_aton(host.c_str(), &addr.sin_addr);

	int opt;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));

	res = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
	if (res < 0)
		somethingWentWrongFunc("bind");

	res = listen(fd, 10);
	if (res < 0)
		somethingWentWrongFunc("listen");

	struct epoll_event event;

	event.events = EPOLLIN;
	event.data.fd = fd;	

	this->epfd = epfd;
	this->config = &config;

	res = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);
	if (res < 0)
		somethingWentWrongFunc("epoll_ctl");


}

VirtualServer::VirtualServer()
{
	
}

VirtualServer::~VirtualServer()
{

}



// === Functions ===
str		VirtualServer::serve(HTTP_Req& request)
{
	// now process the req and serve it
	// request
	(void)request;
	return "HTTP/1.1 200 OK\nCP_Z3R0{itsworkingBABY}";
}

