/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:32:00 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/04 20:00:46 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// sleep(10000);

void	pipe_maker(char *cmd, char **envpath)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	if (pid < 0)
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

int	infile_processing(char *str)
{
	int	in_fd;

	in_fd = open(str, O_RDONLY, 0644);
	if (in_fd == -1)
		input_error();
	dup2(in_fd, STDIN_FILENO);
	close(in_fd);
	return (in_fd);
}

int	outfile_processing(char *str)
{
	int	out_fd;

	out_fd = outfile_processing(str);
	open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (out_fd == -1)
		exit (1);
	return (out_fd);
}

void	performer(int out_fd, char *str, char **envpath)
{
	int	status;

	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	parser(str, envpath);
	wait(NULL);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
		exit(1);
}

int	main( int argc, char **argv, char **envpath)
{
	int		i;
	int		in_fd;
	int		out_fd;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = 3;
			out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			here_doc(argv[2], argc);
		}
		else
		{
			i = 2;
			in_fd = infile_processing(argv[1]);
			out_fd = outfile_processing(argv[argc - 1]);
		}
		while (i < argc - 2)
			pipe_maker(argv[i++], envpath);
		performer(out_fd, argv[argc - 2], envpath);
	}
	else
		error_argc();
}
