/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 23:01:37 by himejjad          #+#    #+#             */
/*   Updated: 2023/10/02 19:11:31 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create_node(char *str)
{
	t_list	*new_node;

	if (!str)
		return (NULL);
	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node != NULL)
	{
		new_node->str = strdup(str);
		new_node->next = NULL;
	}
	return (new_node);
}

t_list	*create_linked_list(char **str)
{
	int		i;
	t_list	*head;
	t_list	*current;

	head = create_node(str[0]);
	current = head;
	i = 1;
	while (str[i])
	{
		current->next = create_node(str[i]);
		current = current->next;
		i++;
	}
	return (head);
}

void	display_list(char **string2)
{
	int	a;

	a = 0;
	while (string2[a])
	{
		printf("%s\n", string2[a]);
		a++;
	}
}

void	free_linked_list(t_list *head)
{
	t_list	*next;
	t_list	*current;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}
