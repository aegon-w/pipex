/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m-boukel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 21:22:45 by m-boukel          #+#    #+#             */
/*   Updated: 2023/02/22 20:27:53 by m-boukel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct data
{
	char	*inf;
	char	**cmd1;
	char	**cmd2;
	char	*outf;
}			t_data;

typedef struct info
{
	int	inf;
	int	outf;
	int	i;
}			t_info;

char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *str);
char		*ft_strnstr(const char *str, const char *to_find, size_t n);
char		*get_path(char *cmd, char **env);
#endif