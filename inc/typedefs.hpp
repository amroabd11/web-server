
#ifndef TYPEDEFS_HPP
#define TYPEDEFS_HPP

#include "stdIncludes.hpp"

typedef std::string str;
typedef std::stringstream strStrm;
typedef std::map<str, str> Headers;
typedef std::map<str, str> Queries;
typedef std::map<str, str>::iterator HeadersIt;
typedef std::map<str, str>::iterator QueriesIt;

//  DEGUGGING
void logStringAsHex(str str);

#ifndef MAX_EVENTS
#define MAX_EVENTS 1024
#endif

#define FD_NOT_SERVER -1
#define HTTPRequestBufferSize 7
#define HTTPResponseBufferSize 1024
#define HTTP_POST_ReqBufferSize 1024

#define FD_IS_SERVER(x) x != FD_NOT_SERVER

// CGIs
#define HTML (0)
#define PYTHON (1)
#define NODEJS (2)

// more beautiful
#define CRLF "\r\n"
#define VERSION "HTTP/1.1"

// 0xx – Edge cases
#define HTTP_000 "000 NO STATUS"

// 1xx – Informational
#define HTTP_100 "100 Continue"
#define HTTP_101 "101 Switching Protocols"

// 2xx – Success
#define HTTP_200 "200 OK"
#define HTTP_201 "201 Created"
#define HTTP_202 "202 Accepted"
#define HTTP_204 "204 No Content"

// 3xx – Redirection
#define HTTP_301 "301 Moved Permanently"
#define HTTP_302 "302 Found"
#define HTTP_304 "304 Not Modified"

// 4xx – Client Errors
#define HTTP_400 "400 Bad Request"
#define HTTP_401 "401 Unauthorized"
#define HTTP_403 "403 Forbidden"
#define HTTP_404 "404 Not Found"
#define HTTP_405 "405 Method Not Allowed"
#define HTTP_406 "406 Not Acceptable"
#define HTTP_408 "408 Request Timeout"
#define HTTP_409 "409 Conflict"
#define HTTP_410 "410 Gone"
#define HTTP_415 "415 Unsupported Media Type"
#define HTTP_429 "429 Too Many Requests"

// 5xx – Server Errors
#define HTTP_500 "500 Internal Server Error"
#define HTTP_501 "501 Not Implemented"
#define HTTP_502 "502 Bad Gateway"
#define HTTP_503 "503 Service Unavailable"
#define HTTP_504 "504 Gateway Timeout"

#endif
