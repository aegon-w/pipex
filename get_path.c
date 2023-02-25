/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m-boukel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:58:37 by m-boukel          #+#    #+#             */
/*   Updated: 2023/02/25 12:56:51 by m-boukel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_lines(char **env)
{
	char	**paths;
	char	*a;
	int		i;

	i = 0;
	a = NULL;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", ft_strlen(env[i])))
			a = env[i];
		i++;
	}
	if (!a)
	{
		write(2, "command not found\n", 19);
		exit(127);
	}
	paths = ft_split(a + 5, ':');
	return (paths);
}

void	check_cmd(char *cmd, char **op)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < (int)ft_strlen(cmd))
	{
		if (cmd[i] == '/' || cmd[0] == '.')
		{
			while (op[j])
				free(op[j++]);
			write(2, "Error : No such file or directory\n", 35);
			exit(1);
		}
		i++;
	}
}

char	*get_path(char *cmd, char **env)
{
	int		j;
	char	**op;
	char	*path;
	int		i;

	j = 0;
	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	op = get_lines(env);
	check_cmd(cmd, op);
	while (op[j])
	{
		op[j] = ft_strjoin(op[j], "/");
		path = ft_strjoin(op[j], cmd);
		free(op[j]);
		if (access(path, X_OK) != -1)
			return (path);
		free(path);
		j++;
	}
	write(2, "command not found\n", 19);
	return (exit(127), NULL);
}
