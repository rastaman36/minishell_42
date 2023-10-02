/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:22:20 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/02 19:43:01 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	int		a;
	int		on;
	char	*string;

	if (!s1 || !s2)
		return (NULL);
	on = ft_strlen(s1);
	string = (char *)malloc(sizeof(char) * on + ft_strlen(s2) + 1);
	if (!string)
		return (NULL);
	a = 0;
	while (s1[a])
	{
		string[a] = s1[a];
		a++;
	}
	a = 0;
	while (s2[a])
		string[on++] = s2[a++];
	string[on] = '\0';
	free(s1);
	return (string);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char c)
{
	int		i;
	char	*str;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	str[++i] = '\0';
	free(s1);
	return (str);
}

char	*ft_strdup(const char *src)
{
	int		i;
	char	*str;

	i = 0;
	while (src[i])
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
