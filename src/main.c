/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:35:01 by hdelmas           #+#    #+#             */
/*   Updated: 2022/12/23 15:43:49 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	cmd_init(char *str)
{
	t_cmd	res;
	char	**tab;

	res.cmd = NULL;
	tab = ft_split(str, ' ');
	if (!tab)
		return (res);
	res.cmd = tab[0];
	res.flags = &tab[1];
	res.tab = tab;
	return (res);
}

t_arg	*arg_init(char **av)
{
	//free all on return if malloc fails
	t_arg	*res;

	res = malloc(sizeof(t_arg));
	if (!res)
		return (NULL);
	res->file.input = ft_strdup(av[1]);
	if (!res->file.input)
		return (NULL);
	res->file.output = ft_strdup(av[4]);	
	if (!res->file.output)
		return (NULL);
	res->cmd1 = cmd_init(av[2]);
	if (!res->cmd1.cmd)
		return (NULL);
	res->cmd2 = cmd_init(av[3]);
	if (!res->cmd2.cmd)
		return (NULL);
	return (res);
}

t_access	*exe_init(char **path, t_arg *arg)
{
	t_access	*res;

	res = malloc(sizeof(t_access));
	if (!res)
		return (NULL);
	res->exec1 = get_access(path, arg->cmd1.cmd);
	if (!res->exec1)
	{
		free_tab(path);//free res
		return (NULL);
	}
	res->exec2 = get_access(path, arg->cmd2.cmd);
	if (!res->exec2)
	{
		free_tab(path);//free res and exec1
		return (NULL);
	}
	free_tab(path);
	return (res);
}

int main(int ac, char **av, char **envp)
{
	char		**path;
	t_access	*exe;
	t_arg		*arg;
// add free all function that check that the adress exist before trying to free so it can be used everywhere cause lazy 
	if (ac != 5)
		return (1);
	arg = arg_init(av);
	path = get_path(envp);
	if (!path)
		return (1);
	exe = exe_init(path, arg);
	if (!exe)
		return (1); //free path, arg
	free(exe->exec1);
	free(exe->exec2);
	free(exe);
	free(arg->file.input);
	free(arg->file.output);
	free_tab(arg->cmd1.tab);
	free_tab(arg->cmd2.tab);
	free(arg);
}
