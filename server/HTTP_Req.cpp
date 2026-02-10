
#include "../inc/Server.hpp"


// === CONSTRUCTOR ===
HTTP_Req::HTTP_Req()
{
	isReqHeadComplete = false;
	isResComplete = false;
	sentResHead = false;
	servFileChanged = false;
	GET_fd = -2;
	POST_fd = -2;
	CGI = HTML;
	contentLength = -1;
}

HTTP_Req::HTTP_Req(const HTTP_Req& other)
{
	*this = other;
}
HTTP_Req& HTTP_Req::operator=(const HTTP_Req& other)
{
	this->isReqHeadComplete = other.isReqHeadComplete;
	this->isResComplete = other.isResComplete;
	this->sentResHead = other.sentResHead;
	this->servFileChanged = other.servFileChanged;
	this->responseStatus = other.responseStatus;

	this->method = other.method; // "GET"
	this->route = other.route; // "/"
	this->version = other.version;

	this->headers = other.headers;
	this->queries = other.queries;
	this->body = other.body;
	this->CGI = other.CGI;
	
	this->response = other.response;

	// fds
	this->GET_fd = other.GET_fd;
	this->POST_fd = other.POST_fd;
	return *this;
}
HTTP_Req::~HTTP_Req() {}

void	setBadReq(HTTP_Req& request)
{
	request.method = "GET";
	request.version = "trigger 400 status code";
}
// === parsing and filling the object ===
void	HTTP_Req::parse(str _rawBytes)
{

	// RESET if new Rick 
	if (this->isResComplete)
		*this = HTTP_Req();

	if (this->isReqHeadComplete)
	{
		this->body = str(_rawBytes);
		return ;
	}
	

	requestStr += str(_rawBytes); // THIS  is for chuncked requests
	size_t _header_end = requestStr.find(str(CRLF) + str(CRLF)); 
	if (_header_end == str::npos)
		return ;
	try{
		ReqTokenizer _req_tokens(requestStr);
		method = _req_tokens.getReqLine()[0];
		route = _req_tokens.getReqLine()[1];
		version = _req_tokens.getReqLine()[2];

		std::cout << "=========================" <<std::endl;
		std::cout << route <<std::endl;
		std::cout << "=========================" <<std::endl;
		_host_name = _req_tokens.getHeaders()["Host"];
	//	if (_host_name.empty())
	//	{
	//		parsingerr = HTTP_400;
	//		return ;
	//	}
	//	headers = _req_tokens.getHeaders();
		strStrm(_req_tokens.getHeaders()["Content-Length"]) >> contentLength;
	//	std::cout <<"contentlength in server "<< contentLength<<std::endl;
		//std::cout <<"connection : << "<< _req_tokens.getHeaders()["Connection"]<<std::endl;
		parsingerr = _req_tokens.error;
		this->body = _req_tokens.body;
	}
	catch(const std::exception& e){
//		std::cout << e.what() <<std::endl;
		return ;
	}

	this->isReqHeadComplete = true;
}





#include <iostream>     // std::cout, std::endl
#include <iomanip>      // std::setw

std::string hexify(const std::string& str)
{
   std::ostringstream oss;
   int i = 0;
	char c;

   while ((c = str[i++])) {
       if (isprint(c)) {
           oss << c;  // Print printable characters as is
       } else {
           // Print non-printable characters in hexadecimal, in red color
           oss << "\033[38;5;196m" << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)c << "\033[0m";
       }
   }
   return oss.str();
}

// Overloading the << operator for HTTP_Req with ASCII art and debug output
// Updated operator<< for HTTP_Req to handle const correctly
std::ostream& operator<<(std::ostream& os, const HTTP_Req& req) {
    // Debug art
    os << "\033[38;5;82m" << "|||||||  -----+  |||||||  -----+  |||||||\033[0m\n";
    os << "\033[38;5;82m" << "  HTTP REQUEST DEBUGGING OUTPUT\n" << "|||||||  -----+  |||||||  -----+  |||||||\033[0m\n";

    // Print HTTP Request data (method, route, version)
    os << "\033[1;34m" << "Method: " << req.method << "\033[0m\n";
    os << "\033[1;34m" << "Route: " << req.route << "\033[0m\n";
    os << "\033[1;34m" << "Version: " << req.version << "\033[0m\n";
    os << "\033[1;34m" << "Request String: " << req.requestStr << "\033[0m\n";
    os << "\033[1;34m" << "Response Status: " << req.responseStatus << "\033[0m\n";

    // Content length and transfer encoding
    os << "\nContent Length: " << req.contentLength << "\n";
    os << "Transfer Encoding: ";
    for (size_t i = 0; i < req.TransferEncoding.size(); ++i) {
        os << req.TransferEncoding[i] << " ";
    }
    os << "\n";

    // Body content (in hex for unprintables)
    os << "\nBody:\n";
    if (req.body.empty()) {
        os << "  (No body content)\n";
    } else {
        os << hexify(req.body) << "\n";
    }

    // Parsing error (if any)
    if (!req.parsingerr.empty()) {
        os << "\nParsing Error: " << req.parsingerr << "\n";
    }

    // End ASCII Art
    os << "\033[38;5;82m" << "|||||||  -----+  |||||||  -----+  |||||||\033[0m\n";

    return os;
}

Chunk::Chunk()
{
	size = "0";
}
Chunk::~Chunk()
{
}
