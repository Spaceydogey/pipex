/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:09:49 by hdelmas           #+#    #+#             */
/*   Updated: 2022/12/23 15:43:50 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
#include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

char	**get_path(char **envp);
char	*ft_strdup(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_access(char **path, char *cmd);
char    **ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t  ft_strlen(const char *s);
char	*free_tab(char **tab);
#endif
