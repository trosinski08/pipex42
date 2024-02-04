/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:31:43 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/03 21:11:35 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
// # include <unistd.h>
#include <io.h>
// # include <sys/wait.h>
# include <fcntl.h>
// # include "../libft/libft.h"

char	*get_path(char *cmd_val, char **env);
char	*my_getenv(char *name, char **env);
void	ft_free(char **tab);
void	cmd_error_print(char *str, char **arr);
void	quotes_way(char *cmd, char **envpath);
void	remove_chars(char *str, char *c);

#endif