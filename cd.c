/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 06:08:06 by himejjad          #+#    #+#             */
/*   Updated: 2023/10/02 19:02:01 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	cwd[1024];
	char	*dir;

	dir = getcwd(cwd, sizeof(cwd));
	if (!dir)
		perror("minishell: pwd: ");
	printf("%s\n", dir);
}

void	change_pwd(t_env *curr, char *cwd, char *owd)
{
	while (curr)
	{
		if (ft_strcmp(curr->var_name, "PWD") == 0)
		{
			free(curr->var_value);
			curr->var_value = ft_strdup(cwd);
		}
		if (ft_strcmp(curr->var_name, "OLDPWD") == 0)
		{
			free(curr->var_value);
			curr->var_value = ft_strdup(owd);
		}
		curr = curr->next;
	}
}

void	ft_cd(t_list *arg, t_env **env)
{
	char	cwd[1000];
	char	owd[1000];
	t_env	*curr;

	curr = (*env);
	arg = arg->next;
	getcwd(owd, sizeof(owd));
	if (!arg)
	{
		if (chdir(get_value("HOME", *env)) != 0)
			printf("cd: HOME not set\n");
	}
	else
	{
		if (chdir(arg->str) == -1)
			printf("cd: %s: No such file or directory\n", arg->str);
	}
	getcwd(cwd, sizeof(cwd));
	change_pwd(curr, cwd, owd);
}
