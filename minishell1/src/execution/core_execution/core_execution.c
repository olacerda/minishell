/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:55:23 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/22 22:03:11 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core_execution.h>

int	normal_execution(t_minishellinfo *all, t_comand *node, char **args, char **envp)
{
	char 	*absolute_path;
	int	pid;

	if (!all || !node || !args || !envp)
		return (0);
	absolute_path = get_absolute_path(all->prefx->path, node->comand, envp);
	execute_redirections(node, all->redir_fds, all->fd, all);
	pid = fork();
	if (pid < 0)
		return (put_error("Error\nFailed normal_execution\n"), 0);
	if (pid == 0)
	{
		execve(absolute_path, args, envp);
		exit (1);
	}
	else if (pid > 0)
		all->children_pids[all->node_number] = pid;
	return (1);
}

int	execute_redirections(t_comand *node, int redir_fds[2], int pipe_fds[2], t_minishellinfo *all)
{
	t_redirection	*redir;
	
	if (!node || !node->redir)
		return (0);
	redir = node->redir;
	while (redir != NULL)
	{
		if ((node->next != NULL) && (redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND))
		{
			redir_fds[1] = pipe_fds[1];
			dprintf(all->true_fds[1], "Trucando redir: %d pelo pipe\n", redir->type);
		}
		if (all->previous_fd_0 != -1 && (redir->type == REDIR_HEREDOC || redir->type == REDIR_INPUT))
		{
			dprintf(all->true_fds[1], "Truncando redir: %d por pipe\n", redir->type);
			redir_fds[0] = all->previous_fd_0;
		}
		if (redir->type == REDIR_OUTPUT)
			redir_out(redir, redir_fds, all);
		else if (redir->type == REDIR_INPUT)
			redir_in(redir, redir_fds);
		else if (redir->type == REDIR_APPEND)
			redir_append(redir, redir_fds);
		else if (redir->type == REDIR_HEREDOC)
			redir_heredoc(redir_fds, 0, all, redir);
		redir = redir->next;
	}
	return (1);
}



int	pipe_execution(t_minishellinfo *all, t_comand *node, char *argv[], char **envp)
{
	char 	*absolute_path;
	int		check_pipe;
	int		pid;

	if (!all || !node || !argv || !envp)
		return (0);
	while (node != NULL)
	{
		restore_original_fds(all, 0);
		absolute_path = get_absolute_path(all->prefx->path, node->comand, envp);
		if (node->next != NULL)
		{
			check_pipe = pipe(all->fd);
			if (check_pipe == -1)
				return (put_error("Error\nFailed pipe in pipe_execution\n"), 0);
		}
		pid = 0;
		execute_redirections(node, all->redir_fds, all->fd, all);
		if (all->node_number == 0)
			pid = execute_first_pipe(absolute_path, node->args, envp, all->fd);
		else if (node->next == NULL)
		{
			dprintf(all->true_fds[1], "executing last pipe\n");
			pid = execute_last_pipe(absolute_path, node->args, envp, all->previous_fd_0);
		}
		else if (all->node_number > 0)
			pid = execute_middle_pipe(absolute_path, node->args, envp, all->fd, all->previous_fd_0);
		all->children_pids[all->node_number++] = pid;
		all->previous_fd_0 = all->fd[0];
		// dup2(all->fd[0], all->previous_fd_0);
		node = node->next;
 	}
	return (1);
}

int	execute_comands(t_minishellinfo *all, t_comand *node, char *argv[], char **envp)
{
	if (!all || !node || !argv || !envp)
		return (0);
	if (node->next != NULL)
		pipe_execution(all, node, argv, envp);
	else
		normal_execution(all, node, node->args, envp);
	wait_all_children(all->children_pids, all->node_count);
	return (1);
}
