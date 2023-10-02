/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 11:14:34 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/02 19:56:03 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_dd(char **str)
{
	int	a;

	a = 0;
	if (!str)
		return ;
	while (str[a])
	{
		free(str[a]);
		a++;
	}
	free(str);
}

void	free_recur1(t_execdata *exnode)
{
	if (exnode->path)
		free_dd(exnode->path);
	if (exnode->argv != NULL)
		free_dd(exnode->argv);
	if (exnode->infile)
		free(exnode->infile);
	if (exnode->outfile)
		free(exnode->outfile);
	free(exnode);
}

void	free_recur(t_cmd *tree)
{
	t_execdata	*exnode;
	t_pipe		*ppnode;
	t_redir		*rdnode;

	if (tree->type == '|')
	{
		ppnode = (t_pipe *)tree;
		free_recur(ppnode->left);
		free_recur(ppnode->right);
		free(ppnode);
	}
	else if (tree->type == '>')
	{
		rdnode = (t_redir *)tree;
		free_recur(rdnode->cmds);
		free(rdnode);
	}
	else if (tree->type == ' ')
	{
		exnode = (t_execdata *)tree;
		free_recur1(exnode);
	}
}
