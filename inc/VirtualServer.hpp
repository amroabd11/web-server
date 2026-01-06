#ifndef SERVER_HPP
#define SERVER_HPP

#include "Configs.hpp"
#include "stdIncludes.hpp"
#include "typedefs.hpp"

class VirtualServer
{
public:
	// === DATA ===
	int						sockfd; // server socket fd
	int						epfd; // global epoll fd
	Config					*config;
	std::map<int, HTTP_Req>	reqOfClient; // get HTTP_Req of certain fd

	// === CONSTRUCTOR ===
	VirtualServer(str host, int port);
	~VirtualServer();

	// === Functions ===
	void	run( void );
};



#endif
