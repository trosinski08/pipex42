/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:32:00 by trosinsk          #+#    #+#             */
/*   Updated: 2024/02/12 12:59:46 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>    // For perror
#include <stdlib.h>   // For exit, EXIT_SUCCESS, EXIT_FAILURE, free
#include <unistd.h>   // For execve
#include <fcntl.h>    // Required for open() flags (O_WRONLY, O_CREAT, O_TRUNC, O_APPEND)

// Assume ft_free_tab is declared (e.g., in libft.h, included via pipex_bonus.h)
// void ft_free_tab(char **tab);
// Assume get_path is declared (e.g., in libft.h or pipex_bonus.h)
// char *get_path(char *cmd_name, char **env_paths);
// Assume quotes_way is declared (e.g., in pipex_bonus.h)
// void quotes_way(char *full_cmd, char **env_paths);
// Assume remove_chars is declared (e.g., in pipex_bonus.h)
// void remove_chars(char *str, char *chars_to_remove);

/**
 * @brief Parses and executes a command in a child process.
 * @details Removes backslashes from cmd. If cmd has quotes, delegates to
 *          \`quotes_way\`. Else, splits cmd, finds path via \`get_path\`,
 *          executes via \`execve\`. Handles \`ft_split\`, \`get_path\`,
 *          \`execve\` errors by printing to stderr, freeing memory,
 *          and exiting (EXIT_FAILURE or 127).
 *          Always terminates the child process.
 * @param cmd Command string, modified by \`remove_chars\`.
 * @param envpath Environment PATH array for \`get_path\`.
 */
void	parser(char *cmd, char **envpath)
{
	char	**cmd_val;
	char	*path;

	remove_chars(cmd, "\\\\");
	if (ft_strchr(cmd, '\'') || ft_strchr(cmd, '\"'))
		quotes_way(cmd, envpath);
	else
	{
		cmd_val = ft_split(cmd, ' ');
		if (!cmd_val || !cmd_val[0])
		{
			ft_putendl_fd("pipex: split error or empty cmd", 2);
			if (cmd_val)
				ft_free(cmd_val);
			exit(EXIT_FAILURE);
		}
		path = get_path(cmd_val[0], envpath);
		if (!path)
		{
			ft_putstr_fd(cmd_val[0], 2); // Use ft_putstr_fd for consistency
			ft_putendl_fd(": command not found", 2); // Standard error message
			ft_free(cmd_val);
			exit(127);
		}
		if (execve(path, cmd_val, envpath) == -1) // Check execve return
		{
			perror(cmd_val[0]); // perror is good for execve errors
			free(path); // Free path if execve fails
			ft_free(cmd_val);
			exit(EXIT_FAILURE); // Or a more specific error code if desired
		}
		// These lines are not reached if execve is successful
		// free(path); 
		// ft_free(cmd_val);
		// exit(EXIT_FAILURE);
	}
}

/**
 * @brief Handles child process logic for \`pipe_maker\`.
 * @details Redirects standard output to the write end of the pipe (fd[1]),
 *          closes both pipe file descriptors, and then calls \`parser\` to
 *          execute the command. If \`dup2\` fails, it prints an error using
 *          \`perror\` and exits with \`EXIT_FAILURE\`.
 * @param fd Array of two integers representing the pipe file descriptors.
 * @param cmd The command string to be executed by \`parser\`.
 * @param envpath Array of environment path strings for \`parser\`.
 */
static void	child_process_logic(int *fd, char *cmd, char **envpath)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("pipex: dup2 child_process_logic");
		close(fd[1]);
		exit(EXIT_FAILURE);
	}
	close(fd[1]);
	parser(cmd, envpath);
}

/**
 * @brief Handles parent process logic for \`pipe_maker\`.
 * @details Redirects standard input to the read end of the pipe (fd[0]),
 *          and closes both pipe file descriptors. If \`dup2\` fails, it prints
 *          an error using \`perror\` and exits with \`EXIT_FAILURE\`.
 * @param fd Array of two integers representing the pipe file descriptors.
 */
static void	parent_process_logic(int *fd)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("pipex: dup2 parent_process_logic");
		close(fd[0]);
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
}

/**
 * @brief Creates a pipe and forks to execute a command, redirecting I/O.
 * @details Initializes a pipe. Forks a new process. The child process
 *          calls \`child_process_logic\` to redirect its stdout to the
 *          pipe's write end and execute the command. The parent process
 *          calls \`parent_process_logic\` to redirect its stdin to
 *          the pipe's read end. Handles errors from \`pipe()\`
 *          and \`fork()\` by calling \`perror\` and exiting with
 *          \`EXIT_FAILURE\`. The PIDs of child processes are not
 *          returned or stored by this function directly.
 * @param cmd The command string to be executed by the child process.
 * @param envpath Array of environment path strings for command execution.
 */
void	pipe_maker(char *cmd, char **envpath)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		perror("pipex: pipe_maker pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("pipex: pipe_maker fork");
		close(fd[0]);
		close(fd[1]);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_process_logic(fd, cmd, envpath);
	else
		parent_process_logic(fd);
}

/**
 * @brief Handles the child process logic for \`here_doc\`.
 * @details Closes the read end of the pipe. Enters a loop to read lines from
 *          standard input using \`get_next_line\`. If EOF is reached (line is
 *          NULL), it closes the write end of the pipe and exits with
 *          \`EXIT_SUCCESS\`. Otherwise, it calls \`here_doc_helper\` to process
 *          the line (compare with delimiter, write to pipe, or exit).
 * @param pipe_fd Array of two integers for the pipe file descriptors.
 * @param delimiter The delimiter string for \`here_doc_helper\`.
 */
static void	here_doc_child_logic(int *pipe_fd, char *delimiter)
{
	char	*line;

	close(pipe_fd[0]);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			close(pipe_fd[1]);
			exit(EXIT_SUCCESS);
		}
		here_doc_helper(line, delimiter, pipe_fd[1]);
	}
}

/**
 * @brief Handles the parent process logic for \`here_doc\`.
 * @details Closes the write end of the pipe. Redirects standard input to the
 *          read end of the pipe. If \`dup2\` fails, prints an error, closes the
 *          read end, waits for the child, and exits. After successful \`dup2\`,
 *          closes the original read end and waits for the child process to finish.
 * @param pipe_fd Array of two integers for the pipe file descriptors.
 * @param child_pid Process ID of the child process to wait for.
 */
static void	here_doc_parent_logic(int *pipe_fd, pid_t child_pid)
{
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("pipex: dup2 here_doc_parent");
		close(pipe_fd[0]);
		waitpid(child_pid, NULL, 0);
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[0]);
	waitpid(child_pid, NULL, 0);
}

/**
 * @brief Implements here-document functionality.
 * @details Checks for minimum argument count. Creates a pipe and forks.
 *          Child calls \`here_doc_child_logic\` to read input until delimiter.
 *          Parent calls \`here_doc_parent_logic\` to redirect stdin from pipe.
 *          Handles \`pipe\` and \`fork\` errors with \`perror\` and \`exit\`.
 * @param delimiter String marking end of here-document input.
 * @param argc Argument count, used to check if enough args for here_doc.
 */
void	here_doc(char *delimiter, int argc)
{
	pid_t	child_pid;
	int		pipe_fd[2];

	if (argc < 6)
		error_here_doc();
	if (pipe(pipe_fd) == -1)
	{
		perror("pipex: pipe here_doc");
		exit(EXIT_FAILURE);
	}
	child_pid = fork();
	if (child_pid < 0)
	{
		perror("pipex: fork here_doc");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
		here_doc_child_logic(pipe_fd, delimiter);
	else
		here_doc_parent_logic(pipe_fd, child_pid);
}

/**
 * @brief Handles input redirection (file or here_doc) and sets command index.
 * @note Assumes argc has been validated by the caller (\`performer\`).
 * @param argc Argument count (passed to here_doc if needed).
 * @param argv Argument vector.
 * @param cmd_start_index Pointer to store the starting index for commands.
 * @param is_here_doc Boolean indicating if it's a here_doc scenario.
 */
static void	handle_input_redirection(int argc, char **argv, \
	int *cmd_start_index, int is_here_doc)
{
	int	in_fd;

	if (is_here_doc)
	{
		*cmd_start_index = 3;
		here_doc(argv[2], argc);
	}
	else
	{
		*cmd_start_index = 2;
		in_fd = open(argv[1], O_RDONLY);
		if (in_fd == -1)
		{
			perror(argv[1]);
			exit(EXIT_FAILURE);
		}
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			perror("pipex: dup2 stdin");
			close(in_fd);
			exit(EXIT_FAILURE);
		}
		close(in_fd);
	}
}

/**
 * @brief Opens the output file with appropriate flags.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param is_here_doc_case Boolean indicating if it's a here_doc scenario
 *                         (affects open flags O_APPEND vs O_TRUNC).
 * @return File descriptor of the opened output file. Exits on error.
 */
static int	open_outfile_fd(int argc, char **argv, int is_here_doc_case)
{
	int	out_fd;
	int	flags;

	if (is_here_doc_case)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	out_fd = open(argv[argc - 1], flags, 0644);
	if (out_fd == -1)
	{
		perror(argv[argc - 1]);
		exit(EXIT_FAILURE);
	}
	return (out_fd);
}

/**
 * @brief Sets up I/O redirection and launches intermediate commands.
 * @details Handles input from a file or a here-document using helper
 *          functions. Opens the output file. Creates pipes and executes
 *          intermediate commands using \`pipe_maker\`. This function exits
 *          if argument counts are invalid or if critical operations like
 *          opening files or duplicating file descriptors fail.
 * @param argc Argument count.
 * @param argv Argument vector, containing file names and commands.
 * @param envpath Array of environment path strings for command execution.
 * @return The file descriptor of the opened output file.
 */
int	performer(int argc, char **argv, char **envpath)
{
	int	cmd_idx;
	int	out_fd;
	int	is_here_doc;

	is_here_doc = (ft_strncmp(argv[1], "here_doc", 8) == 0);
	if (is_here_doc && argc < 6)
		error_here_doc();
	else if (!is_here_doc && argc < 5)
		error_argc();
	handle_input_redirection(argc, argv, &cmd_idx, is_here_doc);
	out_fd = open_outfile_fd(argc, argv, is_here_doc);
	while (cmd_idx < argc - 2)
	{
		pipe_maker(argv[cmd_idx], envpath);
		cmd_idx++;
	}
	return (out_fd);
}

// sleep(10000);
/**
 * @brief Main function for the pipex bonus program.
 * @details Validates arguments, retrieves environment paths, calls \`performer\`
 *          to set up I/O and intermediate commands, redirects output to the
 *          final file, executes the last command using \`parser\`, and waits for
 *          all child processes. It handles argument errors and ensures proper
 *          cleanup and exit statuses.
 * @param argc Argument count.
 * @param argv Argument vector (input file/delimiter, commands, output file).
 * @param envpath Environment path array for command execution.
 * @return Returns \`EXIT_SUCCESS\` on successful completion, or an error code
 *         (e.g., \`EXIT_FAILURE\`, 127) on failure.
 */
int	main(int argc, char **argv, char **envpath)
{
	int		i;
	int		status;
	int		out_fd;
	int		num_children;
	pid_t	last_pid;

	if (argc < 5)
		error_argc();
	if (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6)
		error_here_doc();
	out_fd = performer(argc, argv, envpath);
	if (dup2(out_fd, STDOUT_FILENO) == -1)
	{
		perror("pipex: dup2 main stdout");
		close(out_fd);
		exit(EXIT_FAILURE);
	}
	close(out_fd);
	last_pid = fork();
	if (last_pid < 0)
	{
		perror("pipex: fork last_pid");
		exit(EXIT_FAILURE);
	}
	if (last_pid == 0)
		parser(argv[argc - 2], envpath);
	num_children = argc - 3 - (ft_strncmp(argv[1], "here_doc", 8) == 0);
	i = 0;
	while (i < num_children)
	{
		wait(&status);
		i++;
	}
	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}
