/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_io_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 02:33:42 by trosinsk          #+#    #+#             */
/*   Updated: 2024/06/24 02:33:42 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	handle_regular_input(char *filename, int *cmd_start_index)
{
	int	in_fd;

	*cmd_start_index = 2;
	in_fd = open(filename, O_RDONLY);
	if (in_fd == -1)
	{
		perror(filename);
		exit(EXIT_FAILURE);
	}
	if (dup2(in_fd, STDIN_FILENO) == -1)
	{
		perror("pipex: dup2 stdin");
		close(in_fd);
		exit(EXIT_FAILURE);
	}
	close(in_fd);
}

void	handle_input_redirection(int argc, char **argv,
	int *cmd_start_index, int is_here_doc)
{
	if (is_here_doc)
	{
		*cmd_start_index = 3;
		here_doc(argv[2], argc);
	}
	else
		handle_regular_input(argv[1], cmd_start_index);
}

int	open_outfile_fd(int argc, char **argv, int is_here_doc_case)
{
	int	out_fd;
	int	flags;

	if (is_here_doc_case)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	out_fd = open(argv[argc - 1], flags, 0644);
	if (out_fd == -1)
	{
		perror(argv[argc - 1]);
		exit(EXIT_FAILURE);
	}
	return (out_fd);
}

int	performer(int argc, char **argv, char **envpath)
{
	int	cmd_idx;
	int	out_fd;
	int	is_here_doc;

	is_here_doc = (ft_strncmp(argv[1], "here_doc", 8) == 0);
	if (is_here_doc && argc < 6)
		error_here_doc();
	else if (!is_here_doc && argc < 5)
		error_argc();
	handle_input_redirection(argc, argv, &cmd_idx, is_here_doc);
	out_fd = open_outfile_fd(argc, argv, is_here_doc);
	while (cmd_idx < argc - 2)
	{
		pipe_maker(argv[cmd_idx], envpath);
		cmd_idx++;
	}
	return (out_fd);
}
