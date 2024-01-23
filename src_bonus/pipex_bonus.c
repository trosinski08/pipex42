/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:32:00 by trosinsk          #+#    #+#             */
/*   Updated: 2024/01/23 01:59:49 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// sleep(10000);
void	parser(char *cmd, char **envpath)
{
	char	**cmd_val;
	char	*path;

	cmd_val = ft_split(cmd, ' ');
	path = get_path(cmd_val[0], envpath);
	if (execve(path, cmd_val, envpath) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(cmd_val[0], 2);
		ft_free(cmd_val);
		exit(127);
	}
}

void	pipe_maker(char *cmd, char **envpath)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		parser(cmd, envpath);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

void	error_argc(void)
{
	ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
	exit(1);
}

int	main( int argc, char **argv, char **envpath)
{
	int		i;
	int		infile_fd;
	int		outfile_fd;

	if (argc >= 5)
	{
		i = 2;
		infile_fd = open(argv[1], O_RDONLY, 0644);
		if (infile_fd == -1)
			exit (0);
		outfile_fd = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (outfile_fd == -1)
			exit (1);
		dup2(infile_fd, STDIN_FILENO);
		close(infile_fd);
		while (i < argc - 2)
			pipe_maker(argv[i++], envpath);
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
		parser(argv[argc - 2], envpath);
		wait(NULL);
	}
	else
		error_argc();
}
