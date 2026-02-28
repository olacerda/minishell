/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 04:34:05 by olacerda          #+#    #+#             */
/*   Updated: 2026/02/28 12:52:15 by olacerda         ###   ########.fr       */
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

int	sync_redirection_and_pipe(t_comand *node, int previous_fd_0, int *redir_fd, int *pipe_fd)
{
	if (!node || !node->redir || !redir_fd || !pipe_fd)
		return (0);
	if ((node->next != NULL) && (node->redir->type == REDIR_OUTPUT || node->redir->type == REDIR_APPEND))
		redir_fd[1] = pipe_fd[1];
	if ((previous_fd_0 != -1) && (node->redir->type == REDIR_HEREDOC || node->redir->type == REDIR_INPUT))
		redir_fd[0] = previous_fd_0;
	return (1);
}

int	execute_redirections(t_comand *node, int redir_fds[2], int pipe_fds[2], t_minishellinfo *all)
{
	t_redirection	*redir;
	
	if (!node || !node->redir)
		return (0);
	redir = node->redir;
	sync_redirection_and_pipe(node, all->previous_fd_0, redir_fds, pipe_fds);
	while (redir != NULL)
	{
		if (redir->type == REDIR_OUTPUT)
			redir_out(redir, redir_fds, all);
		else if (redir->type == REDIR_INPUT)
			redir_in(redir, redir_fds);
		else if (redir->type == REDIR_APPEND)
			redir_append(redir, redir_fds);
		else if (redir->type == REDIR_HEREDOC)
			redir_heredoc(redir_fds, 3, all, redir);
		redir = redir->next;
	}
	return (1);
}

func_pointer *get_built_in(char *comand)
{
	if (string_compare(comand, "exit") == 0)
		return (built_exit);
	else if (string_compare(comand, "env") == 0)
		return (built_env);
	else if (string_compare(comand, "export") == 0)
		return (built_export);
	else if (string_compare(comand, "unset") == 0)
		return (built_unset);
	else if (string_compare(comand, "echo") == 0)
		return (built_echo);
	else if (string_compare(comand, "cd") == 0)
		return (built_cd);
	else if (string_compare(comand, "pwd") == 0)
		return (write(1, "Built-In not done yet\n", 22), NULL);
	return (NULL);	
}

int	get_comand_origin(char *prefix, char *comand, char **envp, t_comand_origin *origin)
{
	if (!prefix || !comand || !origin)
		return (0);
	origin->absolute_path = NULL;
	origin->built_in = NULL;
	origin->built_in = get_built_in(comand);
	if (origin->built_in != NULL)
		return (1);
	origin->absolute_path = get_absolute_path(prefix, comand, envp);
	return (1);
}

int	execute_built_in(t_comand_origin *origin, t_comand *node, t_env *env)
{
	if (!origin || !node || !env)
		return (0);
	origin->built_in(env->envp, node, env);
	return (1);
}

int	execute_external_comand(char *absolute_path, char **args, char **envp, int *fds)
{
	int	pid;

	if (!absolute_path || !args || !envp)
		return (0);
	pid = fork();
	if (pid < 0)
		return (put_error("Error\nFailed fork in execute_first_node\n"), 0);
	if (pid == 0)
	{
		execve(absolute_path, args, envp);
		exit(1);
	}
	else if (pid > 0)
	{
		close(fds[1]);
		close(fds[0]);
	}
	return (pid);
}

int	node_execution(t_minishellinfo *all, t_comand *node, char *argv[], char **envp)
{
	t_comand_origin origin;
	int		check_pipe;
	int		pid;
	int		temp;

	if (!all || !node || !argv || !envp)
		return (0);
	while (node != NULL)
	{
		restore_original_fds(all, 0);
		if (node->next != NULL)
		{
			check_pipe = pipe(all->fd);
			if (check_pipe == -1)
				return (put_error("Error\nFailed pipe in node_execution\n"), 0);
			temp = all->fd[0];
		}
		all->fd[0] = all->previous_fd_0;
		pid = 0;
		execute_redirections(node, all->redir_fds, all->fd, all);
		execute_pipes(all->fd);
		get_comand_origin(all->prefx->path, node->comand, envp, &origin);
		if (origin.built_in != NULL)
			execute_built_in(&origin, node, all->my_env);
		else if (origin.absolute_path != NULL)
			pid = execute_external_comand(origin.absolute_path, node->args, envp, all->fd);
		all->children_pids[all->node_number++] = pid;
		all->previous_fd_0 = temp;
		node = node->next;
 	}
	return (1);
}

int	execute_comands(t_minishellinfo *all, t_comand *node, char *argv[], char **envp)
{
	if (!all || !node || !argv || !envp)
		return (0);
	node_execution(all, node, argv, envp);
	wait_all_children(all->children_pids, all->node_count);
	return (1);
}
