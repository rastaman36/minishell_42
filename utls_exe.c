/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:43:48 by himejjad          #+#    #+#             */
/*   Updated: 2023/10/02 19:22:58 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_rremove(char *str)
{
	char	*src;
	char	*dest;

	src = str;
	dest = str;
	while (*src)
	{
		if (*src == '"')
			src++;
		else
		{
			*dest = *src;
			dest++;
			src++;
		}
	}
	*dest = '\0';
}

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

int	is_duplicate(t_env *env, char *var_name)
{
	while (env)
	{
		if (!strcmp(env->var_name, var_name))
			return (0);
		env = env->next;
	}
	return (1);
}
