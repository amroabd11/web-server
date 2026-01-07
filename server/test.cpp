#include "./../inc/Server.hpp"

Server::Server(const Config& config)
{
	epfd = epoll_create1(0);
	if (epfd < 0)
		throw std::runtime_error("epoll_create1 failed");
	for (int i = 0; i < config.vservers.size() ;i++)
	{
		//here comes the part of server managing, there will be size sockets for each vserver, and i implemeted vector of structors since i will need that to access element of each connection if i needed to;
		//std::cout << config.vservers[i].port<<std::endl;
		for (int j = 0; j<l_sockets.size(); j++)
		{
			listen_sock	lsock;
			if (l_sockets[j].port == config.vservers.port)
				lsock.vhost.push_back(&config.vserver[j]);
			else
			{
				struct	sockaddr_in server_addr;
				socklen_t	len_addr;
				int	sock = socket(AF_INET, SOCK_STREAM, 0);
				if(sock < 0)
					throw std::runtime_error("socket failed");
				fcntl(sock, F_SETFL, O_NONBLOCK);
				int op = 1;
				setsockopt(sock, SOL_SOCKET,SO_REUSEADDR, &op, sizeof(op));
				lsock.fd = sock;
				lsock.port = config.vservers[i].port;
				lsock.vhost.push_back(&config.vserver[i]);
				server_addr.sin_family = AF_INET;
				server_addr.sin_port = htons(lsock.port);
				server_addr.sin_addr.sin_addr = inet_pton(lsock.vhost[i].host);
				len_addr = sizeof(sockaddr);
				if (bind(sock, (struct sockaddr*)&server_addr,&len_addr) == -1)
					throw std::runtime_error("bounding the socket failed"); 
				if (listen(sock, 10) == -1)
					throw std::runtime_error("listening failed");
				struct epoll_event ev;
				ev.events = EPOLLIN;
				ev.data.fd = sock;
				epoll_ctl(epfd, EPOLL_CTL_ADD, sock, &ev);
			}
		}
	}
}

Server::~Server()
{
	close (epfd);
}

//listen_sock Server::FindListeningSock(uint16_t port)
//{
//	for (size_t i = 0; i<l_sockets.size(); i++)
//	{
//		if (l_sockets[i].port == port)
//			return l_sockets[i];
//	}
//	return NULL;
//}

int	Server::is_listen_fd(int fd)
{
	for (int i = 0; i < l_sockets.size();i++)
	{
		if(l_sockets[i].fd == fd)
			return true;
	}
	return false;
}

void	Server::run()
{
	//this function is responsible for waiting on events
	int num_events;
	struct	epoll_event events[1024];
	while(1)
	{
		num_events = epoll_wait(epfd, events, 1024, -1);
		if (num_events < 0)
			throw std::runtime_error("epoll wait failed");
		for (int i = 0, i < num_events; i++)
		{
			if (is_listen_fd(events[i].data.fd)
			{
				int	listener = events[i].data.fd;
				sockaddr_in client_addr;
				int	new_fd;
				new_fd = accept(listener,(struct sockaddr*)&client_addr, (socklen_t *)&sizeof(client_addr));
				if (new_fd < 0)
					throw std::runtime_error("accept failed");
				fcntl(new_fd, F_SETFL, O_NONBLOCK);
				struct epoll_event ev;
				ev.events = EPOLLIN;
				ev.data.fd = new_fd;
				epoll_ctl(epfd, EPOLL_CTR_ADD, new_fd, &ev);
				clients client_conn;
				client_conn.fd = new_fd;
				client_conn.listen_fd = listener;
				client_conn.request = NULL;
				client_conn.response = NULL;
				conn_clients.insert(new_fd, client_conn);
			}
			else if (events[i].events & EPOLLIN)
				handle_request(events[i].data.fd);
			else if (events[i].events & EPOLLOUT)
				handle_response(events[i].data.fd);
		}
	}
}


void	Server::handle_request(int fd)
{
	recv();
}




