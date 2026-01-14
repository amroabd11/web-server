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
	int							fd; // server socket fd
	int							epfd; // global epoll fd
	const Config*				config;
	const virtualServersParsing	*vServConfig;
	std::vector<HTTP_Req>		currentRequests;
	// map client fd to response
	// (so we know what of the many responses to give to a certain client)

	// === CONSTRUCTOR ===
	VirtualServer();
	VirtualServer(str host, int port, int epfd, const Config& config);
	~VirtualServer();

	// === Functions ===
	void		serve(HTTP_Req& request, str status);
	void		handleErrPages(HTTP_Req& request);
	void		fillChunk(HTTP_Req& request, responseChunk& chunck, str& file2Serv);

};



#endif
