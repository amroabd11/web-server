
#include "../inc/Server.hpp"


// === CONSTRUCTOR ===
HTTP_Req::HTTP_Req()
{
	isComplete = false;
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

	this->method = "POST";
	this->route = "/index.html";
	this->version = "HTTP/1.1";

	this->headers["Host"] = "127.0.0.1:8201";
	this->headers["Accept-Language"] = "en-US,en;q=0.6";
	// ...
	this->body = "NEW CONTENT BABY";

	this->isComplete = true;
}


