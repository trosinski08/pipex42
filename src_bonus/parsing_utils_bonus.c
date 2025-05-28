/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 20:25:48 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/04 21:10:32 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>  // For perror
#include <stdlib.h> // For exit, EXIT_SUCCESS, EXIT_FAILURE, free
#include <unistd.h> // For write, close

/**
 * @brief Helper for here_doc: processes one line of input.
 * @details Compares line to delimiter. If match, closes pipe and exits child.
 *          Else, writes line to pipe. Exits on write error. Frees line.
 *          Assumes line, delimiter are valid, and pipe_write_fd is open.
 * @param line Input line from get_next_line (has newline).
 * @param delimiter Target delimiter string (no newline).
 * @param pipe_write_fd Write-end file descriptor of the pipe.
 */
void	here_doc_helper(char *line, char *delimiter, int pipe_write_fd)
{
	size_t	delimiter_len;
	size_t	line_len;

	delimiter_len = ft_strlen(delimiter);
	line_len = ft_strlen(line);
	if (line_len == delimiter_len + 1 && \
	line[delimiter_len] == '\n' && \
	ft_strncmp(line, delimiter, delimiter_len) == 0)
	{
		free(line);
		if (close(pipe_write_fd) == -1)
			perror("pipex: hdh close match");
		exit(EXIT_SUCCESS);
	}

	if (write(pipe_write_fd, line, line_len) == -1)
	{
		perror("pipex: hdh write");
		free(line);
		if (close(pipe_write_fd) == -1)
			perror("pipex: hdh close write_err");
		exit(EXIT_FAILURE);
	}
	free(line);
}

void	remove_chars(char *str, char *c)
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

void	quotes_way(char *cmd, char **envpath)
{
	char	**cmd_val;
	char	*path;
	char	*cmd_line[3];
	int		i;

	cmd_val = ft_split(cmd, ' ');
	cmd_line[0] = ft_strdup(cmd_val[0]);
	i = ft_strlen(cmd_val[0]) + 1;
	while (cmd[i] == ' ')
		i++;
	cmd_line[1] = ft_strdup(&cmd[i]);
	if ((ft_strchr(cmd, '\'') && ft_strchr(cmd, '\"'))
		&& (ft_strchr(cmd, '\'') < ft_strchr(cmd, '\"')))
		cmd_line[1] = ft_strtrim(cmd_line[1], "\'");
	else
	{
		cmd_line[1] = ft_strtrim(cmd_line[1], "\'");
		cmd_line[1] = ft_strtrim(cmd_line[1], "\"");
	}
	cmd_line[2] = NULL;
	path = get_path(cmd_val[0], envpath);
	if (execve(path, cmd_line, envpath) == -1)
		cmd_error_print(cmd_line[0], cmd_line);
}

char	**envpath_create(char **envpath)
{
	char	*path[2];
	char	**new_path;

	path[0] = "/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin";
	path[1] = NULL;
	new_path = ft_split(path[0], ':');
	return (new_path);
}
// void	cmd_error_print(char *str, char **arr)
// {
// 	ft_putstr_fd("pipex: ", 2);
// 	ft_putstr_fd(str, 2);
// 	ft_putendl_fd(": command not found", 2);
// 	ft_free(arr);
// 	exit(127);
// }
