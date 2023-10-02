/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:27:46 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/02 19:05:56 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	limiter_expanding(char c)
{
	if (c == '_' || c == '!' || c == '#' || ft_isalnum(c))
		return (1);
	return (0);
}

char	*get_variable(char *str)
{
	int		a;
	char	*arr;
	char	*f;

	a = 0;
	arr = ft_strdup("");
	f = str;
	while (f[a] && limiter_expanding(f[a]))
	{
		arr = ft_strjoin(arr, f[a]);
		a++;
	}
	return (arr);
}

char	*get_value(char *name_vr, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(name_vr, tmp->var_name))
		{
			return (tmp->var_value);
		}
		tmp = tmp->next;
	}
	return ("");
}

char	*ex_h(int *a, char *status, char *string)
{
	*a = *a + 2;
	status = ft_itoa(g_status);
	string = ft_strjoin2(string, status);
	free(status);
	return (string);
}

void	ft_norm(t_env *env, char **f, int *a, char **string)
{
	char	*v;

	env->status = NULL;
	if ((*f)[(*a) + 1] == '?')
		*string = ex_h(a, env->status, *string);
	else
	{
		env->name_vr = get_variable(*f + *a + 1);
		v = env->name_vr;
		env->name_vl = get_value(v, env);
		*string = ft_strjoin2(*string, env->name_vl);
		*f += ft_strlen(v) + 1;
		free(env->name_vr);
	}
}
