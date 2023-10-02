/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utls1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:58:23 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/02 19:03:36 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	norming_fds(char c, int fd, char **string, int *j)
{
	if (c == '<')
	{
		fd = open(string[*j], O_RDONLY);
		if (fd == -1)
			perror("check again fd");
	}
	else
		fd = open(string[*j], O_CREAT | O_WRONLY, 0644);
}

void	norming_fds1(t_env *env, char **string)
{
	env->fd = open("/tmp/.filess", O_CREAT | O_RDWR | O_TRUNC, 0777);
	handling_here_doc(string[env->j], env->fd, env);
}

char	*geting_names_files(char **string, char c, t_env *env)
{
	env->j = 0;
	env->fd = 0;
	env->s = NULL;
	while (string[env->j])
	{
		if (string[env->j][0] == c && string[env->j][1] != c && string[env->j
			+ 1][0] != c)
		{
			env->s = ft_strdup(string[++env->j]);
			norming_fds(c, env->fd, string, &env->j);
			close(env->fd);
		}
		else if (string[env->j][0] == c && string[env->j][1] == c
				&& string[env->j][2] != c && string[env->j + 1][0] != c)
		{
			env->s = ft_strdup(string[++env->j]);
			if (c == '>')
				env->fd = open(string[env->j], O_CREAT | O_WRONLY | O_APPEND,
						0777);
			else
				norming_fds1(env, string);
		}
		env->j++;
	}
	return (env->s);
}
