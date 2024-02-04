/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:32:00 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/03 21:12:04 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <process.h>
#include <sys/types.h>

// sleep(10000);
// void	quotes_way(char *cmd, char **envpath)
// {
// 	char	**cmd_val;
// 	char	*path;
// 	char	*cmd_line[3];

// 	cmd_val = ft_split(cmd, ' ');
// 	cmd_line[0] = ft_strdup(cmd_val[0]);
// 	cmd_line[1] = ft_strdup(&cmd[ft_strlen(cmd_val[0]) + 1]);
// 	if ((ft_strchr(cmd, '\'') && ft_strchr(cmd, '\"'))
// 		&& (ft_strchr(cmd, '\'') < ft_strchr(cmd, '\"')))
// 		cmd_line[1] = ft_strtrim(cmd_line[1], "\'");
// 	else
// 	{
// 		cmd_line[1] = ft_strtrim(cmd_line[1], "\'");
// 		cmd_line[1] = ft_strtrim(cmd_line[1], "\"");
// 	}
// 	cmd_line[2] = NULL;
// 	path = get_path(cmd_val[0], envpath);
// 	if (execve(path, cmd_line, envpath) == -1)
// 	{
// 		ft_putstr_fd("pipex: ", 2);
// 		ft_putstr_fd(cmd_val[0], 2);
// 		ft_putendl_fd(": command not found", 2);
// 		ft_free(cmd_val);
// 		exit(127);
// 	}
// }

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
			ft_putstr_fd(path, 2);
			ft_putendl_fd(": command not found", 2);
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

void	error_argc(void)
{
	ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
	exit(1);
}

void	input_error(void)
{
	ft_putendl_fd("pipex: input: No such file or directory", 2);
	exit (1);
}

void	here_doc(char *delimiter, int argc)
{
	pid_t	read;
	int		fd[2];
	char	*line;

	if (argc < 6)
		usage();
	if (pipe(fd) == -1)
		error();
	read = fork();
	if (read == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
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


int	main( int argc, char **argv, char **envpath)
{
	int		i;
	int		infile_fd;
	int		outfile_fd;

	if (argc >= 5)
	{
		
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = 3;
			outfile_fd = open_file(argv[argc - 1], 0);
			here_doc(argv[2], argc);
		}
		else
		{
		i = 2;
		infile_fd = open(argv[1], O_RDONLY, 0644);
		if (infile_fd == -1)
			input_error();
		dup2(infile_fd, STDIN_FILENO);
		close(infile_fd);
		outfile_fd = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (outfile_fd == -1)
			exit (1);
		}
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
