/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 02:33:42 by trosinsk          #+#    #+#             */
/*   Updated: 2024/06/24 02:33:42 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// We're now using the global flush_gnl_buffers function
static void	here_doc_child_logic(int *pipe_fd, char *delimiter)
{
	char	*line;

	close(pipe_fd[0]);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			close(pipe_fd[1]);
			flush_gnl_buffers();
			exit(EXIT_SUCCESS);
		}
		here_doc_helper(line, delimiter, pipe_fd[1]);
	}
}

static void	here_doc_parent_logic(int *pipe_fd, pid_t child_pid)
{
	int	status;

	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("pipex: dup2 here_doc_parent");
		close(pipe_fd[0]);
		waitpid(child_pid, NULL, 0);
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	waitpid(child_pid, &status, 0);
}

void	here_doc(char *delimiter, int argc)
{
	pid_t	child_pid;
	int		pipe_fd[2];

	if (argc < 6)
		error_here_doc();
	if (pipe(pipe_fd) == -1)
	{
		perror("pipex: pipe here_doc");
		exit(EXIT_FAILURE);
	}
	child_pid = fork();
	if (child_pid < 0)
	{
		perror("pipex: fork here_doc");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
		here_doc_child_logic(pipe_fd, delimiter);
	else
		here_doc_parent_logic(pipe_fd, child_pid);
}
