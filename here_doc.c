/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <mochaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:29:43 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/02 21:53:11 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_here(char **tmp)
{
	free(*tmp);
	*tmp = NULL;
}

void	finish_her(int fd)
{
	fd = open("/tmp/.filess", O_RDONLY, 0644);
	dup2(fd, 0);
	close(fd);
	unlink("/tmp/.filess");
}

void	finishe_here1(char *string, int fd, char *tmp, t_env *env)
{
	while (1)
	{
		her_light(string, fd, env, &tmp);
		write(1, "> ", 2);
		if (tmp)
			free_here(&tmp);
		tmp = get_next_line(0);
		if (tmp == NULL || (ft_strncmp(string, tmp, env->l) == 1
				&& tmp[env->l] == '\n'))
		{
			if (tmp)
				free_here(&tmp);
			break ;
		}
	}
}

void	handling_here_doc(char *string, int fd, t_env *env)
{
	char	*str;
	char	*tmp;

	env->l = ft_strlen(string);
	write(1, "> ", 2);
	str = get_next_line(0);
	tmp = str;
	if (tmp == NULL || (ft_strncmp(string, tmp, env->l) == 1 \
	&& tmp[env->l] == '\n'))
		;
	else
	{
		finishe_here1(string, fd, tmp, env);
	}
	finish_her(fd);
}
