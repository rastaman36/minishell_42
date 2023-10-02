/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:47:09 by himejjad          #+#    #+#             */
/*   Updated: 2023/10/02 19:37:06 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_all_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo_opt(t_list **args)
{
	int	j;

	j = 0;
	while ((*args) && (*args)->str[0] == '-')
	{
		if (!is_all_n((*args)->str))
		{
			printf("%s ", (*args)->str);
			*args = (*args)->next;
			break ;
		}
		j = 1;
		*args = (*args)->next;
	}
	return (j);
}

void	ft_echo(t_list *args)
{
	int	j;
	int	i;

	i = 0;
	args = args->next;
	j = 0;
	j = echo_opt(&args);
	while (args)
	{
		ft_rremove(args->str);
		printf("%s ", args->str);
		args = args->next;
	}
	free_linked_list(args);
	if (j == 0)
		printf("\n");
}
