/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipes1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 10:36:27 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/02 19:55:38 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_of_all(t_pipe *pipenode)
{
	int	test;
	int	test2;

	close(pipenode->pipefd[0]);
	close(pipenode->pipefd[1]);
	waitpid(pipenode->pid, &test, 0);
	waitpid(pipenode->pid2, &test2, 0);
	g_status = WEXITSTATUS(test);
	g_status = WEXITSTATUS(test2);
}

void	childe1_pipes(t_pipe *pipenode, t_env **env, t_list *args, int *counter)
{
	signal(SIGQUIT, handle_signals);
	close(pipenode->pipefd[0]);
	dup2(pipenode->pipefd[1], STDOUT_FILENO);
	execute_pipeline(pipenode->left, counter, env, args);
	free_linked_list(args);
	exit(g_status);
}

void	childe2_pipes(t_pipe *pipenode, t_env **env, t_list *args, int *counter)
{
	signal(SIGQUIT, handle_signals);
	close(pipenode->pipefd[1]);
	dup2(pipenode->pipefd[0], STDIN_FILENO);
	execute_pipeline(pipenode->right, counter, env, args);
	exit(g_status);
}

void	error_msg(int i)
{
	if (i == -1)
	{
		perror("Fork failed");
		exit(1);
	}
}

void	if_it_pipe(t_cmd *tree, int *counter, t_env **env, t_list *args)
{
	t_pipe	*pipenode;

	if (tree->type == '|')
	{
		(*counter)++;
		pipenode = (t_pipe *)tree;
		if (pipe(pipenode->pipefd) == -1)
		{
			perror("Pipe creation failed");
			exit(1);
		}
		pipenode->pid = fork();
		error_msg(pipenode->pid);
		if (!pipenode->pid)
			childe1_pipes(pipenode, env, args, counter);
		pipenode->pid2 = fork();
		if (!pipenode->pid2)
			childe2_pipes(pipenode, env, args, counter);
		else
			parent_of_all(pipenode);
	}
}
