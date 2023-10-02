/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:05:42 by himejjad          #+#    #+#             */
/*   Updated: 2023/10/02 19:28:58 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_new_var(t_env *new_var, char *name, char *value)
{
	new_var = malloc(sizeof(t_env));
	new_var->var_name = ft_strdup(name);
	new_var->var_value = ft_strdup(value);
	new_var->next = NULL;
	return (new_var);
}

void	free_env(t_env *current, t_env *new_var, char *value)
{
	free(current->var_value);
	current->var_value = ft_strdup(value);
	free(new_var->var_value);
	free(new_var->var_name);
	free(new_var);
}

void	new_env_var(t_env **env, char *name, char *value)
{
	t_env	*new_var;
	t_env	*current;

	new_var = NULL;
	new_var = init_new_var(new_var, name, value);
	if ((*env)->var_name == NULL)
		*env = new_var;
	else
	{
		(current) = *env;
		while ((current)->next != NULL)
		{
			if (strcmp(current->var_name, name) == 0)
			{
				current->var_value = ft_strdup(value);
				free_env(current, new_var, value);
				return ;
			}
			current = (current)->next;
		}
		if (strcmp(current->var_name, name) == 0)
			free_env(current, new_var, value);
		else
			(current)->next = new_var;
	}
}

void	norm_exp(t_env *current, t_env *new_var, char *value)
{
	current->var_value = ft_strjoin2(current->var_value, value);
	free(new_var->var_value);
	free(new_var->var_name);
	free(new_var);
	return ;
}

void	join_env_var(t_env **env, char *name, char *value)
{
	t_env	*new_var;
	t_env	*current;

	new_var = NULL;
	new_var = init_new_var(new_var, name, value);
	if ((*env)->var_name == NULL)
		*env = new_var;
	else
	{
		(current) = *env;
		while ((current)->next != NULL)
		{
			if (strcmp(current->var_name, name) == 0)
				norm_exp(current, new_var, value);
			current = (current)->next;
		}
		if (strcmp(current->var_name, name) == 0)
			norm_exp(current, new_var, value);
		else
			(current)->next = new_var;
	}
}
