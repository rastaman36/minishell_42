/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:01:25 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/02 19:56:29 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**geting_path(t_env *env)
{
	int		a;
	char	**s;

	a = 0;
	if (env->var_name != NULL)
	{
		while (env->next)
		{
			if (env->var_name[0] == 'P' && env->var_name[1] == 'A'
				&& env->var_name[2] == 'T' && env->var_name[3] == 'H')
			{
				s = ft_split(env->var_value, ':');
				return (s);
			}
			env = env->next;
		}
	}
	s = NULL;
	return (s);
}

int	check_cmp(char **str, char *s)
{
	int	a;

	a = 0;
	while (str[a])
	{
		if (ft_strcmp(str[a], s) == 0)
		{
			return (1);
		}
		a++;
	}
	return (0);
}

t_cmd	*rederections(t_cmd *exec, char **str)
{
	t_redir		*commend;
	t_execdata	*in_out;

	in_out = (t_execdata *)exec;
	commend = malloc(sizeof(*commend));
	commend->type = '>';
	if (check_cmp(str, "<<"))
		commend->infd = open(in_out->infile, O_RDWR, 0777);
	else if (in_out->infile)
		commend->infd = open(in_out->infile, O_RDONLY);
	else
		commend->infd = 0;
	if (check_cmp(str, ">>"))
		commend->outfd = open(in_out->outfile, O_CREAT | O_WRONLY | O_APPEND,
				0664);
	else if (in_out->outfile)
		commend->outfd = open(in_out->outfile, O_CREAT | O_WRONLY | O_TRUNC,
				0666);
	else
		commend->outfd = 1;
	commend->cmds = exec;
	return ((t_cmd *)commend);
}

t_cmd	*exec_data(char **str, t_env *env)
{
	t_execdata	*commande;

	commande = malloc(sizeof(*commande));
	commande->type = ' ';
	commande->argv = geting_argument(str);
	commande->infile = geting_names_files(str, '<', env);
	commande->outfile = geting_names_files(str, '>', env);
	commande->path = geting_path(env);
	commande = (t_execdata *)rederections((t_cmd *)commande, str);
	free_dd(str);
	return ((t_cmd *)commande);
}

t_cmd	*piping(t_cmd *left, t_cmd *right)
{
	t_pipe	*commande;

	commande = malloc(sizeof(*commande));
	commande->type = '|';
	commande->left = left;
	commande->right = right;
	return ((t_cmd *)commande);
}
