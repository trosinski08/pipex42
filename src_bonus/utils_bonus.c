/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 03:25:42 by trosinsk          #+#    #+#             */
/*   Updated: 2024/06/24 03:25:42 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../../libft/include/libft.h"

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

static char	*check_direct_path(char *cmd)
{
	if (!cmd || !cmd[0])
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*exec;
	char	*path;
	int		i;

	i = 0;
	while (paths[i])
	{
		exec = ft_strjoin(paths[i], "/");
		path = ft_strjoin(exec, cmd);
		free(exec);
		if (path)
		{
			if (access(path, F_OK | X_OK) == 0)
			{
				ft_free(paths);
				return (path);
			}
			free(path);
		}
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	**paths;
	char	*path_env;
	char	*result;

	result = check_direct_path(cmd);
	if (result)
		return (result);
	path_env = my_getenv("PATH", env);
	if (!path_env)
		path_env = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, cmd);
	ft_free(paths);
	return (result);
}
