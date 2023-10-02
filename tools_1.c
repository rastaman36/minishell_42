/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 19:43:04 by himejjad          #+#    #+#             */
/*   Updated: 2023/10/02 19:43:15 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arrlen(char **str)
{
	int	a;

	a = 0;
	while (str[a])
		a++;
	return (a);
}

void	bost_free(char **s)
{
	int	a;

	a = 0;
	while (s[a])
	{
		free(s[a]);
		a++;
	}
	free(s);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1)
		return (-1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	ft_isalnum(int c)
{
	c = (char)c;
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9'))
		return (1);
	return (0);
}
