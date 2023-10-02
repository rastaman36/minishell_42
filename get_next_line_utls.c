/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <mochaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:57:22 by himejjad          #+#    #+#             */
/*   Updated: 2023/09/30 20:27:41 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr3(const char *s, int c)
{
	size_t	a;

	a = 0;
	while (s[a])
	{
		if ((unsigned char)s[a] == (unsigned char)c)
			return ((char *)s + a);
		a++;
	}
	if ((unsigned char)c == 0)
		return ((char *)s + a);
	return (NULL);
}

size_t	ft_strlen3(const char *str)
{
	size_t	a;

	a = 0;
	while (str[a])
		a++;
	return (a);
}

char	*ft_strjoin3(char const *s1, char const *s2)
{
	int		a;
	int		on;
	char	*string;

	if (!s1 || !s2)
		return (NULL);
	on = ft_strlen3(s1);
	string = (char *)malloc(sizeof(char) * on + ft_strlen3(s2) + 1);
	if (!string)
		return (NULL);
	a = 0;
	while (s1[a])
	{
		string[a] = s1[a];
		a++;
	}
	a = 0;
	while (s2[a])
		string[on++] = s2[a++];
	string[on] = '\0';
	return (string);
}

void	*ft_memset3(void *d, int c, size_t n)
{
	size_t			a;
	unsigned char	*w;

	w = (unsigned char *)d;
	a = 0;
	while (a < n)
	{
		w[a] = c;
		a++;
	}
	return (d);
}

void	*ft_calloc3(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_memset3(ptr, 0, size * count);
	return (ptr);
}
