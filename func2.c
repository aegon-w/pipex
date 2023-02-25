/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m-boukel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:06:16 by m-boukel          #+#    #+#             */
/*   Updated: 2023/02/16 12:08:01 by m-boukel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i] && i < n)
	{
		j = 0;
		while (str[i + j] == to_find[j] && (i + j) < n)
		{
			j++;
			if (to_find[j] == '\0')
			{
				return ((char *)str + i);
			}
		}
		i++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	p = malloc(len + 1);
	if (!p)
		return (NULL);
	while (i < len && s1[j])
	{
		p[i++] = s1[j++];
	}
	j = 0;
	while (i < len && s2[j])
	{
		p[i++] = s2[j++];
	}
	p[i] = '\0';
	return ((char *)p);
}
