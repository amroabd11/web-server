#include "../inc/SyntaxError.hpp"

static std::string      trim(std::string& line)
{
        size_t a = line.find_first_not_of(" \t");
        size_t b = line.find_last_not_of(" \t");

        if (a == std::string::npos)
                return "";
        return line.substr(a, b- a + 1);
}

static	std::vector<str>	normalize(std::vector<str> content)
{
	 std::vector<str> out;
         for (size_t i =0; i < content.size(); i++)
         {
                 std::string line = content[i];
                 size_t pos = line.find('#');
                 if (pos != std::string::npos)
                         line = line.substr(0,pos);
                 line = trim(line);
                 if (!line.empty())
                         out.push_back(line);
         }
         return out;
}
//static	void	errors(std::vector<str> contents)
//{
//	for (size_t i= 0; i< contents.size() ;i++)
//	{
//		str line = contents[i];
//		size_t	pos = line.find('}');
//		if (pos != std::string::npos && pos != 0)
//			throw std::runtime_error("config: a block is defined by->context{\nsomething...\n}");
//		else if (pos == 0 && line != "}")
//			throw std::runtime_error("config: block ends by } no any additional text after it");
//	}
//}

static bool blocks_error(std::vector<str> contents)
{
	int	flag = 0;
	for (size_t i = 0;i <contents.size(); i++)
	{
		std::string	line = contents[i];
		if (line.find('{') != std::string::npos)
			flag++;
		if(line.find('}') != std::string::npos)
			flag--;
	}
	if (flag == 0)
		return false;
	return true;
}

SyntaxError::SyntaxError(std::vector<str> contents)
{
	std::vector<str>	normalized = normalize(contents);
//	errors(normalized);
	if (blocks_error(normalized))
		throw std::runtime_error("config: syntax error-> block missing {,}");
	file_contents = normalized;
}

std::vector<str> SyntaxError::getContents()
{
	return file_contents;
}

//static std::vector<str> split(str line)
//{
//	std::vector<str> out;
//	str token;
//	for (size_t i = 0; i < line.size(); i++)
//	{
//		char c = line[i];
//		if (c == ' ' || c == '\t' || c == ':' || c == '{' || c == '}')
//		{
//			if (!token.empty())
//			{
//				out.push_back(token);
//				token.clear();
//			}
//		}
//		else
//			token += c;
//	}
//	if (!token.empty())
//		out.push_back(token);
//	return out;
//}

Tokenizer::Tokenizer(std::vector<str>& contents)
{
	str current;
	for (size_t i = 0; i < contents.size(); i++)
	{
		const str& line = contents[i];
		for (size_t j = 0; j < line.size(); j++)
		{
			char c = line[j];
		//std::cout << current<<std::endl;
			if (c == '{' || c == '}')
			{
				if (!current.empty())
				{
					Token word_token(WORD, current);
					tokens.push_back(word_token);
					current.clear();
				}
				if (c == '{')
				{
					Token lToken(LBRACE, "{");
					tokens.push_back(lToken);
				}
				else if (c == '}')
				{
					Token rToken(RBRACE, "}");
					tokens.push_back(rToken);
				}
			}
			else if (c == ':')
			{
				if (!current.empty())
				{
					Token word_token(WORD, current);
					tokens.push_back(word_token);
					current.clear();
				}
				Token colon_token(COLON, ":");
				tokens.push_back(colon_token);
			}
			else if (c == ';')
			{
				if (!current.empty())
				{
					Token word_token(WORD, current);
					tokens.push_back(word_token);
					current.clear();
				}
				Token smi_colon(SEMI_COLON, ";");
				tokens.push_back(smi_colon);
			}
			else if (std::isspace(c))
			{
				if (!current.empty())
				{
					Token word_token(WORD, current);
					tokens.push_back(word_token);
					current.clear();
				}
			}
			else
				current += c;
		}
		if (!current.empty())
		{
			Token word_token(WORD,current);
			tokens.push_back(word_token);
			current.clear();
		}
	}
	if (!current.empty())
	{
		Token word_token(WORD, current);
		tokens.push_back(word_token);
	}
}

std::vector<Token>& Tokenizer::getVStokens()
{
	return tokens;
}

Token::Token(TokenType type, str tr)
{
	this->type  = type;
	this->value = tr;
}






