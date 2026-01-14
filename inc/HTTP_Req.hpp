


#ifndef HTTP_REQ_HPP
#define HTTP_REQ_HPP

#include "Configs.hpp"
#include "stdIncludes.hpp"
#include "typedefs.hpp"

class HTTP_Req {
public:
	// === DATA ===
	// flags
	bool		isReqComplete;
	bool		isResComplete;
	bool		sentResHead;
	bool		servFileChanged;
	str			responseStatus;

	str			method; // "GET"
	str			route; // "/"
	str			version;

	Headers		headers;
	Queries		queries;
	str			body;
	int			CGI;
	
	str			response;

	// fds
	int			GET_fd;
	int			POST_fd;
	
	// === parsing and filling the object ===
	void	parse(char *rawBytes);

	// === CONSTRUCTOR ===
	HTTP_Req();
};

class responseChunk {
public:

	responseChunk();
	~responseChunk();

	str		size;
	str		data;
	str		status;
};

#endif
