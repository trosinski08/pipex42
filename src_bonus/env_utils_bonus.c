/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 03:25:42 by trosinsk          #+#    #+#             */
/*   Updated: 2024/06/24 03:25:42 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

#define DEFAULT_PATH "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"

static int	is_essential_var(char *env_var)
{
	if (ft_strncmp(env_var, "HOME=", 5) == 0
		|| ft_strncmp(env_var, "USER=", 5) == 0
		|| ft_strncmp(env_var, "SHELL=", 6) == 0
		|| ft_strncmp(env_var, "TERM=", 5) == 0)
		return (1);
	return (0);
}

static void	cleanup_env(char **clean_env, int j)
{
	while (--j >= 0)
		free(clean_env[j]);
	free(clean_env);
}

char	**create_clean_env(char **original_env)
{
	char	**clean_env;
	int		i;
	int		j;

	clean_env = malloc(sizeof(char *) * 10);
	if (!clean_env)
		return (NULL);
	i = 0;
	j = 0;
	while (original_env[i])
	{
		if (is_essential_var(original_env[i]))
		{
			clean_env[j] = ft_strdup(original_env[i]);
			if (!clean_env[j])
				return (cleanup_env(clean_env, j), NULL);
			j++;
		}
		i++;
	}
	clean_env[j] = ft_strdup("PATH=" DEFAULT_PATH);
	if (!clean_env[j])
		return (cleanup_env(clean_env, j), NULL);
	clean_env[++j] = NULL;
	return (clean_env);
}

void	free_clean_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
