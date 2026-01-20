/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:55:23 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/20 00:58:44 by otlacerd         ###   ########.fr       */
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
	execute_redirections(node, all->redir_fds);
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

int	execute_redirections(t_comand *node, int *fds)
{
	t_redirection	*redir;
	
	if (!node || !node->redir)
		return (0);
	redir = node->redir;
	while (redir != NULL)
	{
		if (redir->type == REDIR_OUTPUT)
			redir_out(redir, fds);
		else if (redir->type == REDIR_INPUT)
			redir_in(redir, fds);
		else if (redir->type == REDIR_APPEND)
			redir_append(redir, fds);
		else if (redir->type == REDIR_HEREDOC)
			redir_heredoc(fds);
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
		absolute_path = get_absolute_path(all->prefx->path, node->comand, envp);
		if (node->next != NULL)
		{
			check_pipe = pipe(all->fd);
			if (check_pipe == -1)
				return (put_error("Error\nFailed pipe in pipe_execution\n"), 0);
			if (node->redir != NULL && (node->redir->type == REDIR_OUTPUT || node->redir->type == REDIR_APPEND))
				copy_fds(all->redir_fds, all->fd);
			execute_redirections(node, all->redir_fds);
			if (all->node_number == 0)
				pid = execute_first_pipe(absolute_path, node->args, envp, all->fd);
			else
				pid = execute_middle_pipe(absolute_path, node->args, envp, all->fd, all->previous_fd_0);
			all->previous_fd_0 = all->fd[0];
		}
		else if (node != NULL)
			pid = execute_last_pipe(absolute_path, node->args, envp, all->previous_fd_0);
		all->children_pids[all->node_number] = pid;
		node = node->next;
		all->node_number++;		
 	}
	return (1);
}

int	execute_comands(t_minishellinfo *all, t_comand *node, char *argv[], char **envp, int *fds)
{
	if (!all || !node || !argv || !envp || !fds)
		return (0);
	if (node->next != NULL)
		pipe_execution(all, node, argv, envp);
	else
		normal_execution(all, node, node->args, envp);	
	wait_all_children(all->children_pids, all->node_count);
	return (1);
}
