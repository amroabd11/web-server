

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



	std::cout << "listening on " << host << ":" << port << " port is " << port << "\n";
	std::cout << "use command: nc " << host << " " << port << "\n";
}

VirtualServer::VirtualServer()
{
	
}

VirtualServer::~VirtualServer()
{

}



// === Functions ===
void		VirtualServer::serve(HTTP_Req& request)
{
	// now process the req and serve it
	// request

	// str response = "HTTP/1.1 200 OK\n";
	str response;
	str version = "HTTP/1.1";
	str	status;
	str	body;

	response = version;

	if (request.method == "GET")
	{
		std::ifstream	file2Serve((this->vServConfig->root + request.route).c_str());
		//  check if open 
		if (!file2Serve.is_open())
			status = HTTP_404;
		else
		{
			str content;
			std::getline(file2Serve, content, '\0');
			body = content;
			status = HTTP_200;
		}
		response += " " + status +  "\n";
		response += body;
	}
	else if (request.method == "POST")
	{
		std::ofstream	file2Post((this->vServConfig->root + request.route).c_str());

		if (!file2Post.is_open())
			status = HTTP_404;
		else
		{
			file2Post << request.body;
			status = HTTP_200;
		}
		response += " " + status +  "\n";
	}
	else if (request.method == "DELETE")
	{

		response += " " + str(HTTP_200) +  "\n";
	}
	else
		response += " " + str(HTTP_405) +  "\n";

	request.response = response;
}

