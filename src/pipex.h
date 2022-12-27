/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:09:49 by hdelmas           #+#    #+#             */
/*   Updated: 2022/12/27 14:22:16 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
#include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	char	*cmd;
	int		size;
	char	**tab;
}	t_cmd;

typedef struct s_files
{
	char	*input;
	char	*output;
	int		fd_in;
	int		fd_out;
}	t_files;

typedef struct s_arg
{
	t_files	file;
	t_cmd	cmd1;
	t_cmd	cmd2;
}	t_arg;

typedef struct s_access
{
	char	*exec1;
	char	*exec2;
}	t_access;

char	**get_path(char **envp);
char	*ft_strdup(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_access(char **path, char *cmd);
char    **ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t  ft_strlen(const char *s);
char	*free_tab(char **tab);
int	ppx_exec(t_access *exe, t_arg *arg, char **envp);
#endif
