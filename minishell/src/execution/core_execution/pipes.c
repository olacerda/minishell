/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 03:35:41 by olacerda          #+#    #+#             */
/*   Updated: 2026/02/26 05:46:02 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core_execution.h>

int	execute_pipes(int *fds)
{
	if (!fds)
		return (0);
	if ((fds[0] >= 0) && (isatty(fds[0]) == false))
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
	if ((fds[1] >= 0) && (isatty(fds[1]) == false))
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
	}
	return (1);
}

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

int	execute_middle_node(char *absolute_path, char **args, char **envp, int *fds, int previous_fd_0)
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
		dup2(previous_fd_0, STDIN_FILENO);
		close(previous_fd_0);
		execve(absolute_path, args, envp);
		exit(1);
	}
	else if (pid > 0)
	{
		close(fds[1]);
		close(previous_fd_0);
	}
	return (pid);
}

int	execute_last_node(char *absolute_path, char **args, char **envp, int previous_fd_0)
{
	int	pid;

	if (!absolute_path || !args || !envp)
		return (0);
	pid = fork();
	if (pid < 0)
		return (put_error("Error\nFailed fork in execute_first_node\n"), 0);
	if (pid == 0)
	{
		dup2(previous_fd_0, STDIN_FILENO);
		close(previous_fd_0);
		execve(absolute_path, args, envp);
		exit (1);
	}
	else if (pid > 0)
		close(previous_fd_0);
	return (pid);
}


