

#include "./../inc/Server.hpp"

VirtualServer::VirtualServer(str host, int port, int epfd, const Config& config)
{
	int	res;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
		somethingWentWrongFunc("socket");
		
	// setsockopt
	
	struct sockaddr_in	addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_aton(host.c_str(), &addr.sin_addr);

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
void		VirtualServer::serve(HTTP_Req& request, int clientFd)
{
	// now process the req and serve it
	// request
	(void)request;

	std::stringstream ss;

	ss << vServConfig->port;

	str response = "HTTP/1.1 200 OK\nCP_Z3R0{itsworkingBABY}\nhello from " + vServConfig->host + ":" + ss.str();
	this->getResponseOfClient[clientFd] = response;

}

