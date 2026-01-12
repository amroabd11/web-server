#include "./../inc/Configs.hpp"


Config::Config(char *file)
{

//	(void)file;
	std::ifstream	nfile;
	std::vector<str>	content;
//	std::string	con;
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
			//con += line + "\n";
		}
		nfile.close();
		if (check_syntax_error(content))
			throw std::runtime_error("config file syntax checking error ");
		virtualServersParsing	vsparse;
		vsparse.port = 9080;
		vsparse.host = "localhost";
		config_vServers.push_back(vsparse);
	} catch(std::exception& e){
		std::cout << e.what()<<std::endl;
		throw	Server::somethingWentWrong();
	}
	//virtualServersParsing	vs1;// this are just for testing real ones will come from config file
	//vs1.port = 8090;
	//vs1.host = "10.12.7.3";
	//vs1.root = "/";

//	virtualServersParsing	vs2;
//	vs2.port = 8090;
//	vs2.host = "127.0.0.1";
//	vs2.root = "/home";
//	//vServers.push_back(vs1);
//	config_vServers.push_back(vs2);
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

static bool	semicolon_error(std::vector<str>& contents)
{
	for (size_t i = 0; i<contents.size(); i++)
	{
		std::string line = contents[i];
		if (line == "}")
			continue;
		if (line.find('{') != std::string::npos)
		{
			if (line.find(';') != std::string::npos)
				return true;
			continue;
		}
		//size_t	id = line.length();
		//size_t	id2 = line.find(';');
		//if (id2 == std::string::npos || id != id2)
		//	return true;
		if (*line.rbegin() != ';')
			return true;

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
		//throw std::runtime_error("blocks have a syntax error");
	if (quotes_error(normalized_content))
		return true;
	if (semicolon_error(normalized_content))
		return true;
	return false;
}








