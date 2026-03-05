/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 04:34:05 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/02 16:36:17 by olacerda         ###   ########.fr       */
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
	execute_redirections(node, all->redir_fds, all->pipe_fd, all);
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

int	sync_redirection_and_pipe(t_comand *node, t_redirection *redir, int *redir_fd, int *pipe_fd)
{
	if (!node || !redir_fd || !pipe_fd || !redir)
		return (0);
	if ((node->next != NULL) && (redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND))
		redir_fd[1] = pipe_fd[1];
	if ((pipe_fd[0] != -1) && (redir->type == REDIR_HEREDOC || redir->type == REDIR_INPUT))
		redir_fd[0] = pipe_fd[0];
	return (1);
}

int	execute_redirections(t_comand *node, int redir_fds[2], int pipe_fds[2], t_minishellinfo *all)
{
	t_redirection	*redir;
	int	result;
	
	if (!node || !pipe_fds || !all || !redir_fds)
		return (0);
	// printf("execute_redirections\n\n");
	redir = node->redir;
	result = 0;
	while (redir != NULL)
	{
		// dprintf(2, "entrou execute_redirections\n");
		sync_redirection_and_pipe(node, redir, redir_fds, pipe_fds);
		if (redir->type == REDIR_OUTPUT)
			result = redir_out(redir, redir_fds, all);
		else if (redir->type == REDIR_INPUT)
			result = redir_in(redir, redir_fds);
		else if (redir->type == REDIR_APPEND)
			result = redir_append(redir, redir_fds);
		else if (redir->type == REDIR_HEREDOC)
			result = redir_heredoc(redir_fds, 3, all, redir);
		if (result != true)
			return (0);
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
		return (built_pwd);
	return (NULL);	
}

int	get_comand_origin(char *prefix, char *comand, char **envp, t_comand_origin *origin)
{
	if (!prefix || !comand || !origin)
		return (0);
	// printf("get_comand_origin\n\n");
	origin->absolute_path = NULL;
	origin->built_in = NULL;
	origin->built_in = get_built_in(comand);
	if (origin->built_in != NULL)
		return (1);
	origin->absolute_path = get_absolute_path(prefix, comand, envp);
	if (!origin->absolute_path)
		return (0);
	return (1);
}

int	execute_built_in(t_comand_origin *origin, t_comand *node, t_env *env)
{
	if (!origin || !node || !env)
		return (0);
	// printf("execute_built_in\n\n");
	origin->built_in(env->envp, node, env);
	return (1);
}

int	execute_external_comand(char *absolute_path, char **args, char **envp, int *fds)
{
	int	pid;

	if (!args || !envp || !fds || !absolute_path)
		return (0);
	pid = fork();
	if (pid < 0)
		return (put_error("Error\nFailed fork in execute_first_node\n"), 0);
	if (pid == 0)
	{
		if (!!execve(absolute_path, args, envp))
			perror(args[0]);
		exit(1);
	}
	else if (pid > 0)
	{
		if (fds[0] >= 0)
			close_fd(&fds[0]);
		if (fds[1] >= 0)
			close_fd(&fds[1]);
	}
	return (pid);
}

int	node_execution(t_minishellinfo *all, t_comand *node, char *argv[], char **envp)
{
	t_comand_origin origin;
	// int		check_pipe;
	int		temp;
	int		redir_status;

	if (!all || !node || !argv || !envp)
		return (0);
	// printf("node_execution\n");
	while (node != NULL)
	{
		restore_original_fds(all);
		if (node->next != NULL)
		{
			// check_pipe = pipe(all->pipe_fd);
			if (pipe(all->pipe_fd) == -1)
				return (put_error("Error\nFailed pipe in node_execution\n"), 0);
			temp = all->pipe_fd[0];
		}
		all->pipe_fd[0] = all->prev_fd_0;
		redir_status = execute_redirections(node, all->redir_fds, all->pipe_fd, all);
		// dprintf(2, "execute_pipes\n");
		execute_pipes(all->pipe_fd);
		// dprintf(2, "get_comand_origin\n");
		get_comand_origin(all->prefx->path, node->comand, envp, &origin);
		// dprintf(2, "comand execution\n\n\n");
		if ((redir_status == true) && (origin.built_in != NULL))
			execute_built_in(&origin, node, all->my_env);
		else if (redir_status == true)
			all->children_pids[all->node_number++] = execute_external_comand(origin.absolute_path, node->args, envp, all->pipe_fd);
		all->prev_fd_0 = temp;
		node = node->next;
 	}
	return (1);
}

int	execute_comands(t_minishellinfo *all, t_comand *node, char *argv[], char **envp)
{
	if (!all || !node || !argv || !envp)
		return (0);
	// printf("execute_comands\n");
	node_execution(all, node, argv, envp);
	wait_all_children(all->children_pids, all->node_count, &(all->exit_status));
	return (1);
}
