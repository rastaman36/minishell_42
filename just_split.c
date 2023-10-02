/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   just_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himejjad <himejjad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:32:31 by mochaoui          #+#    #+#             */
/*   Updated: 2023/10/02 19:09:23 by himejjad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_strings(const char *str, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] != '\0' && str[i] == c)
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && str[i] != c)
			i++;
	}
	return (count);
}

size_t	check_len_of_word(const char *str, char c)
{
	size_t	a;

	a = 0;
	while (str[a] != '\0' && str[a] != c)
		a++;
	return (a);
}

char	*alocation_string(const char *str, char c)
{
	char	*word;
	size_t	a;
	size_t	lenword;

	a = 0;
	lenword = check_len_of_word(str, c);
	word = (char *)malloc(sizeof(char) * (lenword + 1));
	while (a < lenword)
	{
		word[a] = str[a];
		a++;
	}
	word[a] = '\0';
	return (word);
}

char	**ft_free(char **str, size_t i)
{
	while (i--)
		free(str[i]);
	free(str);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	strings = (char **)malloc(sizeof(char *) * (count_strings(s, c) + 1));
	if (!strings)
		return (NULL);
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0')
		{
			strings[i] = alocation_string(s, c);
			if (!strings[i])
				return (ft_free(strings, i));
			i++;
		}
		while (*s != '\0' && *s != c)
			s++;
	}
	strings[i] = 0;
	return (strings);
}
