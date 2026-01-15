#include "./../inc/Configs.hpp"


Config::Config(char *file)
{

	std::ifstream	nfile;
	std::vector<str>	content;
	try{
		nfile.open(file, std::ifstream::in);
		if (!nfile)
			throw std::runtime_error("config file stream open failed");
		std::string	line;
		while(std::getline(nfile, line))
		{
			if (line.empty())
				continue;
			content.push_back(line);
		}
		nfile.close();
		if (check_syntax_error(content))
			throw std::runtime_error("config file syntax checking error ");
	//	std::cout << config_vServers[0].port<<std::endl; 
	//	std::cout << config_vServers[0].host<<std::endl; 
		//std::cout << config_vServers[0].block[0]<<std::endl; 
		//std::cout << config_vServers.size()<<std::endl;
	//	std::map<str,str>& loc = config_vServers[0].locations[0];
	//	std::map<str, str>::iterator it = loc.begin();
	//	std::cout << it->first << "=" << it->second<<std::endl;
		//std::cout << "++++++++++===============\n" ;
		//std::cout << config_vServers[0].locations[0]["index"] << std::endl;
		//std::cout << config_vServers[0].locations.size() << std::endl;
		//tokenize_file_contents(content);
	} catch(std::exception& e){
		std::cout << e.what()<<std::endl;
		throw	Server::somethingWentWrong();
	}
}

void	Config::tokenize_file_contents(std::vector<str>& content)
{
	for(size_t i = 0; i<content.size(); i++)
	{
		//std::cout << content[i]<<std::endl;
		if (!content[i].empty() && content[i] != "server{")
			throw std::runtime_error("allowed contexts are servers: you provided unkown context in config file");
		if (content[i] != "server{")
			continue;
		std::vector<str>	block;
		std::map<str, str> locations;
		virtualServersParsing	vsblock;
		std::vector<std::map<str,str> > blockOFlocations;
		bool	inside = true;
		for (++i; i < content.size(); i++)
		{
			std::string& line = content[i];
			if (!inside)
				break;
			if (line.find('}') != std::string::npos)
			{
				inside = false;
				break ;
			}
			if (line == "location{")
			{
				bool inside2 = true;
				for(;i < content.size();i++)
				{
					line = content[i];
					if (line == "location{")
						continue;
					//std::cout << line<<std::endl;
					if (!inside2)
						break;
					if (line.find('}') != std::string::npos)
					{
						inside2 = false;
						break;
					}
					//std::cout << line<<std::endl;
					if (line.find('{') != std::string::npos)
						throw std::runtime_error("config file:unkwon directive inside location");
					// fill_locations();
					std::vector<str> tokens = TokenizServerDirectives::split(line, "\t ");
					if (tokens.size() != 2)
						throw std::runtime_error("config file: you are allowed for one value per rule in each directive");
					locations.insert(std::pair<str, str>(tokens[0],tokens[1]));//test
					//TokenizServerDirectives::insert_locations(locations, tokens[0], tokens[1]);
						//here i need to init a vector for the body of location and a map 
				}
				blockOFlocations.push_back(locations);
			}
			if (line.find('{') != std::string::npos && line != "location{")
				throw std::runtime_error("config file:unkown directive in server context ");
			std::vector<str> tokens = TokenizServerDirectives::split(line, "\t ");
		//	if (tokens.size() != 2)
		//		throw std::runtime_error("config file: you are allowed only for pairs of key and value per directive");
			if (tokens[0] == "listen")
				vsblock.port = static_cast<uint16_t>(std::strtoul(tokens[1].c_str(), 0, 10));
			block.push_back(line);
		}
		//virtualServersParsing	vsblock;
		vsblock.block = block;
		vsblock.locations = blockOFlocations;
		vsblock.host = "localhost";
		config_vServers.push_back(vsblock);
	}
}

static	bool	blocks_error(std::vector<str> &v_contents)
{
	int	flag = 0;
	for (size_t i = 0; i < v_contents.size(); i++)
	{
		std::string 	line = v_contents[i];
		if (line.find('{') != std::string::npos)
			flag++;
		if (line.find('}') != std::string::npos)
			flag--;
	}
	if (flag == 0)
		return false;
	return true;
}

static bool	quotes_error(std::vector<str>& contents)
{
	int	flag = 0;
	for (size_t i = 0; i < contents.size(); i++)
	{
		std::string line = contents[i];
		if (line.find('"') != std::string::npos)
			flag++;
		if(line.find('"') != std::string::npos)
			flag--;
	}
	if (flag == 0)
		return false;
	return true;
}

static bool	errors(std::vector<str>& contents)
{
	std::string allowed = "{} /#_.:\"'\t";
	for (size_t i = 0; i<contents.size(); i++)
	{
		std::string line = contents[i];
		for (size_t j=0; j<line.size();j++)
		{
			if (std::isalnum(line[j]))
				continue;
			if (allowed.find(line[j]) != std::string::npos)
				continue;
			return true;
		}
	}
	return false;
}

static std::string	trim(std::string& line)
{
	size_t a = line.find_first_not_of(" \t");
	size_t b = line.find_last_not_of(" \t");

	if (a == std::string::npos)
		return "";
	return line.substr(a, b- a + 1);
}

static	std::vector<str> normalize(std::vector<str> &content)
{
	std::vector<std::string> out;
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

bool	Config::check_syntax_error(std::vector<str>	&content)
{
	// i may need to clean comments from the fileContents 
	std::vector<str> normalized_content = normalize(content);
	if (blocks_error(normalized_content))
		return true;
	if (quotes_error(normalized_content))
		return true;
	if (errors(normalized_content))
		return true;
	tokenize_file_contents(normalized_content);
	return false;
}








	(void)file;
	virtualServersParsing	vs1;// this are just for testing real ones will come from config file
	srand(time(NULL));
	vs1.port = rand();
	vs1.host = "127.0.0.1";
	vs1.root = "/home/ioulkhir/Desktop/WEBserv";
	vServers.push_back(vs1);


	// virtualServersParsing	vs2;
	// vs2.port = 8080;
	// vs2.host = "localhost";
	// vs2.root = "/home";
	// vServers.push_back(vs2);
}
