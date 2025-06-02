/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:31:43 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/04 19:54:24 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/include/libft.h"

char	*get_path(char *cmd_val, char **env);
char	*my_getenv(char *name, char **env);
void	ft_free(char **tab);
void	cmd_error_print(char *str, char **arr);
void	quotes_way(char *cmd, char **envpath);
void	remove_chars(char *str, char *c);
void	error_handler(char *path, char *cmd, char **cmd_line);
void	error_argc(void);
void	input_error(void);
void	error_here_doc(void);
void	here_doc(char *delimiter, int argc);
void	parser(char *cmd, char **envpath);
char	**envpath_create(char **envpath);
void	pipe_maker(char *cmd, char **envpath);
void	here_doc_helper(char *line, char *delimiter, int pipe_fd_write_end);
void	handle_input_redirection(int argc, char **argv,\
				int *cmd_start_index, int is_here_doc);
int		performer(int argc, char **argv, char **envpath);
char	**create_clean_env(char **original_env);
void	free_clean_env(char **env);

/* Functions moved to command_parser_utils_bonus.c */
char	*get_clean_path(char *cmd);
void	handle_path_error(char **cmd_val);
void	handle_execve_error(char *path, char **cmd_val, char **clean_env);

#endif