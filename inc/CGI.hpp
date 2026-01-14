
#ifndef CGI_HPP
#define CGI_HPP


class CGI
{
private:
	str		interpreter;

public:
	CGI(int cgi);
	~CGI();

	// utility
	int		prepareFd(HTTP_Req& request, str& file2Serv);
};

#endif

