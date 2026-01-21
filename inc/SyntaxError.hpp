#ifndef	SYNTAX_ERROR_HPP
# define SYNTAX_ERROR_HPP

#include "stdIncludes.hpp"
#include "stdIncludes.hpp"
#include "typedefs.hpp"

struct Directives
{
	str name;
	std::vector<str> args;
};

struct Context
{
	std::vector<str> args;
	std::vector<Directives> directives;
	std::vector<Context> children;
};

enum TokenType
{
	WORD,
	LBRACE,
	COLON,
	SEMI_COLON,
	RBRACE
};

class Token
{
	public:
		Token(TokenType, str);
		TokenType type;
		str value;

};

class	Tokenizer
{

	private:
		std::vector<Token>	tokens;
	public:
		std::vector<Token>& getVStokens();
		Tokenizer(std::vector<str>&);
		
};


class	SyntaxError
{
	private:
		std::vector<str> file_contents;
	public:
		SyntaxError(std::vector<str>);
		std::vector<str> getContents();
	
};

#endif
