/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 03:25:42 by trosinsk          #+#    #+#             */
/*   Updated: 2024/06/27 17:23:00 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <errno.h>
#include <string.h>

/* Functions moved to command_parser_utils_bonus.c:
 * - get_clean_path
 * - handle_execve_error
 * - handle_path_error
 */

static void	handle_env_error(char *path, char **cmd_val)
{
	ft_putstr_fd("pipex: memory allocation failed\n", 2);
	free(path);
	ft_free(cmd_val);
	exit(1);
}

static void	handle_command_execution(char **cmd_val, char **envpath)
{
	char	*path;
	char	**clean_env;

	path = get_clean_path(cmd_val[0]);
	if (!path)
		handle_path_error(cmd_val);
	clean_env = create_clean_env(envpath);
	if (!clean_env)
		handle_env_error(path, cmd_val);
	if (execve(path, cmd_val, clean_env) == -1)
		handle_execve_error(path, cmd_val, clean_env);
}

void	parser(char *cmd, char **envpath)
{
	char	**cmd_val;

	remove_chars(cmd, "\\");
	if (!ft_strchr(cmd, '\'') && !ft_strchr(cmd, '\"'))
	{
		cmd_val = ft_split(cmd, ' ');
		if (!cmd_val || !cmd_val[0])
		{
			if (cmd_val)
				ft_free(cmd_val);
			exit(127);
		}
		handle_command_execution(cmd_val, envpath);
	}
	else
		quotes_way(cmd, envpath);
}
