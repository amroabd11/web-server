
#include "./../inc/Server.hpp"

CGI::CGI(int cgi)
{
	if (cgi == PYTHON)
		interpreter = "/usr/bin/python";
	else if (cgi == NODEJS)
		interpreter = "/usr/bin/cat";
	else
		interpreter = "";
}
CGI::~CGI() { }

// Utility
int		CGI::prepareFd(HTTP_Req& request, str& file2Serv)
{
	char		*envp[request.queries.size()+1];
	int			my_pipe[2];
	str			tmp;
	int			fd;
	char		*argv[3];

	if (this->interpreter.empty())
		return open(file2Serv.c_str(), O_RDONLY);

	if (pipe(my_pipe) < 0)
		somethingWentWrongFunc("pipe");
	fd = my_pipe[0];
	int i = 0;
	for (QueriesIt it = request.queries.begin(); it != request.queries.end(); ++it)
	{

		tmp = it->first + "=" + it->second;

		envp[i++] = (char *)(tmp.c_str());
		std::cout << "envp[i] --> " << i << envp[i-1] << "\n";
	}
	envp[i] = NULL;

	int pid = fork();
	if (pid)
	{
		// parent
		close(my_pipe[1]);
		return fd;
	}
	else
	{
		// child
		close(my_pipe[0]);
		dup2(my_pipe[1], STDOUT_FILENO);
		close(my_pipe[1]);

		argv[0] = (char*)(interpreter.c_str());
		argv[1] = (char*)(file2Serv.c_str());
		argv[2] = NULL;

		execve(this->interpreter.c_str(), argv, envp);
		somethingWentWrongFunc("execve");
		return fd;
	}
	return fd;
}

