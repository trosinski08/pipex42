/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 03:25:42 by trosinsk          #+#    #+#             */
/*   Updated: 2024/06/24 03:25:42 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>  // For setbuf, perror
#include <unistd.h> // For isatty

void	parent_process_logic(int *fd)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("pipex: dup2 parent_process_logic");
		close(fd[0]);
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
}

static void	child_process_logic(int *fd, char *cmd, char **envpath)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("pipex: dup2 child_process_logic");
		close(fd[1]);
		exit(EXIT_FAILURE);
	}
	close(fd[1]);
	parser(cmd, envpath);
}

void	pipe_maker(char *cmd, char **envpath)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
	{
		perror("pipex: pipe_maker pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("pipex: pipe_maker fork");
		close(fd[0]);
		close(fd[1]);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_process_logic(fd, cmd, envpath);
	else
	{
		parent_process_logic(fd);
		waitpid(pid, &status, 0);
	}
}
