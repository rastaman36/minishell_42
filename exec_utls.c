/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:22:11 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/02 19:03:16 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**building_data(char **s, int *a)
{
	int		j;
	char	**string;
	int		d;
	int		t;

	j = 0;
	d = (*a);
	while (s[*a])
	{
		if (s[*a][0] == '|')
			break ;
		(*a)++;
	}
	string = (char **)malloc(sizeof(char *) * ((*a) - d) + 1);
	t = (*a) - d;
	while (j < t)
	{
		string[j] = ft_strdup(s[d]);
		d++;
		j++;
	}
	string[j] = NULL;
	(*a)++;
	return (string);
}

int	checking_pipe(char **str, char c, int *a)
{
	int	j;

	j = (*a);
	if (arrlen(str) <= j)
		return (0);
	while (str[j])
	{
		if (str[j][0] == c)
			return (1);
		j++;
	}
	return (0);
}

char	**norming(char **str, char **string, int *j, int *count)
{
	while (str[*j])
	{
		if (str[*j][0] == '<' || str[*j][0] == '>')
		{
			*j = *j + 2;
			continue ;
		}
		else
			string[*count] = ft_strdup(str[*j]);
		*count = *count + 1;
		*j = *j + 1;
	}
	return (string);
}

char	**geting_argument(char **str)
{
	int		j;
	int		count;
	char	**string;

	j = 0;
	count = 0;
	while (str[j])
	{
		if (str[j][0] == '>' || str[j][0] == '<')
			count++;
		j++;
	}
	string = malloc(sizeof(char *) * (j - (count * 2) + 1));
	j = 0;
	count = 0;
	string = norming(str, string, &j, &count);
	string[count] = NULL;
	return (string);
}
