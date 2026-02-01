#ifndef REQ_TOKENIZER_HPP
#define REQ_TOKENIZER_HPP

#include "typedefs.hpp"
#include "stdIncludes.hpp"

enum TkType
{
	OSP,
	RSP,
	BSP,
	WORD,
	COLON
};

struct ReqToken
{
	TkType _tk_type;
	str	value;
};

class	ReqTokenizer
{
	private:
	//	str	_header_end;
		std::vector<str> start_line;
		std::map<str,str> header_fields;
		std::vector<ReqToken> _req_tokens;
	public:
		ReqTokenizer(str &_raw_bytes);
//		void	*headers_error();
		str	error;
		str	handle_postReq(str&);
		class badReq : public std::exception {

			public:
				const char* what() const {
					return  "400 Bad Request";
				}
		};
		
};







#endif
