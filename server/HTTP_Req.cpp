
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

// === parsing and filling the object ===
void	HTTP_Req::parse(char *rawBytes)
{
	// RESET 
	*this = HTTP_Req();

	str	request(rawBytes);
	std::stringstream ss(request);
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

	std::stringstream url_ss(this->route);

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
	this->body = "";

	this->isReqComplete = true;
}



responseChunk::responseChunk()
{
	size = "0";
	
}
responseChunk::~responseChunk()
{
}

