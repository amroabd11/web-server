#ifndef PARSER_HPP
#define PARSER_HPP

#include "stdIncludes.hpp"
#include "typedefs.hpp"
#include "Configs.hpp"
#include "SyntaxError.hpp"

struct location;
struct virtualServersParsing;


class Parser
{
	public:
		Parser(std::vector<virtualServersParsing> &vservers, std::vector<Token> &block);
		typedef void(*handler_t)(virtualServersParsing&, size_t &, std::vector<Token>&);
		typedef void(*handler_location_t)(location&, size_t &, std::vector<Token>&);
		static void	parse_directive(std::vector<Token> &, location&);	
		static std::map<std::string, handler_location_t> init_location_handler();
		static std::map<std::string, handler_t> init_server_handler();
	
};


#endif
