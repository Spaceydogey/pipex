/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:02:04 by hdelmas           #+#    #+#             */
/*   Updated: 2022/12/27 22:27:53 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int ppx_exec(t_access *exe, t_arg *arg, char **envp)
{
	int 	fd[2];
	int		id1;
	int		id2;
	char	*r_str;
	int		f_fd;
//TODO ERR MANAGEMENT	

	if (pipe(fd) == -1) // fd 1 write, read fd 0
		return (1); 
	id1 = fork();
	if (id1 == -1)
		return (2);
	if (id1 == 0)
	{
		close(fd[0]);
		f_fd = open(arg->file.input, O_RDONLY);
		if (f_fd == -1)
			return (6);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (5);		
		if (dup2(f_fd, STDIN_FILENO) == -1)
			return (5);
		close(fd[1]);
		close(f_fd);
		execve(exe->exec1, arg->cmd1.tab, envp);//need to tredirect stout into the pipe to use the output of cmd1 in cmd2 then its donzo
	}
	else
	{	
		wait(NULL);
		id2 = fork();
		if (id2 == -1)
			return (3);
		if (id2 == 0)
		{			
			close(fd[1]);
			if (dup2(fd[0], STDIN_FILENO) == -1)
				return (5);
			close(fd[0]);
			f_fd = open(arg->file.output, O_WRONLY | O_TRUNC | O_CREAT, 0666);
			if (f_fd == -1)
				return (6);
			if (dup2(f_fd, STDOUT_FILENO) == -1)
				return (5);
			close(f_fd);
			execve(exe->exec2, arg->cmd2.tab, envp);
		}
		//wait(NULL); ??? 
	}
	return (0);
}
