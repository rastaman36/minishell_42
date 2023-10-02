/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <mochaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:07:32 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/02 16:00:00 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	temp = *lst;
	if ((*lst) == NULL)
	{
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

t_env	*ft_lstnew(char *name, char *value)
{
	t_env	*ptr;

	ptr = malloc(sizeof(t_env));
	if (ptr == NULL)
		return (NULL);
	ptr->var_name = ft_strdup(name);
	ptr->var_value = ft_strdup(value);
	ptr->next = NULL;
	return (ptr);
}
