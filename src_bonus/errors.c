/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:53:47 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/11 20:19:27 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_argc(void)
{
	ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
	exit(1);
}

void	input_error(void)
{
	ft_putendl_fd("pipex: input: No such file or directory", 2);
	exit (1);
}

void	error_here_doc(void)
{
	char	*s;

	s = "./pipex \"here_doc\" <LIMITER> <cmd> <cmd1> <...> <file>\n";
	ft_putstr_fd(s, 2);
	exit(1);
}

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
