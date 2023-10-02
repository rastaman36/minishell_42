/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_finish.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <mochaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 23:17:03 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/02 23:25:01 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parce_tree(char **str, int *a, t_env **env)
{
	t_cmd		*tree;
	t_cmd		*mouad;
	char		**for_free;

	if (checking_pipe(str, '|', a))
	{
		for_free = building_data(str, a);
		mouad = exec_data(for_free, *env);
		tree = piping(mouad, parce_tree(str, a, env));
	}
	else
	{
		for_free = building_data(str, a);
		tree = exec_data(for_free, *env);
	}
	return (tree);
}

int	clearing(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' || s[i] != '\t' || s[i] != '\v' || s[i] != '\r'
			|| s[i] != '\b')
			return (0);
		i++;
	}
	return (1);
}

int	norming_main(char *line_cmd)
{
	if (line_cmd == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	if (ft_strncmp(line_cmd, "\n", ft_strlen(line_cmd)))
	{
		free(line_cmd);
		line_cmd = NULL;
		return (1);
	}
	if (!line_cmd)
		return (0);
	if (line_cmd && clearing(line_cmd))
	{
		free(line_cmd);
		return (1);
	}
	return (-1);
}

void	free_of_magic(t_list *args, char *line_cmd, char **string, t_cmd *parce)
{
	if (!ft_strcmp(line_cmd, "clear"))
		system("clear");
	free_linked_list(args);
	free(line_cmd);
	free_recur(parce);
	line_cmd = NULL;
	free_dd(string);
}
