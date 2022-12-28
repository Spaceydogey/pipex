/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:02:04 by hdelmas           #+#    #+#             */
/*   Updated: 2022/12/28 18:19:46 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	exec_cmd1(char *exec, t_arg *arg, char **envp, int p_fd[2])
{
	int		f_fd;

	close(p_fd[0]);
	f_fd = open(arg->file.input, O_RDONLY);
	if (f_fd == -1)
		return (errno);
	if (dup2(p_fd[1], STDOUT_FILENO) == -1)
		return (errno);//close on error
	if (dup2(f_fd, STDIN_FILENO) == -1)
		return (errno);
	close(p_fd[1]);
	close(f_fd);
	return (execve(exec, arg->cmd1.tab, envp));
}

static int exec_cmd2(char *exec, t_arg *arg, char **envp, int p_fd[2])
{
	int		f_fd;

	close(p_fd[1]);
	if (dup2(p_fd[0], STDIN_FILENO) == -1)
		return (errno);
	close(p_fd[0]);
	f_fd = open(arg->file.output, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (f_fd == -1)
		return (errno);//close on error
	if (dup2(f_fd, STDOUT_FILENO) == -1)
		return (errno);
	close(f_fd);
	return (execve(exec, arg->cmd2.tab, envp));
}

int	ppx_exec(t_access *exe, t_arg *arg, char **envp)
{
	int		p_fd[2];
	int		id1;
	int		id2;
	char	*r_str;
	int		res;

	res = 0;
	if (pipe(p_fd) == -1)// fd 1 write, read fd 0
		return (errno);
	id1 = fork();
	if (id1 == -1)
		return (errno);
	if (id1 == 0)
	{
		if (exec_cmd1(exe->exec1, arg, envp, p_fd) == -1)
			res = errno;
	}
	else
	{	
		wait(NULL);
		id2 = fork();
		if (id2 == -1)
			return (errno);
		if (id2 == 0)
			if (exec_cmd2(exe->exec2, arg, envp, p_fd) == -1)
				res = errno;
	}
	return (res);
}
