/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utls1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <mochaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:58:23 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/03 00:53:32 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_in_out(char **string, char c, int fd, t_env *env)
{
	if (string[env->j][0] == c && string[env->j][1] != c \
	&& string[env->j + 1][0] != c)
	{
		env->s = ft_strdup(string[++env->j]);
		if (c == '<')
		{
			fd = open(string[env->j], O_RDONLY);
			if (fd == -1)
				perror("check again fd");
		}
		else
			fd = open(string[env->j], O_CREAT | O_WRONLY, 0644);
		close(fd);
	}
}

char	*geting_names_files(char **string, char c, t_env *env)
{
	int		fd;

	env->j = 0;
	fd = 0;
	env->s = NULL;
	while (string[env->j])
	{
		check_in_out(string, c, fd, env);
		if (string[env->j][0] == c && string[env->j][1] == c \
		&& string[env->j][2] != c && string[env->j + 1][0] != c)
		{
			env->s = ft_strdup(string[++env->j]);
			if (c == '>')
				fd = open(string[env->j], O_CREAT | O_WRONLY | O_APPEND, 0777);
			else
			{
				fd = open("/tmp/.filess", O_CREAT | O_RDWR | O_TRUNC, 0777);
				handling_here_doc(string[env->j], fd, env);
			}
		}
		env->j++;
	}
	return (env->s);
}
