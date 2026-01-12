#include "./../inc/ConfigParser.hpp"


//HttpTrafficParse::HttpTrafficParse(char*	file)
//{
//	std::ifstream	nfile;
//	//file.exceptions(std::ifstream::failbit | std::ifstream::badbit)
//	try{
//		nfile.open(file, std::ifstream::in);
//		if (!nfile)
//			throw	std::runtime_error("file stream open failed");
//		std::string	line;
//		std::string	content;
//		while(std::getline(nfile, line))
//		{
//			if (!line.empty())
//				content += line + "\n";
//		}
//		nfile.close();
//
//		virtualServersParsing vsParse;
//		vsParse.port = 9080;
//		vsParse.host = "localhost";
//		Config::config_vServers.push_back(vsParse);
//	}
//	catch(std::exception& e)
//	{
//		std::cout << "configParser failed: "<< e.what()<<std::endl;
//		throw	Server::somethingWentWrong();
//	}
//}

