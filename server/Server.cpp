
#include "../inc/Server.hpp"

void	somethingWentWrongFunc(const char *syscall)
{
	std::cerr << syscall << ": ";
	throw Server::somethingWentWrong();
}

// === EXCEPTIONS ===
const char*	Server::somethingWentWrong::what() const throw()
{
	return strerror(errno);
}


Server::Server(const Config& config)
{
	this->epfd = epoll_create1(0);
	if (epfd < 0)
		somethingWentWrongFunc("epoll_create1");

	for (unsigned long i = 0; i < config.vServers.size(); i++)
	{
		int port = config.vServers[i].port;
		str host = config.vServers[i].host;
		
		VirtualServer	vServ(host, port, epfd, config);
		vServ.vServConfig = &config.vServers[i];
		vServers.push_back(vServ);
	}
}

Server::~Server()
{
}


// === UTILITY functions ===
unsigned long	Server::isServerFd( int fd )
{
	for (unsigned long i = 0; i < vServers.size(); i++)
	{
		if (vServers[i].fd == fd)
			return i;
	}
	return FD_NOT_SERVER;
}

void	Server::run( void )
{
	struct epoll_event		events[MAX_EVENTS];
	struct epoll_event		newEvent, modifiedEvent;
	int						clientFd, readyFd, res, vServerIdx;
	char					clientReqBuffer[HTTPRequestBufferSize];
	ssize_t					clientReqSize;
	str						response;
	int						httpRequestIndex = 0;
	VirtualServer			*requestServer;

	std::cout << "before loop" << std::endl;

	while (1)
	{
		int nfds = epoll_wait(this->epfd, events, MAX_EVENTS, -1);
		
		std::cout << "==========" << nfds << "==========" << std::endl;

		for (int i = 0; i < nfds; i++)
		{
			// we just received something in some socket
			// reqOfClient
			readyFd = events[i].data.fd;
			vServerIdx = isServerFd(readyFd);
			if (FD_IS_SERVER(vServerIdx))
			{
				// new conn
				clientFd = accept(readyFd, 0, 0);
				if (clientFd < 0)
					somethingWentWrongFunc("accept");
				newEvent.data.fd = clientFd;
				newEvent.events = EPOLLIN;

				vServers[vServerIdx].currentRequests.push_back(HTTP_Req());
				getServerAndReqOfClient[clientFd] = std::make_pair(&vServers[vServerIdx], httpRequestIndex++);

				std::cout << "new client --> " << clientFd << std::endl;


				res = epoll_ctl(epfd, EPOLL_CTL_ADD, clientFd, &newEvent);
				if (res < 0)
					somethingWentWrongFunc("epoll_ctl");
			}
			else
			{
				if (events[i].events == EPOLLIN)
				{
					// new HTTP Req
					// it would be good to mesure the time read() spends on reading
					clientReqSize = read(readyFd, clientReqBuffer, HTTPRequestBufferSize);
					if (clientReqSize < 0)
						somethingWentWrongFunc("read");
					else if (clientReqSize == 0)
					{
						// close connection
						close(readyFd);
						// getServerAndReqOfClient[readyFd].second; // clean up
						continue ;
					}
					
					clientReqBuffer[clientReqSize] = '\0';
					// and now comes parsing the req
					// parse(buffer)
					std::cout << "'" << clientReqBuffer << "'" << std::endl;

					// if parse returns 0  ----> a request is parsed and we need to respond
					requestServer = getServerAndReqOfClient[readyFd].first;
					int	index = getServerAndReqOfClient[readyFd].second;
					HTTP_Req	&req = requestServer->currentRequests[index];

					req.parse(clientReqBuffer);

					if (req.isComplete)
					{
						modifiedEvent.data.fd = readyFd;
						modifiedEvent.events = EPOLLOUT;
						res = epoll_ctl(epfd, EPOLL_CTL_MOD, readyFd, &modifiedEvent);
						if (res < 0)
							somethingWentWrongFunc("epoll_ctl");
					} else
					{
						// if parse returns -1 ----> a request is incomplete
						continue ;
					}

				}
				else if (events[i].events == EPOLLOUT)
				{
					std::cout << "responding" << std::endl;
					
					requestServer = getServerAndReqOfClient[readyFd].first;
					int	index = getServerAndReqOfClient[readyFd].second;
					HTTP_Req	&req = requestServer->currentRequests[index];
					requestServer->serve(req);
					response = req.response;
					
					write(readyFd, response.c_str(), response.size());

					// back to reading
					modifiedEvent.data.fd = readyFd;
					modifiedEvent.events = EPOLLIN;
					res = epoll_ctl(epfd, EPOLL_CTL_MOD, readyFd, &modifiedEvent);
					if (res < 0)
						somethingWentWrongFunc("epoll_ctl");
				}
			}
		}
		
	}
}
