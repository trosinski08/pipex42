/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 22:11:43 by trosinsk          #+#    #+#             */
/*   Updated: 2024/01/22 16:35:59 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_char_remove(char *cmd, char c)
{
	char	*dst;

	dst = NULL;
	while (*cmd)
	{
		if (*cmd != c)
		{
			*dst = *cmd;
			dst++;
		}
		cmd++;
	}
	*dst = '\0';
	return (dst);
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

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**cmd_val;

	i = -1;
	allpath = ft_split(my_getenv("PATH", env), ':');
	cmd_val = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, cmd_val[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free(cmd_val);
			return (exec);
		}
		free(exec);
	}
	ft_free(allpath);
	ft_free(cmd_val);
	return (cmd);
}
