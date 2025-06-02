/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:09:46 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/11 19:46:29 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// TO DO
//check if "" are closed, ex.: if strchr != strrchr

static void	remove_chars(char *str, char *c)
{
	char	*char_pos;
	int		i;

	i = 0;
	if (str != NULL)
	{
		while (c[i] != '\0')
		{
			char_pos = ft_strchr(str, c[i]);
			while (char_pos != NULL)
			{
				ft_strlcpy(char_pos, char_pos + 1, ft_strlen(char_pos));
				char_pos = ft_strchr(str, c[i]);
			}
			i++;
		}
	}
}

void	parser(char *cmd, char **envpath)
{
	char	**cmd_val;
	char	*path;

	remove_chars(cmd, "\\");
	if (ft_strnstr(cmd, "./", ft_strlen(cmd)) && ft_strchr(cmd, ' ') != 0)
	{
		path = get_path(cmd, envpath);
		if (execve(path, &cmd, envpath) == -1)
			exit(0);
	}
	if (!ft_strchr(cmd, '\'') && !ft_strchr(cmd, '\"'))
	{
		cmd_val = ft_split(cmd, ' ');
		path = get_path(cmd_val[0], envpath);
		if (execve(path, cmd_val, envpath) == -1)
			cmd_error_print(cmd_val[0], cmd_val);
	}
	else
		quotes_way(cmd, envpath);
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
	close(fd[0]);
	dup2(fds, STDIN_FILENO);
	close(fds);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	parser(argv[2], envpath);
}

void	outfile_processing(char **argv, int *fd, char **envpath)
{
	int	fds;

	fds = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fds == -1)
		exit (1);
	close(fd[1]);
	dup2(fds, STDOUT_FILENO);
	close(fds);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	parser(argv[3], envpath);
}

	// sleep(10000);
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
	waitpid(pid1, &status, 0);
	close (STDIN_FILENO);
	close (STDOUT_FILENO);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	else
		exit(1);
}
