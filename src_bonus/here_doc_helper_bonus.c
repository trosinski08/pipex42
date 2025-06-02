/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_helper_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:45:00 by trosinsk          #+#    #+#             */
/*   Updated: 2024/06/02 14:45:00 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	handle_write_error(char *line, char *trimmed_line,
	int pipe_fd_write_end)
{
	perror("pipex: write here_doc_helper");
	free(line);
	free(trimmed_line);
	close(pipe_fd_write_end);
	exit(EXIT_FAILURE);
}

static int	is_delimiter(char *trimmed_line, char *delimiter)
{
	size_t	delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	return (ft_strncmp(trimmed_line, delimiter, delimiter_len) == 0
		&& ft_strlen(trimmed_line) == delimiter_len);
}

void	here_doc_helper(char *line, char *delimiter, int pipe_fd_write_end)
{
	char	*trimmed_line;

	if (!line)
		return ;
	trimmed_line = ft_strtrim(line, "\n");
	if (!trimmed_line)
	{
		free(line);
		return ;
	}
	if (is_delimiter(trimmed_line, delimiter))
	{
		free(line);
		free(trimmed_line);
		close(pipe_fd_write_end);
		exit(EXIT_SUCCESS);
	}	if (write(pipe_fd_write_end, line, ft_strlen(line)) == -1 ||
		write(pipe_fd_write_end, "\n", 1) == -1)
		handle_write_error(line, trimmed_line, pipe_fd_write_end);
	free(line);
	free(trimmed_line);
}
