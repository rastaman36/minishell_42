/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 00:31:01 by himejjad          #+#    #+#             */
/*   Updated: 2023/10/02 19:22:32 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delet_2(t_env **envar, char *var_name)
{
	t_env	*current;
	t_env	*prev;

	current = *envar;
	while (current->next)
	{
		if (!ft_strcmp(current->next->var_name, var_name))
		{
			prev = current->next;
			free(current->next->var_name);
			free(current->next->var_value);
			current->next = current->next->next;
			free(prev);
			return ;
		}
		current = current->next;
	}
}

void	delet_unset(t_env **env, char *var_name)
{
	t_env	*current;
	t_env	*perv;

	perv = NULL;
	current = *env;
	if (env != NULL)
	{
		if (ft_strcmp(current->var_name, var_name))
			delet_2(env, var_name);
		else
		{
			current = (*env);
			(*env) = (*env)->next;
			free(current->var_name);
			free(current->var_value);
			return ;
		}
	}
}

void	unset(t_env **varenv, t_list *args)
{
	while (args != NULL)
	{
		delet_unset(varenv, args->str);
		args = args->next;
	}
}
