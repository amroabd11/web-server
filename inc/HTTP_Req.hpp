


#ifndef HTTP_REQ_HPP
#define HTTP_REQ_HPP

#include "Configs.hpp"
#include "ReqTokenizer.hpp"
#include "stdIncludes.hpp"
#include "typedefs.hpp"

//#include <sstream>

class HTTP_Req {
public:
	// === DATA ===
	// flags
	std::vector<str>	start_line;
	bool				isReqHeadComplete;
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
	long				contentLength;
	std::vector<str>	Transfer-Encoding;

	str					parsingerr; //HTTP_000 by default no error 

	str	_host_name;
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
