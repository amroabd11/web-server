
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

	ReqTokenizer _req_tokens(requestStr);
	method = _req_tokens.start_line[0];
	route = _req_tokens.start_line[1];
	version = _req_tokens.start_line[2];
	strStrm(headers["Content-Length"]) >> contentLength;
	strStrm(headers["Host"])>> _host_name;
	parsingerr = _req_tokens.error;
	//AA server MUST reject any received request message that contains whitespace between a header field name and colon with a response 400bad request

	this->isReqHeadComplete = true;
}



Chunk::Chunk()
{
	size = "0";
}
Chunk::~Chunk()
{
}
