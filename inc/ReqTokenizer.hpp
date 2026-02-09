#ifndef REQ_TOKENIZER_HPP
#define REQ_TOKENIZER_HPP

#include "typedefs.hpp"
#include "stdIncludes.hpp"

enum TkType
{
	OSP,
	RSP,
	BSP,
	WORD1,
	COLON1
};

class ReqToken
{
public:
	ReqToken(TkType, str);
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
		~ReqTokenizer();
//		void	*headers_error();
		str	error;
		str	handle_postReq(str&);
		void	handle_getReq(size_t& );
		bool	tokenized(str&);
		std::vector<str> getReqLine();
		std::map<str, str> getHeaders();
//		class badReq : public std::exception {
//
//			public:
//				virtual const char* what() const {
//					return  "syntax error in request parsing";
//				}
//		};
		
};







#endif
