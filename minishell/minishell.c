/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 23:13:10 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/18 05:40:09 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <core_execution.h>
#include <data.h>
#include <utils.h>

// #include <execution.h>

// int	clear_buffer(char *string, int size)
// {
// 	int	index;

// 	index = 0;
// 	if (!string || !size)
// 		return (0);
// 	while (index < size)
// 	{
// 		string[index] = 0;
// 		index++;
// 	}
// 	return (1);
// }

// int	string_lenght(char *string)
// {
// 	int	size;

// 	size = 0;
// 	if (!string)
// 		return (0);
// 	while (string[size])
// 		size++;
// 	return (size);
// }

// int	get_all_prefixs(t_prefix *prefix)
// {
// 	if (!prefix)
// 	{
// 		put_error("Error\nNULL pointer in argument of 'get_all_prefixs'");
// 		return (0);
// 	}
// 	prefix->path = "PATH=";
// 	prefix->home = "HOME=";
// 	prefix->oldpwd = "PWD=";
// 	prefix->oldpwd = "OLDPWD=";
// 	prefix->user = "USER=";
// 	return (1);
// }

// int	compare_prefix(char *string1, char *string2)
// {
// 	int	index;

// 	index = 0;
// 	if (!string1 || !string2)
// 		return (0);
// 	while ((string1[index]) && (string2[index]) && string1[index] == string2[index])
// 	{
// 		index++;
// 	}
// 	if (string1[index] == '\0')
// 	{
// 		return (1);
// 	}
// 	return (0);
// }

// char	*find_environment_variable(char *prefix, char **envp)
// {
// 	int	result;
// 	int	line;

// 	line = 0;
// 	if (!prefix || !envp)
// 	{
// 		return (NULL);
// 	}
// 	while (envp[line] != NULL)
// 	{
// 		result = compare_prefix(prefix, envp[line]);
// 		if (result > 0)
// 		{
// 			return (envp[line]);
// 		}
// 		line++;
// 	}
// 	return (NULL);
// }

// int	get_next_path(char *path, char *environment_variable, int env_idx, int path_buffer_size)
// {
// 	int	index;

// 	index = 0;
// 	if (!path || !environment_variable || !env_idx)
// 		return (0);
// 	if ((environment_variable[env_idx]) && (environment_variable[env_idx] == ':'))
// 		env_idx++;
// 	while ((environment_variable[env_idx]) && (index < (path_buffer_size - 1)) && (environment_variable[env_idx] != ':'))
// 	{
// 		path[index] = environment_variable[env_idx];
// 		index++;
// 		env_idx++;
// 	}
// 	path[index] = '\0';
// 	return (index);
// }

// int	is_accessible(char *path, char *comand)
// {
// 	int	result;

// 	if (!path || !comand)
// 		return (0);
// 	result = 0;
// 	result = access((const char *)path, X_OK);
// 	return (result);
// }

// char *find_absolute_path(char *environment_variable, char *comand, int prefix_size)
// {
// 	static char	path[PATH_MAX];
// 	int			env_size;
// 	int			env_idx;
// 	int			path_size;
	
// 	if (!clear_buffer(path, PATH_MAX) || !environment_variable || !comand || !prefix_size)
// 		return (NULL);
// 	path[PATH_MAX - 1] = '\0';
// 	env_size = string_lenght(environment_variable);
// 	env_idx = prefix_size;
// 	path_size = 0;
// 	if (!env_size || env_size <= prefix_size)
// 		return (NULL);
// 	while ((env_idx < env_size) && environment_variable[env_idx])
// 	{
// 		path_size = get_next_path(path, environment_variable, env_idx, PATH_MAX);
// 		if (!path_size)
// 			return (NULL);
// 		if (!append_comand_to_path(path, comand, path_size, PATH_MAX))
// 			return (NULL);
// 		if (is_accessible(path, comand) == 0)
// 			return (path);	
// 		env_idx += path_size;
// 	}
// 	return (NULL);
// }

// int	append_comand_to_path(char *path, char *comand, int path_idx, int path_buffer_size)
// {
// 	int	index;

// 	if (!path || !comand || !path_idx || !path_buffer_size)
// 		return (0);
// 	index = 0;
// 	if (path_idx < (path_buffer_size - 1))
// 	{
// 		path[path_idx] = '/';
// 		path_idx++;
// 	}
// 	while ((path_idx < (path_buffer_size - 1)) && (comand[index] != '\0'))
// 	{
// 		path[path_idx] = comand[index];
// 		path_idx++;
// 		index++;
// 	}
// 	path[path_idx] = '\0';
// 	return (1);
// }

// char *get_absolute_path(char *prefix, char *comand, char **envp)
// {
// 	char *environment_variable;
// 	char *absolute_path;
// 	int	prefix_size;

// 	if (!prefix || !comand || !envp)
// 		return (put_error("Error\nNull pointer in argument of 'get_absolute_path'\n"), NULL);
// 	environment_variable = NULL;
// 	absolute_path = NULL;
// 	prefix_size = string_lenght(prefix);
// 	if (!prefix_size)
// 		return (put_error("Error\nPrefix size == 0 in get_absolute_path\n"), NULL);
// 	environment_variable = find_environment_variable(prefix, envp);
// 	if (!environment_variable)
// 		return (put_error("Error\nFailed to get enviroment path in get_absolute_path\n"), NULL);
// 	absolute_path = find_absolute_path(environment_variable, comand, prefix_size);
// 	if (!absolute_path)
// 		return (put_error("Error\nFailed to get absolute_path in find_absolute_path\n"), NULL);
// 	return (absolute_path);
// }

// void	put_error(char *problem)
// {
// 	int	index;

// 	index = 0;
// 	if (!problem)
// 		return ;
// 	while (problem[index])
// 		index++;
// 	write(2, problem, index);
// }

// t_minishellinfo *init_structures(void)
// {
// 	t_minishellinfo *all;
// 	t_prefix *prefx;

// 	all = malloc(sizeof(t_minishellinfo));
// 	if (!all)
// 	{
// 		put_error("Error\nFailed to allocate struct 'ALL'\n");
// 		end_structures(all);
// 		return (NULL);
// 	}
// 	*all = (t_minishellinfo){0};
// 	prefx = malloc(sizeof(t_prefix));
// 	if (!prefx)
// 	{
// 		put_error("Error\nFaile to allocate struct 'prefx'\n");
// 		end_structures(all);
// 		return (NULL);
// 	}
// 	*prefx = (t_prefix){0};
// 	all->prefx = prefx;
// 	return (all);
// }

// void	end_structures(t_minishellinfo *all)
// {
// 	if (!all)
// 		return ;
// 	if (all->prefx)
// 		free(all->prefx);
// 	if (all)
// 		free(all);
// }


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

// char **create_args(char *string)
// {
// 	char **result;
// 	int	line;
// 	int	index1;
// 	int	index2;
// 	int	count;

// 	if (!string)
// 		return (NULL);
// 	index1 = 0;
// 	count = 0;
// 	while (string[index1] != '\0')
// 	{
// 		if (string[index1] == ' ')
// 			while ((string[index1]) && (string[index1] == ' '))
// 				index1++;
// 		if ((string[index1] != '\0') && (string[index1] != ' '))
// 		{
// 			while ((string[index1] != ' ') && (string[index1] != '\0'))
// 				index1++;
// 			count++;
// 		}
// 	}
// 	result = malloc((count + 1) * (sizeof(char *)));
// 	if (!result)
// 		return (NULL);
// 	index1 = 0;
// 	line = 0;
// 	while (string[index1] != '\0')
// 	{
// 		count = 0;
// 		while ((string[index1] != '\0') && (string[index1] == ' '))
// 			index1++;
// 		if ((string[index1] != '\0') && (string[index1] != ' '))
// 		{
// 			index2 = index1;
// 			while ((string[index1] != '\0') && (string[index1++] != ' '))
// 				count++;
// 			result[line] = malloc((count + 1) * (sizeof(char)));
// 			if (!result[line])
// 				return (NULL);
// 			count = 0;
// 			while ((string[index2] != '\0') && (string[index2] != ' '))
// 				result[line][count++] = string[index2++];
// 			result[line][count] = '\0';
// 			line++;
// 		}
// 	}
// 	result[line] = NULL;
// 	return (result);
// }

// void	clean_args(char **args)
// {
// 	int	line;

// 	line = 0;
// 	if (!args)
// 		return ;
// 	while (args[line] != NULL)
// 	{
// 		free(args[line]);
// 		line++;
// 	}
// 	free(args[line]);
// }

// int	count_args(char **args)
// {
// 	int	line;

// 	line = 0;
// 	while (args[line] != NULL)
// 		line++;
// 	return (line);
// }

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

// int	is_builtin_or_external(t_minishellinfo *all, char *comand, char *absolute_path)
// {
// 	int	result;
	

// 	result = 0;
// 	if (absolute_path)
// 		return (2);
// 	result = is_comand(comand);
// 	if (result)
// 		return (result);
// }

// int	execute_in_pipe(t_list *node)
// {
// 	if (node->next != NULL)
// 		return (1);
// 	return (0);
// }

// int	execute_comand(t_minishellinfo *all, char *comand, char *argv[], char **envp)
// {
// 	int	alter_pid;
// 	char *absolute_path;

// 	alter_pid = fork();
// 	if (alter_pid < 0)
// 	{
// 		put_error("Error\nFailed to get a new pid in execute_coman\n");
// 		return (0);
// 	}
// 	absolute_path = get_absolute_path(all->prefx->path, comand, envp);
// 	// if (!absolute_path)
// 	// {
// 	// 	put_error("Error\nFailed to get_absolute_path in execute_comand\n");
// 	// 	return (0);
// 	// }
// 	if (alter_pid == 0)
// 	{
// 		execve(absolute_path, argv, envp);
// 		exit(130);
// 	}
// 	else if (alter_pid > 0)
// 		waitpid(alter_pid, NULL, 0);
// 	return (1);
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

// void	fill_structures(t_minishellinfo *all, int argc, char **argv, char **envp)
// {
// 	if (!all)
// 		return ;
// 	all->argv = argv;
// 	all->envp = envp;
// 	all->argc = argc;
// 	if (!get_all_prefixs(all->prefx))
// 	{
// 		end_structures(all);
// 		exit (1);
// 	}
// }


int	main(int argc, char *argv[], char **envp)
{
	t_minishellinfo *all;
	t_comand		*node;
	char 			**args;
	char 			*line;
	int				pid;
	
	all = init_structures();
	if (!all)
		return (1);
	fill_structures(all, argc, argv, envp);
	line = NULL;
	pid = getpid();
	all->father_pid = pid;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		args = create_args(line);
		
//----------------------------------------------------		
		int line2 = 0;
		printf("split: \n");
		while (args[line2] != NULL)
			printf("%s\n", args[line2++]);
		write(1, "\n\n\n", 3);
//----------------------------------------------------		
		// exit(1);
		
		all->head = create_comand_list(args);

//----------------------------------------------------		
		printf("linked-list: \n");
		while (all->head != NULL)
		{
			printf("%s\n", all->head->comand);
			line2 = 0;
			while (all->head->args[line2])
				printf("%s\n", all->head->args[line2++]);
			all->head = all->head->next;
		}
		exit(1);
//----------------------------------------------------		

		node = all->head;
		all->node_number = 1;
		execute_comand(all, node, argv, envp, all->fd);
		free(line);
	}
	return (0);
}
