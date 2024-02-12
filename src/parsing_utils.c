/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 20:25:48 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/11 20:18:43 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	cmd_error_print(char *str, char **arr)
// {
// 	ft_putstr_fd("pipex: ", 2);
// 	ft_putstr_fd(str, 2);
// 	ft_putendl_fd(": command not found", 2);
// 	ft_free(arr);
// 	exit(127);
// }

void	cmd_error_print(char *str, char **arr)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd("command not found: ", 2);
	ft_putendl_fd(str, 2);
	ft_free(arr);
	exit(127);
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
