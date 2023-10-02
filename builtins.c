/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 05:10:09 by himejjad          #+#    #+#             */
/*   Updated: 2023/10/02 19:48:30 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_execdata *execnode)
{
	printf("exit\n");
	if (arrlen(execnode->argv) == 2)
	{
		if (ft_isdegit(execnode->argv[1]))
			g_status = atoi(execnode->argv[1]);
		else
		{
			perror("exit : numeric argument required");
			g_status = 2;
			exit(g_status);
		}
		exit(g_status);
	}
	else if (arrlen(execnode->argv) > 2)
	{
		perror("exit : too many arguments");
		g_status = 1;
		return ;
	}
	exit(0);
}

int	is_builtin(char *s)
{
	if (!ft_strcmp(s, "env"))
		return (1);
	else if (!ft_strcmp(s, "export"))
		return (1);
	else if (!ft_strcmp(s, "echo"))
		return (1);
	else if (!ft_strcmp(s, "pwd"))
		return (1);
	else if (!ft_strcmp(s, "cd"))
		return (1);
	else if (!ft_strcmp(s, "unset"))
		return (1);
	return (0);
}

void	builtins(t_env **env, t_list *args, char *s, t_execdata *execnode)
{
	if (ft_strcmp(execnode->argv[0], "exit") == 0)
		ft_exit(execnode);
	if (!strcmp(s, "env"))
		printer_env(*env);
	else if (!strcmp(s, "export"))
		export(env, args);
	else if (!strcmp(s, "echo"))
		ft_echo(args);
	else if (!strcmp(s, "pwd"))
		ft_pwd();
	else if (!strcmp(s, "cd"))
		ft_cd(args, env);
	else if (!strcmp(s, "unset"))
		unset(env, args);
}
