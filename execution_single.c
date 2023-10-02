/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_single.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 12:00:39 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/02 19:55:28 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_single_command(char **command, t_cmd *tree, t_env **env,
		t_list *args)
{
	t_execdata	*execnode;

	(void)command;
	execnode = (t_execdata *)tree;
	args = create_linked_list(execnode->argv);
	if (is_builtin(execnode->argv[0]))
	{
		builtins(env, args, execnode->argv[0], execnode);
		free_linked_list(args);
		return ;
	}
	else if (execnode->path == NULL)
	{
		printf("Command not found\n");
		free_linked_list(args);
		return ;
	}
	free_linked_list(args);
	execute_single1(execnode);
}
