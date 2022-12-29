/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:32:45 by hdelmas           #+#    #+#             */
/*   Updated: 2022/12/29 16:20:43 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	*free_all(t_access *exe, t_arg *arg)
{
	if (exe)
	{
		if (exe->exec1)
			free(exe->exec1);
		if (exe->exec2)
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
	return (NULL);
}

void	*input_file_error(t_arg *arg)
{
	perror(arg->file.input);
	return (free_all(NULL, arg));
}
