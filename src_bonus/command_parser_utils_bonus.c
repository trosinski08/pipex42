/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:23:00 by trosinsk          #+#    #+#             */
/*   Updated: 2024/06/27 17:23:00 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <errno.h>
#include <string.h>

#define DEFAULT_PATH "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"

static char	*check_direct_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (NULL);
}

static char	*try_path_combinations(char **paths, char *cmd)
{
	char	*exec;
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		exec = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(exec, cmd);
		free(exec);
		if (full_path && access(full_path, F_OK | X_OK) == 0)
		{
			ft_free(paths);
			return (full_path);
		}
		if (full_path)
			free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_clean_path(char *cmd)
{
	char	**paths;
	char	*direct_path;
	char	*path_result;

	direct_path = check_direct_path(cmd);
	if (direct_path)
		return (direct_path);
	paths = ft_split(DEFAULT_PATH, ':');
	if (!paths)
		return (NULL);
	path_result = try_path_combinations(paths, cmd);
	if (path_result)
		return (path_result);
	ft_free(paths);
	return (NULL);
}

void	handle_execve_error(char *path, char **cmd_val, char **clean_env)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(cmd_val[0], 2);
	if (errno == EACCES)
		ft_putendl_fd(": Permission denied", 2);
	else if (errno == ENOENT)
		ft_putendl_fd(": No such file or directory", 2);
	else
		ft_putendl_fd(": command not found", 2);
	free(path);
	ft_free(cmd_val);
	free_clean_env(clean_env);
	exit(126);
}

void	handle_path_error(char **cmd_val)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(cmd_val[0], 2);
	ft_putendl_fd(": command not found", 2);
	ft_free(cmd_val);
	exit(127);
}
