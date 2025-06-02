/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 02:33:42 by trosinsk          #+#    #+#             */
/*   Updated: 2024/06/24 02:33:42 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	wait_for_children(int num_children, pid_t last_pid)
{
	int	i;
	int	status;

	i = 0;
	while (i < num_children)
	{
		wait(&status);
		i++;
	}
	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

static pid_t	execute_last_command(char *cmd, char **envpath)
{
	pid_t	last_pid;

	last_pid = fork();
	if (last_pid < 0)
	{
		perror("pipex: fork last_pid");
		exit(EXIT_FAILURE);
	}
	if (last_pid == 0)
	{
		parser(cmd, envpath);
	}
	return (last_pid);
}

int	main(int argc, char **argv, char **envpath)
{
	int		out_fd;
	int		num_children;
	pid_t	last_pid;
	int		exit_code;

	if (argc < 5)
		error_argc();
	if (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6)
		error_here_doc();
	out_fd = performer(argc, argv, envpath);
	if (dup2(out_fd, STDOUT_FILENO) == -1)
	{
		perror("pipex: dup2 main stdout");
		close(out_fd);
		exit(EXIT_FAILURE);
	}
	close(out_fd);
	last_pid = execute_last_command(argv[argc - 2], envpath);
	num_children = argc - 3 - (ft_strncmp(argv[1], "here_doc", 8) == 0);
	exit_code = wait_for_children(num_children, last_pid);
	flush_gnl_buffers();
	return (exit_code);
}
