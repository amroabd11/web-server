


#ifndef HTTP_REQ_HPP
#define HTTP_REQ_HPP

#include "Configs.hpp"
#include "stdIncludes.hpp"
#include "typedefs.hpp"

class HTTP_Req {
public:
	// === DATA ===
	char	buffer[1024];
	size_t	buff_len;
	
	// === HTTP ===
	// methods
	// headers
	// body

	// === CONSTRUCTOR ===
	HTTP_Req();
};

#endif
