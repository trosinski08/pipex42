/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 03:25:42 by trosinsk          #+#    #+#             */
/*   Updated: 2024/06/24 03:25:42 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../../libft/include/libft.h"

// Function to check if a string contains only spaces
static int	is_space_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// Function to handle command parsing and execution
static void	execute_command(char *cmd, char **envp)
{
	char	*path;
	char	**args;

	if (!cmd || is_space_str(cmd))
		return ;
	args = ft_split(cmd, ' ');
	if (!args || !args[0])
	{
		ft_free(args);
		return ;
	}
	path = get_path(args[0], envp);
	if (!path)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd("\n", 2);
		ft_free(args);
		exit(127);
	}
	execve(path, args, envp);
	perror("pipex: execute_command execve");
	ft_free(args);
	free(path);
	exit(EXIT_FAILURE);
}

// Function to process a single command
static void	process_command(char *cmd, char **envp) __attribute__((unused));

static void	process_command(char *cmd, char **envp)
{
	char	**cmds;
	int		i;

	cmds = ft_split(cmd, '|');
	if (!cmds)
		return ;
	i = 0;
	while (cmds[i])
	{
		cmds[i] = ft_strtrim(cmds[i], " ");
		execute_command(cmds[i], envp);
		i++;
	}	ft_free(cmds);
}
