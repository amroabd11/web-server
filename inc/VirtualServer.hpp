#ifndef VIRTUAL_SERVER_HPP
#define VIRTUAL_SERVER_HPP

#include "Configs.hpp"
#include "stdIncludes.hpp"
#include "typedefs.hpp"
#include "HTTP_Req.hpp"

class VirtualServer
{
public:
	// === DATA ===
	int						sockfd; // server socket fd
	int						epfd; // global epoll fd
	const Config*			config;
	std::map<int, HTTP_Req>	reqOfClient; // get HTTP_Req of certain fd

	// === CONSTRUCTOR ===
	VirtualServer(str host, int port, int epfd, const Config& config);
	~VirtualServer();

	// === Functions ===
	void	run( void );
};



#endif
