
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
	this->requestStr = other.requestStr;
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
		std::cout << "\n--this body when headIsComplete:::::  "<<body<< "\nb++++++++++\n"<<std::endl;
		return ;
	}

	std::cout << "||||||||||" << std::endl;	
	std::cout << _rawBytes << std::endl;	
	std::cout << "||||||||||" << std::endl;	

	requestStr += str(_rawBytes); // THIS  is for chuncked requests
	size_t _header_end = requestStr.find(str(CRLF) + str(CRLF)); 
	if (_header_end == str::npos)
		return ;
	try{
		ReqTokenizer _req_tokens(requestStr);
		method = _req_tokens.getReqLine()[0];
		route = _req_tokens.getReqLine()[1];
		version = _req_tokens.getReqLine()[2];


		std::cout << "\n#######this is the method :  " << method <<std::endl;
		std::cout << "*******this is the route :  " << route <<std::endl;
		std::cout << "------ thsi is the version :  "<< version <<std::endl;

		_host_name = _req_tokens.getHeaders()["Host"];
		if (_host_name.empty())
		{
			parsingerr = HTTP_400;
			return ;
		}
		headers = _req_tokens.getHeaders();

	//	std::cout << "this are headers --------------------------------------------"<<std::endl;
	//	std::map<str, str>::iterator it;
	//	for (it = headers.begin(); it!= headers.end(); ++it)
	//	{
	//		std::cout << it->first << "--> "<<it->second<<std::endl;
	//	}
	//	std::cout << "this is the end ----------------------------------------------"<<std::endl;

		strStrm(_req_tokens.getHeaders()["Content-Length"]) >> contentLength;
		parsingerr = _req_tokens.error;
	}
	catch(const std::exception& e){
		std::cout << e.what() <<std::endl;
		return ;
	}

	this->isReqHeadComplete = true;
	std::cout << "\nwssal lakhar daba rah true \n";
}



Chunk::Chunk()
{
	size = "0";
}
Chunk::~Chunk()
{
}
