/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochaoui <mochaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:10:31 by himejjad          #+#    #+#             */
/*   Updated: 2023/09/30 20:27:29 by mochaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100

# endif

char	*get_next_line(int fd);
char	*ft_strchr3(const char *s, int c);
size_t	ft_strlen3(const char *str);
char	*ft_strjoin3(char const *s1, char const *s2);
void	*ft_memset3(void *d, int c, size_t n);
void	ft_bzero3(void *s, size_t n);
void	*ft_calloc3(size_t count, size_t size);

#endif