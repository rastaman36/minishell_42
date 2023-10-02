/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <mochaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 10:55:26 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/02 20:11:07 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restoring_data_utls(char **str, int a, int j)
{
	if (str[a][j] == PIPE)
		str[a][j] = '|';
	if (str[a][j] == REDR)
		str[a][j] = '>';
	if (str[a][j] == REDL)
		str[a][j] = '<';
	if (str[a][j] == SPACES)
		str[a][j] = ' ';
}

void	restoring_data(char **str)
{
	int	a;
	int	j;

	a = 0;
	j = 0;
	while (str[a])
	{
		if (str[a][0] == '\"')
		{
			j = 0;
			while (str[a][j])
			{
				restoring_data_utls(str, a, j);
				j++;
			}
		}
		a++;
	}
}

char	*norm_remov(char *s, int *a, char *string)
{
	while (s[*a] != '\"')
	{
		if (s[*a] == ' ')
			string = ft_strjoin(string, SPACES);
		else if (s[*a] == '>')
			string = ft_strjoin(string, REDR);
		else if (s[*a] == '|')
			string = ft_strjoin(string, PIPE);
		else if (s[*a] == '<')
			string = ft_strjoin(string, REDL);
		else
			string = ft_strjoin(string, s[*a]);
		*a = *a + 1;
	}
	return (string);
}

char	*retur(char **string)
{
	printf("error!");
	return (*string);
}

char	*removing_spaces(char *s)
{
	int		a;
	char	*string;

	a = 0;
	string = ft_strdup("");
	while (s[a])
	{
		if (s[a] && ft_strlen(s) == 1)
			return (retur(&string));
		if (s[a] == '\"')
		{
			if (ft_strlen(s) == 6 && s[a] == '\"')
				return (retur(&string));
			if (s[ft_strlen(s) - 1] != '\"')
				return (retur(&string));
			string = ft_strjoin(string, s[a++]);
			return (norm_remov(s, &a, string));
			string = ft_strjoin(string, s[a]);
		}
		else
			string = ft_strjoin(string, s[a++]);
	}
	free(s);
	return (string);
}
