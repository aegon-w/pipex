/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m-boukel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:22:29 by m-boukel          #+#    #+#             */
/*   Updated: 2023/02/25 12:55:08 by m-boukel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *av, int i, int *index)
{
	int	file;

	file = 0;
	if (i == 1)
	{
		file = open(av, O_RDONLY, 0644);
		if (file < 0)
		{
			perror("Error");
			(*index)++;
		}
	}
	else if (i == 2)
	{
		file = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file < 0)
		{
			perror("Error");
			exit(1);
		}
	}
	return (file);
}

void	ft_free1(char **s)
{
	int	j;

	j = 0;
	while (s[j])
		free(s[j++]);
	free(s);
}

void	child(int i, int ac, char **env, char **av)
{
	char	**s;
	int		fd[2];

	while (i < ac - 1)
	{
		s = ft_split(av[i], ' ');
		if (pipe(fd) == -1)
			return ;
		if (!fork())
		{
			if (i < ac - 2)
				dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			execve(get_path(s[0], env), s, env);
			exit(1);
		}
		ft_free1(s);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	int	inf;
	int	outf;
	int	i;

	i = 2;
	if (ac < 5)
	{
		write(2, "Error\n", 7);
		exit(1);
	}
	inf = open_file(av[1], 1, &i);
	outf = open_file(av[ac - 1], 2, &i);
	dup2(inf, 0);
	close(inf);
	dup2(outf, 1);
	close(outf);
	child(i, ac, env, av);
	while (wait(NULL) != -1)
		;
	return (0);
}
