/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:04:33 by himejjad          #+#    #+#             */
/*   Updated: 2023/10/02 19:32:49 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_join_enva(t_env **env, char *name, char *value, int j)
{
	if (j == 1)
		join_env_var(env, name, value);
	else
		new_env_var(env, name, value);
	free(name);
	free(value);
}

void	add_env_var(t_env **env, char *str)
{
	int		i;
	char	*name;
	char	*value;
	int		j;

	j = 0;
	i = ft_strchr(str, '=');
	if (str[i - 1] == '+')
		j = 1;
	name = strndup(str, i - j);
	if (i >= ft_strlen(str))
		value = ft_strdup("");
	else
		value = ft_strdup(str + i + 1);
	if (name && value)
	{
		if (!isalpha(name[0]) && name[0] != '_')
		{
			printf("export: `%s': not a valid identifier \n", name);
			g_status = 1;
			return ;
		}
		add_join_enva(env, name, value, j);
	}
}

int	export_2(t_env *env, t_list *args)
{
	char	*var_name;
	int		j;

	j = 0;
	while (args)
	{
		var_name = args->str;
		if (is_duplicate(env, var_name))
			add_env_var(&env, args->str);
		args = args->next;
	}
	return (j);
}

void	export(t_env **varenv, t_list *args)
{
	t_env	*env;

	args = args->next;
	export_2(*varenv, args);
	if (!args)
	{
		env = *varenv;
		while (env)
		{
			if (env->var_value[0] == '\0')
				printf("declare - x %s\n", env->var_name);
			else
				printf("declare - x %s=\"%s\"\n", env->var_name,
					env->var_value);
			env = env->next;
		}
	}
}
