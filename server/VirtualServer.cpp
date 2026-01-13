

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
	std::cout << "test this --> " << host << ":" << port << "/index.html"<< "\n";
	std::cout << "test this --> " << host << ":" << port << "/images.jpeg"<< "\n";
	std::cout << "use command: nc " << host << " " << port << "\n";
}

VirtualServer::VirtualServer()
{
	
}

VirtualServer::~VirtualServer()
{

}



#include <iostream>
#include <iomanip>
#include <string>

void logStringAsHex(str str)
{
    for (size_t i = 0; i < str.size(); ++i)
    {
        // Print each byte as 2-digit hex
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << (static_cast<unsigned int>(static_cast<unsigned char>(str[i]))) 
                  << " ";
    }
    std::cout << std::dec << std::endl; // reset to decimal
}

str	long_to_str(long x)
{
	std::ostringstream oss;
	oss << x;
	return oss.str();
}

str	long_to_hexstr(long x)
{
	if (x <= 0) return "0";

	str	result;
	if (x >= 0x10)
		result = long_to_hexstr(x >> 4);
	result += "0123456789abcdef"[x & 0x0F];
	return result;
}

// fill chunk with data
void	fillChunk(HTTP_Req& request, responseChunk& chunck, str& file2Serv)
{
	ssize_t		read_ret;
	char		buffer[HTTPResponseBufferSize];
	int			my_pipe[2];
	char		*envp[request.queries.size()+1];

	if (request.GET_fd == -2)
	{
		if (request.CGI == HTML)
			request.GET_fd = open(file2Serv.c_str(), 0);
		else
		{
			if (pipe(my_pipe) < 0)
				somethingWentWrongFunc("pipe");
			request.GET_fd = my_pipe[0];
			int i = 0;
			for (QueriesIt it = request.queries.begin(); it != request.queries.end(); ++it)
			{

				it->first += "=\"" + it->second + "\"";

				envp[i++] = (char *)(it->first.c_str());
				std::cout << "envp[i] --> " << i << envp[i-1] << "\n";
			}
			envp[i] = NULL;
			// new process	--> request.CGI {file2Serv} 
			// env			--> request queries

			int pid = fork();
			if (pid)
			{
				// parent
				close(my_pipe[1]);
			}
			else
			{
				// child
				close(my_pipe[0]);
				dup2(my_pipe[1], STDOUT_FILENO);
				close(my_pipe[1]);

				char *argv[3];

				argv[0] = (char*)("python");
				argv[1] = (char*)(file2Serv.c_str());
				argv[2] = NULL;

				// char *envp[] = { NULL };

				execve("/usr/bin/python", argv, envp);
				somethingWentWrongFunc("execve");
			}
		}
	}
	//  check if open 
	if (request.GET_fd == -1)
	{
		request.isResComplete = true;
		chunck.status = HTTP_404;
	}
	else
	{
		if (request.sentResHead)
		{
			std::cout << "fd --> " << request.GET_fd << "\n";
			read_ret = read(request.GET_fd, buffer, HTTPResponseBufferSize);
			
			if (read_ret <= 0)
				request.isResComplete = true;
			else
				chunck.data = str(buffer, read_ret);
			chunck.status = HTTP_200;
		}
	}
	chunck.size = long_to_hexstr(read_ret);
}

// === Functions ===
void		VirtualServer::serve(HTTP_Req& request)
{

	str 		response;
	str 		version = "HTTP/1.1";
	Headers		headers;
	str			body;
	str			file2Serv = this->vServConfig->root + request.route;

	responseChunk	chunck;

	if (request.method == "GET")
	{
		fillChunk(request, chunck, file2Serv);
	}
	
	headers["Transfer-Encoding"] = "chunked";
	headers["Server"] = "dyali ana w p000py";

	if (!request.sentResHead)
	{
		response = version + " " + chunck.status + CRLF;
		for (HeadersIt it = headers.begin(); it != headers.end(); ++it)
			response += it->first + ": " + it->second + CRLF;
		request.sentResHead = true;
		response += CRLF;
	}
	else
	{
		response = chunck.size + CRLF + chunck.data + CRLF;
	}

	if (request.isResComplete)
	{
		close(request.GET_fd);
		request.GET_fd = -2;
		response += CRLF;
	}

	// std::cout << "response ---> ;;;;" << body << ";;;;\n";
	// std::cout << "response ---> ;;;;" << chunck.size  << ";;;;\n";

	// logStringAsHex(response);

	request.response = response;
}

