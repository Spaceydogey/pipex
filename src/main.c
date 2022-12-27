/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:35:01 by hdelmas           #+#    #+#             */
/*   Updated: 2022/12/27 11:26:41 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	free_all(t_access *exe, t_arg *arg)
{
	if (exe)
	{
		if (exe->exec1)
			free(exe->exec1);
		if (exe->exec1)
			free(exe->exec2);
		free(exe);
	}
	if (arg)
	{
		if (arg->file.input)
			free(arg->file.input);
		if (arg->file.output)
			free(arg->file.output);
		if (arg->cmd1.tab)
			free_tab(arg->cmd1.tab);
		if (arg->cmd2.tab)
			free_tab(arg->cmd2.tab);
		free(arg);
	}
	return (1);
}
static t_cmd	cmd_init(char *str, char *file)
{
	t_cmd	res;
	char	**tab;
	int		i;
	char	**tmp;

	res.cmd = NULL;
	tmp = ft_split(str, ' ');
	if (!tmp)
		return (res);
	res.cmd = tmp[0];
	i = -1;
	while (tmp[++i])
		;
	res.size = i + 1;// ?? 
	tab = malloc(sizeof(char *) * (res.size + 1));
	if (!tab)
		return (res); //free tmp;
	i = -1;
	while (tmp[++i])
	{
		tab[i] = tmp[i];
	}
	free(tmp);
	tab[i] = file;
	tab[i + 1] = NULL;
	res.tab = tab;
	return (res);
}

static t_arg	*arg_init(char **av)
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
	res->cmd1 = cmd_init(av[2], res->file.input);
	if (!res->cmd1.cmd)
		return (NULL);
	res->cmd2 = cmd_init(av[3], NULL);//add output cmd1 maybe change code layout
	if (!res->cmd2.cmd)
		return (NULL);
	return (res);
}

static t_access	*exe_init(char **path, t_arg *arg)
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

	if (ac != 5)
		return (1);
	arg = arg_init(av);
	path = get_path(envp);
	if (!path)
		return (free_all(exe, arg));
	exe = exe_init(path, arg);
	if (!exe)
		return (free_all(exe, arg)); 
	//free files str
	ppx_exec(exe, arg, envp);
	free_all(exe, arg);
}
