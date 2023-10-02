/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <mochaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:50:50 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/02 21:52:36 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check(char *name_vr, t_env *env)
{
	t_env	*tmp;
	char	*str;
	char	*r;

	str = ft_strdup("");
	r = str;
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(name_vr, tmp->var_name))
		{
			return (tmp->var_value);
		}
		tmp = tmp->next;
	}
	free(r);
	return (str);
}

char	*start_expanding(char *s, t_env *env)
{
	int		a;
	char	*string;
	char	*name_vl;
	char	*name_vr;
	char	*v;

	a = 0;
	string = ft_strdup("");
	while (s[a])
	{
		if (s[a] == '$')
		{
			name_vr = get_variable(s + a + 1);
			v = name_vr;
			name_vl = get_value(v, env);
			string = ft_strjoin2(string, name_vl);
			s += ft_strlen(v) + 1;
			free(name_vr);
		}
		else
			string = ft_strjoin(string, s[a++]);
	}
	return (string);
}

void	putinfile(int fd, char *s)
{
	int	a;

	a = 0;
	while (s[a])
	{
		write(fd, &s[a], 1);
		a++;
	}
}

int	check_lim(char *str)
{
	int	a;

	a = 0;
	while (str[a])
	{
		if ((str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
			|| (str[0] == '\'' && str[ft_strlen(str) - 1] == '\''))
		{
			return (1);
		}
		a++;
	}
	return (0);
}

void	her_light(char *string, int fd, t_env *env, char **tmp)
{
	char	*save;

	save = NULL;
	if (check_lim(string) == 0)
	{
		save = start_expanding(*tmp, env);
		putinfile(fd, save);
	}
	else
		putinfile(fd, *tmp);
	if (check(save, env) == NULL)
	{
		*tmp = ft_strdup("");
		putinfile(fd, *tmp);
	}
	if (save)
	{
		free(save);
		save = NULL;
	}
}
