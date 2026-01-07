#ifndef SERVER_HPP
#define SERVER_HPP

#include "Configs.hpp"
#include "stdIncludes.hpp"
#include "typedefs.hpp"
#include "VirtualServer.hpp"

class VirtualServer;
void	somethingWentWrongFunc(const char *syscall);

class Server {

public:

	// === DATA ===
	int							epfd;
	std::vector<VirtualServer>	vServers;
	
	// === CONSTRUCTOR ===
	Server(const Config& config);
	~Server();
	
	// === EXCEPTIONS ===
	class somethingWentWrong: public std::exception {
	public:
		virtual const char*	what() const throw();
	};

};

#endif
