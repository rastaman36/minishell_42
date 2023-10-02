/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_single1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <mochaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 10:39:49 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/02 20:18:33 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	the_last_exec(t_execdata *execnode, char *str)
{
	if (execve(str, execnode->argv, NULL) == -1)
	{
		perror("error check again your command");
		free(str);
		exit(0);
	}
}

void	path_exec1(t_execdata *execnode, int pid, int status)
{
	if (access(execnode->argv[0], F_OK) != -1)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			exit(1);
		}
		else if (pid == 0)
		{
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
}

void	fork_failed(int pid)
{
	if (pid == -1)
	{
		perror("Fork failed");
		exit(1);
	}
}

char	*execute_single2(t_execdata *execnode, char *str, int status, int pid)
{
	int	a;

	a = 0;
	while (execnode->path[a])
	{
		execnode->tmp = ft_strdup(execnode->path[a]);
		str = ft_strjoin2(execnode->tmp, "/");
		str = ft_strjoin2(str, execnode->argv[0]);
		if (access(str, F_OK) != -1)
		{
			pid = fork();
			fork_failed(pid);
			if (pid == 0 && is_builtin(execnode->argv[0]) == 0)
				the_last_exec(execnode, str);
			else
			{
				waitpid(pid, &status, 0);
				break ;
			}
		}
		a++;
		free(str);
	}
	return (str);
}

void	execute_single1(t_execdata *execnode)
{
	char	*str;
	int		pid;
	int		status;

	status = 0;
	pid = 0;
	str = NULL;
	str = execute_single2(execnode, str, status, pid);
	if (access(str, F_OK) == -1 && access(execnode->argv[0], F_OK) == -1)
	{
		g_status = 127;
		printf(" %s :Command Not Found!\n", execnode->argv[0]);
		return ;
	}
	path_exec1(execnode, pid, status);
	if (str && access(execnode->argv[0], F_OK) == -1)
		free(str);
}
