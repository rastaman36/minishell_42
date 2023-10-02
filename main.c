/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <mochaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:24:08 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/02 23:24:32 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

int	main_tools(char **string, char *line_cmd)
{
	if (!checkerrors(string))
	{
		free(line_cmd);
		line_cmd = NULL;
		free_dd(string);
		return (1);
	}
	return (0);
}

t_cmd	*main_tools1(char **string, t_cmd *parce, t_env *env, t_list *args)
{
	int	ss;
	int	pp;

	parce = NULL;
	ss = 0;
	pp = 0;
	parce = parce_tree(string, &ss, &env);
	execute_pipeline(parce, &pp, &env, args);
	return (parce);
}

void	signals_fun(int ac, char **av)
{
	(void)av;
	(void)ac;
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
}

char	*init(char *line_cmd, char **string, t_env *env, t_list *args)
{
	t_cmd	*parce;
	int		i;
	int		x;

	i = dup(0);
	x = dup(1);
	while (1)
	{
		line_cmd = readline("minishell :-> ");
		if (norming_main(line_cmd) == 1)
			continue ;
		if (norming_main(line_cmd) == 0)
			return (0);
		add_history(line_cmd);
		line_cmd = expanding_env(line_cmd, env);
		line_cmd = puting_space(line_cmd);
		string = ft_split(line_cmd, ' ');
		restoring_data(string);
		if (main_tools(string, line_cmd) == 1)
			continue ;
		parce = main_tools1(string, parce, env, args);
		dup2(x, 1);
		dup2(i, 0);
		free_of_magic(args, line_cmd, string, parce);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	char	*line_cmd;
	char	**string;
	t_list	*args;

	args = NULL;
	env = NULL;
	line_cmd = NULL;
	string = NULL;
	signals_fun(ac, av);
	creation_of_env(&env, envp);
	init(line_cmd, string, env, args);
	return (0);
}
