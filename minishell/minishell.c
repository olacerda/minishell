/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 23:13:10 by otlacerd          #+#    #+#             */
/*   Updated: 2025/11/11 05:26:01 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
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


int	is_comand(char *comand)
{
	char *reference;
	int	index;

	if (!comand)
		return (0);
	reference = "ls";
	index = 0;
	while (comand[index] == reference[index])
	{
		index++;
	}
	if (comand[index] == '\0')
		return (1);
	return (0);
}

int	execute_comand(t_minishellinfo *all, char *comand, char *argv[], char **envp)
{
	int	alter_pid;
	char *absolute_path;

	alter_pid = fork();
	if (alter_pid < 0)
	{
		put_error("Error\nFailed to get a new pid in execute_coman\n");
		return (0);
	}
	absolute_path = get_absolute_path(all->prefx->path, comand, envp);
	if (!absolute_path)
	{
		put_error("Error\nFailed to get_absolute_path in execute_comand\n");
		return (0);
	}
	if (alter_pid == 0)
	{
		if (!execve(absolute_path, argv, envp))
			return (0);
	}
	else if (alter_pid > 0)
		waitpid(alter_pid, NULL, 0);
	return (1);
}

// ----------------- MAIN PARA DEBUGS -------------
int	main(int argc, char *argv[], char **envp)
{
	int	pid;
	char *line;
	char *absolute_path;
	char *enviroment_variable;
	t_minishellinfo *all;

	enviroment_variable = NULL;
	absolute_path = NULL;
	all = init_structures();
	if (!all)
		return (1);
	
	// int	line = -1;
	// int	number = 0;
	// while (envp[++line])
	// {
	// 	printf("Pointer number: %d\n", number++);
	// 	printf("%s\n\n", envp[line]);
	// }
	
	enviroment_variable = find_environment_variable("PATH=", envp);
	all->enviroment_variable_path = enviroment_variable;
	printf("enviroment variable PATH:\n%s\n\n\n", enviroment_variable);
	if (!get_all_prefixs(all->prefx))
	{
		end_structures(all);
		exit (1);
	}
	absolute_path = get_absolute_path(all->prefx->path, "ls", envp);
	if (!absolute_path)
	{
		end_structures(all);
		exit (1);
	}
	printf("Absolut path of 'LS': %s\n\n", absolute_path);


	line = NULL;
	pid = getpid();
	all->father_pid = pid;
	while (1)
	{
		write(1, "minishell> ", 11);
		line = readline(NULL);
		if (!line)
			break ;
		if (is_comand(line))
		{
			// write(1, "\n", 1);
			execute_comand(all, line, argv, envp);
		}
		free(line);
	}
	
	// if (access(absolute_path, X_OK) == 0)
	// 	printf("Path válido e executável: %s\n", absolute_path);
	// else
	// 	perror("Caminho inválido");
	(void)argv;
	(void)argc;
	(void)envp;
	return (0);
}

// int	main(int argc, char *argv[], char **envp)
// {
	// int	pid;
	// char *line;

	// line = NULL;
	// pid = getpid();
	
	// while (1)
	// {
	// 	write(1, "minishell> ", 11);
	// 	line = readline(NULL);
	// 	if (!line)
	// 		break ;
	// 	if (is_comand(line))
	// 		execute_comand(line);
	// 	free(line);
	// }
// 	(void)argv;
// 	(void)argc;
// 	(void)envp;
// }
