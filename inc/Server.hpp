#ifndef SERVER_HPP
#define SERVER_HPP

#include "Configs.hpp"
#include "stdIncludes.hpp"
#include "typedefs.hpp"
#include "VirtualServer.hpp"

class VirtualServer;
void	somethingWentWrongFunc(const char *syscall);

class Server {

private:
	// === UTILITY functions ===
	unsigned long	isServerFd( int fd );

public:

	// === DATA ===
	int								epfd;
	std::vector<VirtualServer>		vServers;
	std::map<int, VirtualServer>	getServerOfThisClient;
	
	// === CONSTRUCTOR ===
	Server(const Config& config);
	~Server();
	
	// === UTILITY functions ===
	void	run( void );

	// === EXCEPTIONS ===
	class somethingWentWrong: public std::exception {
	public:
		virtual const char*	what() const throw();
	};

};

#endif
