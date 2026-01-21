
#include "../inc/Server.hpp"


// === CONSTRUCTOR ===
HTTP_Req::HTTP_Req()
{
	isReqHeadComplete = false;
	isReqBodyComplete = false;
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
	str			line;
	size_t		currPos, headerEnd, bodyStart;

	// RESET if new Rick 
	// if (this->isReqBodyComplete)
	// 	*this = HTTP_Req();

	if (this->isReqHeadComplete)
	{
		this->body = str(_rawBytes);
		return ;
	}
	

	requestStr += str(_rawBytes);
	headerEnd = requestStr.find(str(CRLF)+str(CRLF));
	if (headerEnd == str::npos)
		return ;

	bodyStart = headerEnd + 4;
	this->body = requestStr.substr(bodyStart);
	requestStr = requestStr.substr(0, bodyStart);

	std::cout << "--head--"<<  requestStr << "--\n--";
	std::cout << "--body--"<<  this->body << "--\n--";

	currPos = requestStr.find(str(CRLF));
	line = requestStr.substr(0, currPos);
	requestStr = requestStr.substr(currPos + 2, str::npos);

	strStrm	lineStream(line);
	std::getline(lineStream, this->method , ' ');
	std::getline(lineStream, this->route  , ' ');
	std::getline(lineStream, this->version, ' ');


	while (true)
	{
		if (requestStr == str(CRLF))
			break ;
		currPos = requestStr.find(str(CRLF));
		line = requestStr.substr(0, currPos);
		requestStr = requestStr.substr(currPos + 2, str::npos);

		// headers now
		ssize_t	pos = line.find(": ");
		str		key = line.substr(0, pos);
		str		value = line.substr(pos+2, str::npos);
		this->headers[key] = value;
	}

	strStrm(this->headers["Content-Length"]) >> this->contentLength;

	this->isReqHeadComplete = true;
}



Chunk::Chunk()
{
	size = "0";
}
Chunk::~Chunk()
{
}
