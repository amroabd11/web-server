


#ifndef HTTP_REQ_HPP
#define HTTP_REQ_HPP

#include "Configs.hpp"
#include "stdIncludes.hpp"
#include "typedefs.hpp"

class HTTP_Req {
public:
	// === DATA ===
	bool				isComplete;

	str					method; // "GET"
	str					route; // "/"
	str					version; // "HTTP/1.1"

	std::map<str, str>	headers;
	str					body;
	
	str					response;
	
	// === parsing and filling the object ===
	void	parse(char *rawBytes);

	// === CONSTRUCTOR ===
	HTTP_Req();
};

#endif
