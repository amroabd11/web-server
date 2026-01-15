
#include "../inc/Server.hpp"


// === CONSTRUCTOR ===
HTTP_Req::HTTP_Req()
{
	isReqComplete = false;
	isResComplete = false;
	sentResHead = false;
	servFileChanged = false;
	GET_fd = -2;
	POST_fd = -2;
	CGI = HTML;
}

HTTP_Req::HTTP_Req(const HTTP_Req& other)
{
	*this = other;
}
HTTP_Req& HTTP_Req::operator=(const HTTP_Req& other)
{
	this->isReqComplete = other.isReqComplete;
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

// === parsing and filling the object ===
void	HTTP_Req::parse(char *rawBytes)
{
	// RESET 
	HTTP_Req();

	str	request(rawBytes);
	strStrm ss(request);
	str	firstWord;


	// GET, POST, and DELETE
	// if (std::getline(ss, firstWord, ' '))
	// {
	// 	if (firstWord == "GET" || firstWord == "POST" || firstWord == "DELETE")
	// 		this->method = firstWord;
	// }
	// else
	// {
		
	// }


	ss >> this->method;
	ss >> this->route;
	ss >> this->version;

	strStrm url_ss(this->route);

	std::getline(url_ss, this->route, '?');
	while (true)
	{
		str	key;
		str	value;
		if (
			!std::getline(url_ss, key, '=') ||
			!std::getline(url_ss, value, '&')
		)
			break ;
		this->queries[key] = value;
	}


	this->headers["Host"] = "127.0.0.1:8201";
	this->headers["Accept-Language"] = "en-US,en;q=0.6";

	// this->queries["test"] = "155";
	// this->queries["anothertest"] = "testing string";

	// this->CGI = HTML;
	this->CGI = HTML;
	if (this->route == "/test.py")
		this->CGI = PYTHON;
	// PYTHON PHP
	// this->body = "";
	this->bodyStream << this->body;

	this->isReqComplete = true;
}



Chunk::Chunk()
{
	size = "0";
	
}
Chunk::~Chunk()
{
}

