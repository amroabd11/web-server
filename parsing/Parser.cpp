#include "./../inc/Parser.hpp"

void expect(TokenType expected, Token &tok)
{
	if(tok.type != expected)
		throw std::runtime_error("confg syntax error near: "+tok.value);
}

void	parse_listen(virtualServersParsing& vser, size_t &i, std::vector<Token>& block)
{
	expect(WORD, block[++i]);
	vser.host = block[i].value;
	expect(COLON, block[++i]);
	expect(WORD, block[++i]);
	vser.port = std::atoi(block[i].value.c_str());
}

void parse_root(virtualServersParsing& vser, size_t &i, std::vector<Token>& block)
{
	expect(WORD, block[++i]);
	vser.root = block[i].value;
}

void	parse_autoindex(virtualServersParsing& vser, size_t &i,std::vector<Token>& block)
{
	expect(WORD, block[++i]);
	//vser.autoindex = vser.block[i].value;
	if (block[i].value == "off")
		vser.autoindex = false;
	else
		vser.autoindex = true;
}

void	parse_error(virtualServersParsing& vser, size_t &i, std::vector<Token>& block)
{
	expect(WORD, block[++i]);
	vser.error = block[i].value;
}

void	parse_methods(virtualServersParsing& vser, size_t &i, std::vector<Token>& block)
{
	expect(WORD, block[++i]);
	while (i + 1 < block.size() && block[i+1].type == WORD)
		vser.methods.push_back(block[++i].value);
}

void	parse_index(virtualServersParsing& vser, size_t &i, std::vector<Token>& block)
{
	expect(WORD, block[++i]);
	while (i + 1 < block.size() && block[i+1].type == WORD)
		vser.index.push_back(block[++i].value);
}

void	parse_return(virtualServersParsing& vser, size_t& i, std::vector<Token>& block)
{
	expect (WORD, block[++i]);
	vser.redir = block[i].value;
}

void	parse_body(virtualServersParsing& vser, size_t &i, std::vector<Token>& block)
{
	expect(WORD, block[++i]);
	vser.body_size = std::strtoul(block[i].value.c_str(), NULL, 0);
}

void	parse_cgi(virtualServersParsing& vser, size_t &i, std::vector<Token>& block)
{
	expect(WORD, block[++i]);
	while (i + 1 < block.size() && block[i+1].type == WORD)
		vser.cgi.push_back(block[++i].value);
}


void	parse_location_route(location& loc, size_t& i, std::vector<Token>& tok_block)
{
	expect(WORD, tok_block[++i]);
	loc.route = tok_block[i].value;
}

void	parse_location_root(location& loc, size_t& i, std::vector<Token>& tok_block)
{
	expect(WORD, tok_block[++i]);
	loc.root = tok_block[i].value;
}


void	parse_location_error(location& loc, size_t& i, std::vector<Token>& tok_block)
{
	expect(WORD, tok_block[++i]);
	loc.error = tok_block[i].value;
}


void	parse_location_autoindex(location& loc, size_t& i, std::vector<Token>& tok_block)
{
	expect(WORD, tok_block[++i]);
	if (tok_block[i].value == "off")
		loc.autoindex = false;
	else 
		loc.autoindex = true;
}
void	parse_location_methods(location& loc, size_t& i, std::vector<Token>& tok_block)
{
	expect(WORD, tok_block[++i]);
	while (i +1 < tok_block.size() && tok_block[i].type == WORD)
		loc.methods.push_back(tok_block[++i].value);
}
void	parse_location_return(location& loc, size_t& i, std::vector<Token>& tok_block)
{
	expect(WORD, tok_block[++i]);
	loc.redir = tok_block[i].value;
}
void	parse_location_index(location& loc, size_t& i, std::vector<Token>& tok_block)
{
	expect(WORD, tok_block[++i]);
	while (i +1 < tok_block.size() && tok_block[i].type == WORD)
		loc.index.push_back(tok_block[++i].value);
}

void 	parse_location_body(location& loc, size_t& i, std::vector<Token>& tok_block)
{
	expect(WORD, tok_block[++i]);
	loc.body_size = std::strtoul(tok_block[i].value.c_str(), NULL, 0);

}
std::map<std::string, Parser::handler_location_t> Parser::init_location_handler()
{
	std::map<std::string, handler_location_t> handlers;
	handlers["route"] = parse_location_route;
	//handlers["host"] = parse_host;
	handlers["root"] = parse_location_root;
	handlers["autoindex"] = parse_location_autoindex;
	handlers["error"] = parse_location_error;
	handlers["methods"] = parse_location_methods;
	handlers["return"] = parse_location_return;
	handlers["index"] = parse_location_index;
	handlers["clientBodyMaxSize"] = parse_location_body;
	//handlers["cgi"] = parse_cgi;

	return handlers;
}
std::map<std::string, Parser::handler_t> Parser::init_server_handler()
{
	std::map<std::string, handler_t> handlers;
	handlers["listen"] = parse_listen;
	//handlers["host"] = parse_host;
	handlers["root"] = parse_root;
	handlers["autoindex"] = parse_autoindex;
	handlers["error"] = parse_error;
	handlers["methods"] = parse_methods;
	handlers["return"] = parse_return;
	handlers["index"] = parse_index;
	handlers["clientBodyMaxSize"] = parse_body;
	handlers["cgi"] = parse_cgi;

	return handlers;
}

void Parser::parse_directive(std::vector<Token> &block, location &loc)
{
	std::map<std::string, handler_location_t> handlers = Parser::init_location_handler();
	for(size_t i = 0; i<block.size(); i++)
	{
		if (block[i].type != WORD)
			continue;
		std::map<str, handler_location_t>::iterator it = handlers.find(block[i].value);
		if (it == handlers.end())
			throw std::runtime_error("invalid location directive in config file");
		it->second(loc, i, block);
	}
}

static void	parse_locations(virtualServersParsing& vser, size_t &i, std::vector<Token>& block)
{
	location loc;
	if (block[i].type != WORD || block[i].value != "location")
		throw std::runtime_error("expected location dir");
	if (block[++i].type != WORD)
		throw std::runtime_error("expected location path");
	loc.route = block[i].value;
	if (block[++i].type != LBRACE)
		throw std::runtime_error("expected '{' after path");
	std::vector<Token> innerBlock;
	int flag = 1;
	while( ++i < block.size() && flag > 0)
	{
		if (block[i].type == LBRACE)
			flag++;
		else if (block[i].type == RBRACE)
			flag--;
		if (flag > 0)
			innerBlock.push_back(block[i]);
	}
	if (flag !=0)
		throw std::runtime_error("unclosed location block");
	Parser::parse_directive(innerBlock, loc);
	vser.locations.push_back(loc);
	std::cout << "looooo"<<std::endl;
}

Parser::Parser(std::vector<virtualServersParsing> &vservers, std::vector<Token> &tokensBlock) //TODO it should be reimplemented 
{
	std::vector<Token> &block = tokensBlock;
	std::map<std::string, handler_t> handlers = init_server_handler();
	for(size_t i = 0; i<block.size(); i++)
	{
		std::cout << block[i].value << block[i+1].value<< std::endl;
		if (block[i].value == "server")
		{
			std::cout << block[i].value << "--->"<<block[i].type<<std::endl;
			virtualServersParsing vser;
			if (block[++i].type != LBRACE)
				throw std::runtime_error("expected {' after server");
			while (++i < block.size() && block[i].type != RBRACE)
			{
				if (block[i].value == "location")
				{
			//std::cout << block[i].value << "--->"<<block[i].type<<std::endl;
					parse_locations(vser, i, block);
					continue;
				}
				if(block[i].type == WORD)
				{
			std::cout << block[i].value << "--->"<<block[i].type<<std::endl;
					std::map<str, handler_t>::iterator it = handlers.find(block[i].value);
					if (it == handlers.end())
						throw std::runtime_error("unknown directive in config file");
					it->second(vser, i,block);
			std::cout << block[i].value << "--->"<<block[i].type<<std::endl;
				}
			}
			vservers.push_back(vser);
		}
	}
}
