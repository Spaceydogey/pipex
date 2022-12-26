#include "pipex.h"

void ppx_exec(t_access *exe, t_arg *arg, char **envp)
{
	int	id;
	int fd[2];
//TODO ERR MANAGEMENT	
////dup2 
	if (pipe(fd) == -1); // fd 1 write, read fd 0
		return ; 
	id = fork();
	if (id == -1)
		return ;
	if (id == 0)
	{	//wait cmd1
		//arg->cmd2.tab[arg->cmd2.size - 1] = //cmd1 out  
		execve(exe->exec1, arg->cmd2.tab, envp);
	}
	else
	{	
		id = fork();
		if (id == -1)
			return ;
		if (id == 0)
			execve(exe->exec1, arg->cmd1.tab, envp);//need to tredirect stout into the pipe to use the output of cmd1 in cmd2 then its donzo
	}
	wait(NULL);
}
