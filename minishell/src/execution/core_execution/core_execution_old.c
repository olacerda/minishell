/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_execution_old.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:55:23 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/26 05:14:56 by olacerda         ###   ########.fr       */
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
			redir_fds[1] = pipe_fds[1];
		if (all->previous_fd_0 != -1 && (redir->type == REDIR_HEREDOC || redir->type == REDIR_INPUT))
			redir_fds[0] = all->previous_fd_0;
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

int	built_exit(char **envp, char **args)
{
	(void)envp;
	(void)args;
	if (!envp)
		return (0);
	return (exit(1), 1);
}

func_pointer *get_built_in(char *comand)
{
	// printf("checking_built_in\n");
	if (string_compare(comand, "exit") == 0)
		return (built_exit);
	else if (string_compare(comand, "echo") == 0)
		return (built_echo);
	// else if (string_compare(comand, "cd") == 0)
	// 	return (built_cd);
	else if (string_compare(comand, "env") == 0)
		return (built_env);
	return (NULL);	
}

t_comand_origin *get_comand_origin(char *prefix, char *comand, char **envp)
{
	static t_comand_origin origin;

	origin.absolute_path = NULL;
	origin.built_in = NULL;
	if (!prefix || !comand)
		return (NULL);
	// printf("comand: %s\n", comand);
	origin.built_in = get_built_in(comand);
	if (origin.built_in != NULL)
		return (&origin);
	origin.absolute_path = get_absolute_path(prefix, comand, envp);
	return (&origin);
}

int	node_execution(t_minishellinfo *all, t_comand *node, char *argv[], char **envp)
{
	t_comand_origin *comand_origin;
	int		check_pipe;
	int		pid;

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
		}
		pid = 0;
		execute_redirections(node, all->redir_fds, all->fd, all);
		comand_origin = get_comand_origin(all->prefx->path, node->comand, envp);
		// if (comand_origin->built_in != NULL)
		// 	comand_origin->built_in(envp, node->args);
		// 	else
		if (all->node_number == 0)
			pid = execute_first_node(comand_origin->absolute_path, node->args, envp, all->fd);
		else if (node->next == NULL)
			pid = execute_last_node(comand_origin->absolute_path, node->args, envp, all->previous_fd_0);
		else if (all->node_number > 0)
			pid = execute_middle_node(comand_origin->absolute_path, node->args, envp, all->fd, all->previous_fd_0);
		all->children_pids[all->node_number++] = pid;
		// {
		// }
		all->previous_fd_0 = all->fd[0];
		node = node->next;
 	}
	return (1);
}

int	execute_comands(t_minishellinfo *all, t_comand *node, char *argv[], char **envp)
{
	if (!all || !node || !argv || !envp)
		return (0);
	node_execution(all, node, argv, envp);
	// if (node->next != NULL)
	// 	node_execution(all, node, argv, envp);
	// else
	// 	normal_execution(all, node, node->args, envp);
	wait_all_children(all->children_pids, all->node_count);
	return (1);
}
