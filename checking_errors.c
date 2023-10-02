/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 22:16:52 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/02 19:02:25 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdegit(char *string)
{
	int	a;

	a = 0;
	while (string[a])
	{
		if (string[a] > '9' || string[a] < '0')
			return (0);
		a++;
	}
	return (1);
}

int	checking_exit(char **s)
{
	if (ft_strcmp(s[0], "exit") == 0)
	{
		if (arrlen(s) == 2)
		{
			if (ft_isdegit(s[1]))
				g_status = atoi(s[1]);
			else
			{
				perror("exit : numeric argument required");
				g_status = 1;
			}
			exit(g_status);
		}
		else if (arrlen(s) > 2)
		{
			perror("exit : too many arguments");
			g_status = 1;
			return (0);
		}
		printf("exit\n");
		exit(0);
		return (0);
	}
	return (1);
}

int	checkerrors_1(char **s, int i)
{
	if ((s[i][0] == '>' || s[i][0] == '<') && arrlen(s) == (i + 1))
	{
		perror("minishell: No file");
		return (0);
	}
	if (s[0][0] == '|' || s[arrlen(s) - 1][0] == '|')
	{
		perror("minishell: error");
		return (0);
	}
	if (s[i][0] == '<' && s[i + 1][0] == '>')
	{
		perror("minishell: error");
		return (0);
	}
	return (1);
}

int	checkerrors_2(char **s, int i)
{
	if (s[i][0] == '>' && s[i + 1][0] == '<')
	{
		perror("minishell: error");
		return (0);
	}
	if ((s[i][0] == '<' && s[i][1] == '<' && s[i + 1][0] == '<')
		|| (s[i][0] == '<' && s[i][1] == '<' && s[i + 1][0] == '>')
		|| (s[i][0] == '<' && s[i][1] == '<' && s[i][2] == '<'))
	{
		perror("minishell: error");
		return (0);
	}
	if ((s[i][0] == '>' && s[i][1] == '>' && s[i][2] == '>') || (s[i][0] == '>'
			&& s[i][1] == '>' && s[i + 1][0] == '<'))
	{
		perror("minishell: error");
		return (0);
	}
	if ((s[i][0] == '>' || s[i][0] == '<') && s[i + 1][0] == '|')
	{
		perror("minishell: error");
		return (0);
	}
	return (1);
}

int	checkerrors(char **s)
{
	int	i;

	i = 0;
	if (*s == NULL)
		return (0);
	if (!checking_exit(s))
		return (0);
	while (s[i])
	{
		if (!checkerrors_1(s, i))
			return (0);
		if (!checkerrors_2(s, i))
			return (0);
		i++;
	}
	return (1);
}
