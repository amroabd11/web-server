#include "../inc/ReqTokenizer.hpp"


static str firstLine_syntax(std::vector<str> &startLine)
{
	str error = "HTTP_000";
	
	if (startLine[0] != "POST" && startLine[0] != "GET" && startLine[0] != "DELETE")
		return str="HTTP_405 unsupported method";
	if (startLine[1].find(".") != std::npos && startLine[1].find("..") != std::npos)
		return str = "HTTP_404 Forbidden access";
	if (startLine[2] != "HTTP/1.1")
		return str = "HTTP_400 Unkown http version";
	// here i need to implement error of the first line of header 
	//regarding case sensitivity and size of parts in the line. also are the methods valid or not , also checking the http version if it is supported and checking the route TODO reading rfc for uri standards i should follow

	return error;
	//METHOD SP request-target SP HTTP-version CRLF
}

str	ReqTokenizer::handle_postReq(str& headers)
{
	
}

ReqTokenizer::ReqTokenizer(str &_bytes)
{
	size_t	_h_end_pos = bytes.find(str(CRLF) + str(CRLF));
	_h_end_pos += 4;

	error = "HTTP_000";
	size_t curr_pos = bytes.find(str(CRLF));
	str	startline = bytes.substr(0, curr_pos);
	for (size_t i = 0; i < startline.length(); i++)
	{
		size_t start = i;
		if (startline[i] == '\r' && startline[i +1] == '\n')
			break ;
		if (startline[0] == ' ' || startline[0] == '\t')
		{
			error = "HTTP_400";
			return ;///throw badReq();
		}
		while (startline[i] == ' ')
			i++;
		start_line.push_back(startline.substr(start, i));
	}
	 if (start_line.size() != 3)
	 {
		 error = "HTTP_400";
		 return ;//throw badReq();
	 }
	 error = firstLine_syntax(start_line);
	 if (error != "HTTP_000")
		 return ;
	str	headers = bytes.substr(curr_pos + 2, _h_end_pos);
	if (start_line[0] == "POST")
	{
		error = handle_postReq(headers);
	}
	else if (start_line[0] == "GET")
		handle_getReq();	
	else if (start_line[0] == "DELETE")
		handle_deleteReq();
}
