
#include "../inc/Server.hpp"


// === CONSTRUCTOR ===
HTTP_Req::HTTP_Req()
{
	isReqComplete = false;
	isResComplete = false;
	sentResHead = false;
	GET_fd = -2;
	POST_fd = -2;
}


// === parsing and filling the object ===
void	HTTP_Req::parse(char *rawBytes)
{
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

	// this->method = "GET";
	// this->route = "/index.html";
	// this->version = "HTTP/1.1";



	this->headers["Host"] = "127.0.0.1:8201";
	this->headers["Accept-Language"] = "en-US,en;q=0.6";

	this->queries["test"] = "155";
	this->queries["anothertest"] = "testing string";

	// this->CGI = HTML;
	this->CGI = HTML;
	if (this->route == "/test.py")
		this->CGI = PYTHON;
	// PYTHON PHP
	this->body = "";

	this->isReqComplete = true;
}


