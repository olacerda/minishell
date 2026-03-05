/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_old.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:12:31 by otlacerd          #+#    #+#             */
/*   Updated: 2026/03/01 15:37:20 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core_execution.h>

int	execute_first_node(char *absolute_path, char **args, char **envp, int *fds)
{
	int	pid;

	if (!absolute_path || !args || !envp)
		return (0);
	pid = fork();
	if (pid < 0)
		return (put_error("Error\nFailed fork in execute_first_node\n"), 0);
	if (pid == 0)
	{
		if (fds[1] > 0)
		{
			close(fds[0]);
			dup2(fds[1], STDOUT_FILENO);
			close(fds[1]);
		}
		execve(absolute_path, args, envp);
		exit(1);
	}
	else if (pid > 0)
		close(fds[1]);
	return (pid);
}

int	execute_middle_node(char *absolute_path, char **args, char **envp, int *fds, int prev_fd_0)
{
	int	pid;

	if (!absolute_path || !args || !envp)
		return (0);
	pid = fork();
	if (pid < 0)
		return (put_error("Error\nFailed fork in execute_first_node\n"), 0);
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		dup2(prev_fd_0, STDIN_FILENO);
		close(prev_fd_0);
		execve(absolute_path, args, envp);
		exit(1);
	}
	else if (pid > 0)
	{
		close(fds[1]);
		close(prev_fd_0);
	}
	return (pid);
}

int	execute_last_node(char *absolute_path, char **args, char **envp, int prev_fd_0)
{
	int	pid;

	if (!absolute_path || !args || !envp)
		return (0);
	pid = fork();
	if (pid < 0)
		return (put_error("Error\nFailed fork in execute_first_node\n"), 0);
	if (pid == 0)
	{
		dup2(prev_fd_0, STDIN_FILENO);
		close(prev_fd_0);
		execve(absolute_path, args, envp);
		exit (1);
	}
	else if (pid > 0)
		close(prev_fd_0);
	return (pid);
}


