#ifndef SERVER_HPP
#define SERVER_HPP

#include "Configs.hpp"
#include "stdIncludes.hpp"
#include "typedefs.hpp"
#include "VirtualServer.hpp"
#include "CGI.hpp"

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
	std::map<int, std::pair<VirtualServer*, int> >	getServerAndReqOfClient;
	// map client fd to vserver ptr and nth request in the list of current requests
	
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

str		long_to_str(long x);
str		long_to_hexstr(long x);

#endif
