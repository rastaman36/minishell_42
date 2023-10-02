/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <mochaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 11:32:31 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/02 22:41:50 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	singel_one(t_execdata *execnode, t_list *args, t_env **env)
{
	args = create_linked_list(execnode->argv);
	builtins(env, args, execnode->argv[0], execnode);
	free_linked_list(args);
	exit(0);
}

void	path_in_pipe(t_execdata *execnode)
{
	int	pid;
	int	status;

	pid = fork();
	error_msg(pid);
	if (pid == 0)
	{
		signal(SIGQUIT, handle_signals);
		execve(execnode->argv[0], execnode->argv, NULL);
		perror("error check again your command");
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		g_status = WEXITSTATUS(status);
	}
}

char	*execute_commande_withoutfork(t_execdata *execnode, char *str)
{
	int	a;

	a = 0;
	if (execnode->path == NULL)
	{
		perror("Path not found");
		exit(1);
	}
	while (execnode->path[a])
	{
		str = ft_strjoin2(execnode->path[a], "/");
		str = ft_strjoin2(str, execnode->argv[0]);
		if (access(str, F_OK) != -1)
		{
			if (execve(str, execnode->argv, NULL) == -1)
			{
				perror("error check again your command");
				free(str);
				exit(1);
			}
		}
		a++;
		free(str);
	}
	return (str);
}

void	if_it_command(t_cmd *tree, int *counter, t_env **env, t_list *args)
{
	char		*str;
	t_execdata	*execnode;

	str = NULL;
	if (tree->type == ' ')
	{
		execnode = (t_execdata *)tree;
		if (*counter == 0)
			execute_single_command(execnode->argv, tree, env, args);
		else if (is_builtin(execnode->argv[0]))
			singel_one(execnode, args, env);
		else if (access(execnode->argv[0], F_OK) != -1)
			path_in_pipe(execnode);
		else
		{
			str = execute_commande_withoutfork(execnode, str);
			if (access(str, F_OK) == -1 && access(execnode->argv[0], F_OK)
				== -1)
			{
				g_status = 127;
				printf(" %s :Command Not Found!\n", execnode->argv[0]);
				return ;
			}
		}
	}
}

void	execute_pipeline(t_cmd *tree, int *counter, t_env **env, t_list *args)
{
	t_redir	*rder;

	if_it_pipe(tree, counter, env, args);
	if_it_command(tree, counter, env, args);
	if (tree->type == '>')
	{
		rder = (t_redir *)tree;
		dup2(rder->infd, STDIN_FILENO);
		dup2(rder->outfd, STDOUT_FILENO);
		execute_pipeline(rder->cmds, counter, env, args);
	}
}
