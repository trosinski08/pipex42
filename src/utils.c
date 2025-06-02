/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 22:11:43 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/03 20:05:40 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**envpath_create(char **envpath)
{
	char	*path[2];
	char	**new_path;

	(void)envpath;
	path[0] = "/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin";
	path[1] = NULL;
	new_path = ft_split(path[0], ':');
	return (new_path);
}

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

	// if (!env[0])
	// 	env = envpath_create(env);
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

void	helper(char *path, char *cmd, char **exec, char **path_part)
{
	*path_part = ft_strjoin(path, "/");
	*exec = ft_strjoin(*path_part, cmd);
	free(*path_part);
	if (access(*exec, F_OK | X_OK) == 0)
		return ;
	free(*exec);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;

	i = -1;
	if (env[0] != NULL)
		allpath = ft_split(my_getenv("PATH", env), ':');
	else
		allpath = envpath_create(env);
	if (!allpath)
		return (NULL);
	while (allpath[++i])
		helper(allpath[i], cmd, &exec, &path_part);
	return (ft_free(allpath), NULL);
}
