


#ifndef HTTP_REQ_HPP
#define HTTP_REQ_HPP

#include "Configs.hpp"
#include "stdIncludes.hpp"
#include "typedefs.hpp"

#include <sstream>

class HTTP_Req {
public:
	// === DATA ===
	// flags
	bool				isReqHeadComplete;
	bool				isReqBodyComplete;
	bool				isResComplete;
	bool				sentResHead;
	bool				servFileChanged;
	str					responseStatus;

	str					requestStr;
	str					method; // "GET"
	str					route; // "/"
	str					version;

	Headers				headers;
	Queries				queries;
	int					contentLength;
	str					body;
	int					CGI;
	
	str					response;

	// fds
	int					GET_fd;
	int					POST_fd;
	strStrm				bodyStream;
	
	// === parsing and filling the object ===
	void	parse(str rawBytes);

	// === CONSTRUCTOR ===
	HTTP_Req();
	HTTP_Req(const HTTP_Req& other);
	HTTP_Req& operator=(const HTTP_Req& other);
	~HTTP_Req();
};

class Chunk {
public:

	Chunk();
	~Chunk();

	str		size;
	str		data;
	str		status;
};

#endif
