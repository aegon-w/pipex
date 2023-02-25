/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m-boukel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:56:06 by m-boukel          #+#    #+#             */
/*   Updated: 2023/02/25 11:22:10 by m-boukel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	*stor(char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->cmd1 = ft_split(av[2], ' ');
	data->cmd2 = ft_split(av[3], ' ');
	data->inf = av[1];
	data->outf = av[4];
	return (data);
}

void	cmd1(t_data *data, int *_pipe, char **env)
{
	int	fdin;

	fdin = open(data->inf, O_RDONLY);
	if (fdin == -1)
	{
		perror("Error");
		exit(1);
	}
	dup2(_pipe[1], 1);
	dup2(fdin, 0);
	close(_pipe[0]);
	close(_pipe[1]);
	execve(get_path(data->cmd1[0], env), data->cmd1, env);
	write(2, "Error : command not found\n", 27);
	exit(127);
}

void	cmd2(t_data *data, int *_pipe, char **env)
{
	int	fdout;

	fdout = open(data->outf, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdout == -1)
	{
		perror("Error");
		exit(1);
	}
	dup2(_pipe[0], 0);
	dup2(fdout, 1);
	close(_pipe[1]);
	close(_pipe[0]);
	execve(get_path(data->cmd2[0], env), data->cmd2, env);
	write(2, "Error : command not found\n", 27);
	exit(127);
}

pid_t	forking(void)
{
	pid_t	id;

	id = fork();
	if (id == -1)
	{
		perror("Error ");
		exit(1);
	}
	return (id);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	t_data	*data;
	pid_t	id1;
	pid_t	id2;

	data = stor(av);
	if (ac != 5)
	{
		write(2, "CHECK_ARGS\n", 12);
		exit(1);
	}
	if (pipe(fd) == -1)
		return (0);
	id1 = forking();
	if (id1 == 0)
		cmd1(data, fd, env);
	id2 = forking();
	if (id2 == 0)
		cmd2(data, fd, env);
	close(fd[0]);
	close(fd[1]);
	while (wait(NULL) != -1)
		;
	return (0);
}
