/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 11:06:16 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/02 19:02:43 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	creation_of_env(t_env **env, char **envp)
{
	int		a;
	t_env	*new;
	char	**var;

	a = 0;
	if (!envp)
		return ;
	while (envp[a])
	{
		var = ft_split(envp[a], '=');
		new = ft_lstnew(var[0], var[1]);
		ft_lstadd_back(env, new);
		free_dd(var);
		a++;
	}
}

void	printer_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->var_value[0] != '\0')
			printf("%s=%s\n", tmp->var_name, tmp->var_value);
		tmp = tmp->next;
	}
}
