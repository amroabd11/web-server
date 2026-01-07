
#ifndef TYPEDEFS_HPP
#define TYPEDEFS_HPP

#include "stdIncludes.hpp"

typedef std::string str;

#ifndef MAX_EVENTS
#define MAX_EVENTS 1024
#endif

#define FD_NOT_SERVER -1
#define HTTPRequestBufferSize 1024

#define FD_IS_SERVER(x) x != FD_NOT_SERVER

#endif



