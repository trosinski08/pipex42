/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:09:46 by trosinsk          #+#    #+#             */
/*   Updated: 2024/01/22 15:45:32 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

void	parser(char *cmd, char **envpath)
{
	char	**cmd_val;
	char	*path;

	if (ft_strncmp(cmd, "awk", ft_strlen("awk")) == 0)
		cmd = ft_char_remove(cmd, '\'');
	cmd_val = ft_split(cmd, ' ');
	path = get_path(cmd_val[0], envpath);
	if (execve(path, cmd_val, envpath) == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(cmd_val[0], 2);
		ft_putendl_fd(": command not found", 2);
		ft_free(cmd_val);
		exit(127);
	}
}

void	infile_processing(char **argv, int *fd, char **envpath)
{
	int	fds;

	fds = open(argv[1], O_RDONLY, 0644);
	if (fds == -1)
	{
		ft_putendl_fd("pipex: input: No such file or directory", 2);
		exit (1);
	}
	dup2(fds, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fds);
	parser(argv[2], envpath);
}

void	outfile_processing(char **argv, int *fd, char **envpath)
{
	int	fds;

	fds = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fds == -1)
		exit (1);
	dup2(fds, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fds);
	parser(argv[3], envpath);
}

int	main(int argc, char **argv, char **envpath)
{
	int		fd[2];
	int		status;
	pid_t	pid1;

	if (argc != 5)
	{
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
		exit(1);
	}
	if (pipe(fd) == -1)
		exit (1);
	pid1 = fork();
	if (pid1 < 0)
		exit (1);
	if (pid1 == 0)
		infile_processing(argv, fd, envpath);
	outfile_processing(argv, fd, envpath);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
		exit(1);
}
