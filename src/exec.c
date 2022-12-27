#include "pipex.h"

void ppx_exec(t_access *exe, t_arg *arg, char **envp)
{
	int fd[2];
	int	id1;
	int	id2;
//TODO ERR MANAGEMENT	
////dup2 
	if (pipe(fd) == -1) // fd 1 write, read fd 0
		return ; 
	id1 = fork();
	if (id1 == -1)
		return ;
	if (id1 == 0)
		execve(exe->exec1, arg->cmd1.tab, envp);//need to tredirect stout into the pipe to use the output of cmd1 in cmd2 then its donzo
	else
	{	
		wait(NULL);
		id2 = fork();
		if (id2 == -1)
			return ;
		if (id2 == 0)
		{	
			arg->cmd2.tab[arg->cmd2.size - 1] = //cmd1 out  
			execve(exe->exec2, arg->cmd2.tab, envp);
		}
	}
	wait(NULL);
}
