/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:10:40 by trosinsk          #+#    #+#             */
/*   Updated: 2024/01/22 07:31:39 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"

void	ft_free(char **tab);
char	*get_path(char *cmd_val, char **env);
char	*my_getenv(char *name, char **env);
char	*ft_char_remove(char *cmd, char c);

#endif