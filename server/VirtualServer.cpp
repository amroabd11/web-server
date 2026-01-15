

#include "./../inc/Server.hpp"

VirtualServer::VirtualServer(str host, int port, int epfd, const Config& config)
{
	int	res;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
		somethingWentWrongFunc("socket");
		
	// setsockopt
	int opt = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		somethingWentWrongFunc("setsockopt");
	
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
	std::cout << "test this --> " << host << ":" << port << "/test.html"<< "\n";
	std::cout << "test this --> " << host << ":" << port << "/images.jpeg"<< "\n";
	std::cout << "test this --> " << host << ":" << port << "/test.py"<< "\n";
	std::cout << "use command: nc " << host << " " << port << "\n";
}

VirtualServer::VirtualServer()
{
	
}

VirtualServer::~VirtualServer()
{

}



#include <iomanip>

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

// fill chunk with data
void	VirtualServer::fillChunk(HTTP_Req& request, responseChunk& chunck, str& file2Serv)
{
	ssize_t		read_ret;
	char		buffer[HTTPResponseBufferSize];
	CGI			cgi(request.CGI);

	if (request.GET_fd == -2)
		request.GET_fd = cgi.prepareFd(request, file2Serv);

	//  check if open 
	if (request.GET_fd == -1)
	{
		chunck.status = HTTP_404;
		request.isResComplete = true;
	}
	else
	{
		if (request.sentResHead)
		{
			read_ret = read(request.GET_fd, buffer, HTTPResponseBufferSize);
			// std::cout << buffer << "\n";
			
			if (read_ret <= 0)
			{
				chunck.status = HTTP_200;
				request.isResComplete = true;
			}
			else
				chunck.data = str(buffer, read_ret);
			chunck.size = long_to_hexstr(read_ret);
		}
		chunck.status = HTTP_200;
	}
}

// === Functions ===
void		VirtualServer::serve(HTTP_Req& request, str status)
{
	str 		response;
	str 		version = VERSION;
	Headers		headers;
	str			body;
	str			file2Serv = this->vServConfig->root + request.route;

	responseChunk	chunck;

	if (request.version == VERSION)
	{
		if (request.method == "GET")
		{
			this->fillChunk(request, chunck, file2Serv);
		}
		else
		{
			chunck.status = HTTP_405;
			request.isResComplete = true;
		}
	}
	else
	{
		chunck.status = HTTP_400;
		request.isResComplete = true;
	}

	headers["Transfer-Encoding"] = "chunked";
	headers["Server"] = "dyali ana w p000py";

	if (!request.sentResHead)
	{

		// std::cout << "am here " << std::endl;

		request.responseStatus = chunck.status;
		response = version + " " + ((status == HTTP_000) ? chunck.status : status) + CRLF;
		for (HeadersIt it = headers.begin(); it != headers.end(); ++it)
			response += it->first + ": " + it->second + CRLF;
		request.sentResHead = true;
		response += CRLF;
	}
	else
		response = chunck.size + CRLF + chunck.data + CRLF;

	if (request.isResComplete)
	{
		close(request.GET_fd);
		request.GET_fd = -2;
		response += CRLF;
	}

	request.response = response;
}

void		VirtualServer::handleErrPages(HTTP_Req& request)
{
	str	status = request.responseStatus;
	std::stringstream ss(status);
	str	statusCode;

	ss >> statusCode;
	if (request.responseStatus != HTTP_200) // supported err codes
	{
		request = HTTP_Req();
		request.method = "GET";
		request.route = "/default_err_pages/" + statusCode + ".html";
		request.version = VERSION;
		request.sentResHead = false;
		request.isReqComplete = true;
		this->serve(request, status);
		if (request.responseStatus == HTTP_404)
		{
			close(request.GET_fd);
			request.GET_fd = -2;
			request.response += str("0") + CRLF + CRLF;
		}
	}
}


