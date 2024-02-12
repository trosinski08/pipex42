/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:32:00 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/12 12:59:46 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// sleep(10000);

void	parser(char *cmd, char **envpath)
{
	char	**cmd_val;
	char	*path;

	remove_chars(cmd, "\\");
	if (ft_strnstr(cmd, "./", ft_strlen(cmd)) && ft_strchr(cmd, ' ') != 0)
	{
		path = get_path(cmd, envpath);
		if (execve(path, &cmd, envpath) == -1)
		{
			ft_putstr_fd("pipex: ", 2);
			ft_putstr_fd("command not found: ", 2);
			ft_putendl_fd(str, 2);
			ft_free(arr);
			exit(127);
		}
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

void	here_doc(char *delimiter, int argc)
{
	pid_t	read;
	int		fd[2];
	char	*line;

	if (argc < 6)
		error_here_doc();
	if (pipe(fd) == -1)
		exit(1);
	read = fork();
	if (read == 0)
	{
		close(fd[0]);
		while (mini_gnl(&line))
		{
			if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

int	performer(int in_fd, int argc, char **argv, char **envpath)
{
	int	i;
	int	out_fd;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		i = 3;
		out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		here_doc(argv[2], argc);
	}
	else
	{
		i = 2;
		in_fd = open(argv[1], O_RDONLY, 0644);
		if (in_fd == -1)
			input_error();
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
		out_fd = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (out_fd == -1)
			exit (1);
	}
	while (i < argc - 2)
		pipe_maker(argv[i++], envpath);
	return (out_fd);
}

// sleep(10000);
int	main( int argc, char **argv, char **envpath)
{
	int		in_fd;
	int		out_fd;

	in_fd = 0;
	if (argc >= 5)
	{
		out_fd = performer(in_fd, argc, argv, envpath);
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
		parser(argv[argc - 2], envpath);
		wait(NULL);
	}
	else
		error_argc();
}
