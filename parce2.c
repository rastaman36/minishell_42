/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 10:59:10 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/02 19:42:10 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*puting_space_utls(char *s, char *string, int a)
{
	if (s[a] != ' ')
	{
		string = ft_strjoin(string, s[a]);
		string = ft_strjoin(string, ' ');
	}
	else
		string = ft_strjoin(string, s[a]);
	return (string);
}

char	*puting_space_utls1(char *s, char *string, int a)
{
	if (s[a + 1] != ' ' && s[a + 1] != '<' && s[a + 1] != '>')
	{
		string = ft_strjoin(string, s[a]);
		string = ft_strjoin(string, ' ');
	}
	else
		string = ft_strjoin(string, s[a]);
	return (string);
}

char	*puting_space_utls2(char *s, char *string, int a)
{
	if (s[a + 2] != ' ')
	{
		string = ft_strjoin(string, s[a]);
		string = ft_strjoin(string, ' ');
	}
	else
		string = ft_strjoin(string, s[a]);
	return (string);
}

char	*puting_space_utls3(char *s, char *string, int a)
{
	if (s[a + 2] != ' ')
	{
		string = ft_strjoin(string, s[a]);
		string = ft_strjoin(string, ' ');
	}
	else
		string = ft_strjoin(string, s[a]);
	return (string);
}

char	*puting_space(char *s)
{
	int		a;
	char	*string;

	string = ft_strdup("");
	s = removing_spaces(s);
	a = 0;
	while (s[a])
	{
		if (s[a + 1] == '|' || (s[a + 1] == '<' && s[a] != '<') || (s[a
					+ 1] == '>' && s[a] != '>'))
				string = puting_space_utls(s, string, a);
		else if (s[a] == '|' || s[a] == '<' || s[a] == '>')
			string = puting_space_utls1(s, string, a);
		else if (s[a] == '<' && s[a + 1] == '<')
			string = puting_space_utls2(s, string, a);
		else if (s[a] == '>' && s[a + 1] == '>')
			string = puting_space_utls3(s, string, a);
		else
			string = ft_strjoin(string, s[a]);
		a++;
	}
	free(s);
	return (string);
}
