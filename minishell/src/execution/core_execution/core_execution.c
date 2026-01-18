/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:55:23 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/18 05:14:49 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core_execution.h>


// while (tiver_pipes) {
//     if (primeiro_pipe) {
//         // no fork do primeiro comando
//         dup2(pipe[1], STDOUT_FILENO);
//         close(pipe[0]); // não tem pipe anterior
//     } 
//     else if (pipe_no_meio) {
//         // no fork dos comandos do meio
//         dup2(pipe_anterior[0], STDIN_FILENO);
//         dup2(pipe_atual[1], STDOUT_FILENO);
//     } 
//     else if (ultimo_pipe) {
//         // no fork do último comando
//         dup2(pipe_anterior[0], STDIN_FILENO);
//         close(pipe[1]); // vai escrever no stdout original
//     }
// }


// int	execute_in_pipe(t_minishellinfo *all, char **args, int pipe_position)
// {
// 	int	fd_backup[2];
// 	int	fds[2];
// 	int	pipe_status;
// 	int	fork_status;

// 	fds[0] = 0;
// 	fds[1] = 0;
// 	fd_backup[0] = 0;
// 	fd_backup[1] = 0;

// 	fd_backup[0] = dup(0);
// 	fd_backup[1] = dup(1);
// 	pipe_status = pipe(fds);
// 	if (pipe_status == -1)
// 		return (0);
// 	dup2(fds[1], 1);
// 	fork_status = fork();
// 	if (fork_status == 0)
// 	{
// 		execute_comand(all, args[pipe_position - 1], all->argv, all->envp);
// 		close(fds[1]);
// 		exit(1);
// 	}
// 	if (fork_status > 0)
// 	{
// 		wait(NULL);
// 		close(fds[1]);
// 		dup2(fds[0], 0);
// 		dup2(fd_backup[1], 1);
// 		fork_status = fork();
// 		if (fork_status == 0)
// 		{
// 			execute_comand(all, args[pipe_position + 1], all->argv, all->envp);
// 			close(fds[0]);
// 			exit(1);
// 		}
// 		if (fork_status > 0)
// 		{
// 			wait(NULL);
// 			dup2(fd_backup[0], 0);	
// 		}
// 	}
// 	return (1);
// }

//-----------------------DELETAR ISSO----------------------
// int	get_pipe_position(char **args)
// {
// 	int	line;

// 	line = 0;
// 	while (args[line] != NULL)
// 	{
// 		if (args[line][0] == '|')
// 			return (line);
// 		line++;
// 	}
// 	return (-1);
// }
//-------------------------------------------------------

int	execute_first_pipe(char *absolute_path, char *argv[], char **envp, int *fds)
{
	int	pid;

	if (!absolute_path || !argv || !envp)
		return (0);
	pid = fork();
	if (pid < 0)
		return (put_error("Error\nFailed fork in execute_first_pipe\n"), 0);
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		execve(absolute_path, argv, envp);
		exit(1);
	}
	else if (pid > 0)
	{
		close(fds[1]);
		waitpid(pid, NULL, 0);
	}
	return (1);
}

int	execute_middle_pipe(char *absolute_path, char *argv[], char **envp, int *fds, int prev_fd_0)
{
	int	pid;

	if (!absolute_path || !argv || !envp)
		return (0);
	pid = fork();
	if (pid < 0)
		return (put_error("Error\nFailed fork in execute_first_pipe\n"), 0);
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		dup2(prev_fd_0, STDIN_FILENO);
		close(prev_fd_0);
		execve(absolute_path, argv, envp);
		exit(1);
	}
	else if (pid > 0)
	{
		close(fds[1]);
		close(prev_fd_0);
		waitpid(pid, NULL, 0);
	}
	return (1);
}

int	execute_last_pipe(char *absolute_path, char *argv[], char **envp, int prev_fd_0)
{
	int	pid;

	if (!absolute_path || !argv || !envp)
		return (0);
	pid = fork();
	if (pid < 0)
		return (put_error("Error\nFailed fork in execute_first_pipe\n"), 0);
	if (pid == 0)
	{
		dup2(prev_fd_0, STDIN_FILENO);
		close(prev_fd_0);
		execve(absolute_path, argv, envp);
		exit (1);
	}
	else if (pid > 0)
	{
		close(prev_fd_0);
		waitpid(pid, NULL, 0);
	}
	return (1);
}

int	pipe_execution(t_minishellinfo *all, t_comand *node, char *argv[], char **envp)
{
	char 	*absolute_path;
	int		check_pipe;

	if (!all || !node || !argv || !envp)
		return (0);
	while (node != NULL)
	{
		absolute_path = get_absolute_path(all->prefx->path, node->comand, envp);
		if (node->next != NULL)
		{
			check_pipe = pipe(all->fd);
			if (!check_pipe)
				return (put_error("Error\nFailed pipe in execute_first_pipe\n"), 0);
			if (all->node_number == 1)
				execute_first_pipe(absolute_path, argv, envp, all->fd);
			else
				execute_middle_pipe(absolute_path, argv, envp, all->fd, all->prev_fd_0);
			all->prev_fd_0 = all->fd[0];
		}
		else if (node != NULL)
			execute_last_pipe(absolute_path, argv, envp, all->prev_fd_0);
		node = node->next;
		all->node_number++;		
 	}
	return (1);
}

int	normal_execution(t_minishellinfo *all, t_comand *node, char *argv[], char **envp)
{
	char 	*absolute_path;
	int	pid;

	if (!all || !node || !argv || !envp)
		return (0);
	absolute_path = get_absolute_path(all->prefx->path, node->comand, envp);
	pid = fork();
	if (pid < 0)
		return (put_error("Error\nFailed normal_execution\n"), 0);
	if (pid == 0)
	{
		execve(absolute_path, argv, envp);
		exit (1);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	return (1);
}

int	execute_comand(t_minishellinfo *all, t_comand *node, char *argv[], char **envp, int *fds)
{
	if (!all || !node || !argv || !envp || !fds)
		return (0);
	if (node->next != NULL)
		pipe_execution(all, node, argv, envp);
	else
		normal_execution(all, node, argv, envp);
	return (1);
}

// int	is_comand(char *comand)
// {
// 	char **references;
// 	int	line;
// 	int	index;
	
// 	if (!comand)
// 	return (0);
// 	references = (char *[3]){"ls", "wc", NULL};
// 	line = 0;
// 	index = 0;
// 	while (references[line] != NULL)
// 	{
// 		index = 0;
// 		while (comand[index] == references[line][index])
// 			index++;
// 		if (comand[index] == '\0')
// 			return (1);
// 		line++;
// 	}
// 	return (0);
// }