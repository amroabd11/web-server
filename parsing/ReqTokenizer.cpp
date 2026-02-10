#include "../inc/ReqTokenizer.hpp"


static str firstLine_syntax(std::vector<str> &startLine)
{
	
	if (startLine[0] != "POST" && startLine[0] != "GET" && startLine[0] != "DELETE")
		return HTTP_405;
	if (startLine[1].find("./") != std::string::npos || startLine[1].find("..") != std::string::npos)
		return HTTP_404;
	if (startLine[2] != "HTTP/1.1")
		return HTTP_400;
	return HTTP_000;
}

//str	ReqTokenizer::handle_postReq(str& headers)
//{
//	
//}
//
//void	ReqTokenizer::handle_getReq(size_t& pos)
//{
//	
//}

ReqTokenizer::ReqTokenizer(str &_bytes)
{
	size_t	_h_end_pos = _bytes.find(str(CRLF) + str(CRLF));
	_h_end_pos += 4;

	error = HTTP_000;
	size_t curr_pos = _bytes.find("\r\n");
	if (curr_pos== str::npos)
		throw std::runtime_error("errrrrrrror");
	str	startline = _bytes.substr(0, curr_pos);
	
	for (size_t i = 0; i < startline.size(); i++)
	{
		size_t start = i;
		if ((i+1 < startline.size()) && (startline[i] == '\r' && startline[i +1] == '\n'))
			break ;
		if (startline[0] == ' ' || startline[0] == '\t')
		{
			error = HTTP_400;
			 throw std::runtime_error("spaces in the first of reqLine");
		}
		if (IS_SP(startline[i]))
			continue;
		while (!IS_SP(startline[i]))
			i++;
		start_line.push_back(startline.substr(start, i-start));
	}

	if (start_line.size() != 3)
	{
		error = HTTP_400;
		throw std::runtime_error("error in request line form");
	}
	error = firstLine_syntax(start_line);
//	std::cout << error<<std::endl;
	if (error != HTTP_000)
		 throw std::runtime_error("error in firstLine_syntax");
	str	headers = _bytes.substr(curr_pos + 2, _h_end_pos);

	if (!tokenized(headers))
	{
		throw std::runtime_error("tokenizing error");
	}

	for (size_t i = 0; i< _req_tokens.size(); i++)
	{
		str fieldName;
//		std::cout << _req_tokens[i].value<< "-----------> type: "<< _req_tokens[i]._tk_type<<std::endl;
	
		if ((i+2 < _req_tokens.size() && i+1 < _req_tokens.size()) && (_req_tokens[i]._tk_type == WORD1 && _req_tokens[i+1]._tk_type == COLON1 && _req_tokens[i+2]._tk_type == OSP))
		{
			fieldName = _req_tokens[i].value;
			i+=3;
		}
	//	else if(_req_tokens[i]._tk_type == RSP)
	//		continue;
		else if (_req_tokens[i]._tk_type == BSP)
			break;
		else
		{
			throw std::runtime_error("the only handled header's syntax as: field:OSP value OSP RSP");
		}
		if (_req_tokens[i]._tk_type == WORD1)
			header_fields[fieldName] = _req_tokens[i].value;
		else
			throw std::runtime_error("error: correctSYNTAX:headers token:OSPvalueOSPcrlf");
	}
//	body = _bytes.substr(_h_end_pos);
//	if (start_line[0] == "POST")
//	{
//		error = handle_postReq(headers);
//	}
//	else if (start_line[0] == "GET")
//		handle_getReq(curr_pos+2);	
//	else if (start_line[0] == "DELETE")
//		handle_deleteReq();
}
ReqTokenizer::~ReqTokenizer()
{}

bool ReqTokenizer::tokenized(str& headers)
{
//	std::cout << headers.size()<<std::endl;
	for(size_t i = 0; i<headers.size();i++)
	{
		if (i +3<headers.size() && headers[i] == '\r' && headers[i+1] == '\n' && headers[i+2] == '\r' && headers[i+3] == '\n')
		{
			ReqToken crlfToken(BSP, "\r\n\r\n");
			_req_tokens.push_back(crlfToken);
			return true;
		}
		size_t crlf_pos = headers.find("\r\n",i);
		if (crlf_pos == str::npos)
		{
			error = HTTP_400;
			return false;
		}
		str line = headers.substr(i, crlf_pos-i);
		if (line.empty())
			return true;
		if(IS_SP(line[0]))
		{
			error = HTTP_400;
			return false;
		}
		size_t cur_pos = line.find(':');
		if (cur_pos == str::npos)
		{
			error = HTTP_400;
			return false;
		}
		
		str token = line.substr(0, cur_pos);
		if (token.find(' ') != str::npos)
		{
			error = HTTP_400;
			return false;
		}
		ReqToken wordToken(WORD1,token);
		_req_tokens.push_back(wordToken);
		if (cur_pos != str::npos)
		{
			ReqToken colon(COLON1, ":");
			_req_tokens.push_back(colon);
		}
		str value = line.substr(cur_pos+1, crlf_pos-i);
		//std::cout << value<<std::endl;
		for (size_t j =0; j<value.size(); j++)
		{
			size_t start = j;
			if (value[j] == ' ')
			{
				while (j<value.size() && value[j] == ' ')
					j++;
				ReqToken spaces(OSP, value.substr(start, j-start));
				_req_tokens.push_back(spaces);
				j--;
			}
			else
			{
			//	if (value[j] == ':')
			//		start+=1;
				while (j<value.size())
					j++;
		//		std::cout << value.substr(start, j)<<std::endl;
				ReqToken wordValue(WORD1, value.substr(start, j-start));
				_req_tokens.push_back(wordValue);
			}
			//if (j+2 == value.size() && value[j] == '\r' && value[j+1]=='\n')
			//{
			//	ReqToken ReqSep(RSP, "\r\n");
			//	_req_tokens.push_back(ReqSep);
			//	j+=2;
			//}
		}
		i=crlf_pos+1;
	}
	return true;
}

std::vector<str> ReqTokenizer::getReqLine()
{
	return start_line;
}

std::map<str, str> ReqTokenizer::getHeaders()
{
	return header_fields;
}

ReqToken::ReqToken(TkType type, str value)
{
	_tk_type = type;
	this->value = value;
}
