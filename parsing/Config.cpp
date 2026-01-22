#include "./../inc/Configs.hpp"

Config::Config()
{
	virtualServersParsing defaultvs;
	memset(&defaultvs, 0, sizeof(defaultvs));
	defaultvs.port = 8080;
	defaultvs.host = "0.0.0.0";
	defaultvs.root = "/app";
	//defaultvs.error = "/error_pages";
	defaultvs.autoindex = false;
//	defaultvs.error = NULL;
//	defaultvs.
}


Config::Config(char *file)
{

	std::ifstream	nfile;
	std::vector<str>	content;
	try{
		nfile.open(file, std::ifstream::in);
		if (!nfile)
			throw std::runtime_error("config: opening failed");
		std::string	line;
		while(std::getline(nfile, line))
		{
			if (line.empty() || line == "\n")
				continue;
			content.push_back(line);
		}
		nfile.close();
		SyntaxError syntax_error(content);
		file_contents = syntax_error.getContents();
		Tokenizer tokens(file_contents);
		vser_struct.block = tokens.getVStokens();
		//std::cout << tokens.getVStokens()[3].value<<std::endl;
		//config_vServers;
		//std::cout << tokens.getVStokens()[4].value<<"----" << tokens.getVStokens()[5].value<< std::endl;
	//	config_vServers.block = tokens.getVStokens();
//		std::cout << tokens.getVStokens()[17].value<<std::endl;
		Parser parse_tokens(config_vServers, tokens.getVStokens());
	} catch(std::exception& e){
		std::cout <<"config parser: "<< e.what()<<std::endl;
		throw	Server::somethingWentWrong();
	}
}

std::vector<str> Config::getContents() { return file_contents; }

const std::vector<virtualServersParsing> Config::getVservers() const
{
	return config_vServers;
}

//virtualServersParsing Config::getTokensBlock()
//{
//	return vser_struct ;
//}

