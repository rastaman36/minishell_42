/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:32:34 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/02 19:06:15 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expanding_env(char *s, t_env *env)
{
	int		a;
	char	*string;
	int		var;
	char	*f;

	a = 0;
	string = ft_strdup("");
	var = 0;
	f = s;
	while (f[a])
	{
		if (f[a] == '$')
			ft_norm(env, &f, &a, &string);
		else if (var != 2 && f[a] == '\'')
		{
			a++;
			while (f[a] && f[a] != '\'')
				string = ft_strjoin(string, f[a++]);
			a++;
		}
		else
			string = ft_strjoin(string, f[a++]);
	}
	free(s);
	return (string);
}
