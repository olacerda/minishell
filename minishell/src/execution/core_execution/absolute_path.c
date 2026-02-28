/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:53:45 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/28 11:33:58 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core_execution.h>

int	get_next_path(char *path, char *environment_variable, int env_idx, int path_buffer_size)
{
	int	index;

	index = 0;
	if (!path || !environment_variable || !env_idx)
		return (0);
	if ((environment_variable[env_idx]) && (environment_variable[env_idx] == ':'))
		env_idx++;
	while ((environment_variable[env_idx]) && (index < (path_buffer_size - 1)) && (environment_variable[env_idx] != ':'))
	{
		path[index] = environment_variable[env_idx];
		index++;
		env_idx++;
	}
	path[index] = '\0';
	return (index);
}

int	append_comand_to_path(char *path, char *comand, int path_idx, int path_buffer_size)
{
	int	index;

	if (!path || !comand || !path_idx || !path_buffer_size)
		return (0);
	index = 0;
	if (path_idx < (path_buffer_size - 1))
	{
		path[path_idx] = '/';
		path_idx++;
	}
	while ((path_idx < (path_buffer_size - 1)) && (comand[index] != '\0'))
	{
		path[path_idx] = comand[index];
		path_idx++;
		index++;
	}
	path[path_idx] = '\0';
	return (1);
}

int	is_accessible(char *path, char *comand)
{
	int	result;

	if (!path || !comand)
		return (0);
	result = 0;
	result = access((const char *)path, X_OK);
	return (result);
}

char *find_absolute_path(char *environment_variable, char *comand, int prefix_size)
{
	static char	path[PATH_MAX];
	int			env_size;
	int			env_idx;
	int			path_size;
	
	if (!clear_string(path, PATH_MAX) || !environment_variable || !comand || !prefix_size)
		return (NULL);
	path[PATH_MAX - 1] = '\0';
	env_size = string_lenght(environment_variable);
	env_idx = prefix_size;
	path_size = 0;
	if (!env_size || env_size <= prefix_size)
		return (NULL);
	while ((env_idx < env_size) && environment_variable[env_idx])
	{
		path_size = get_next_path(path, environment_variable, env_idx, PATH_MAX);
		if (!path_size)
			return (NULL);
		if (append_comand_to_path(path, comand, path_size, PATH_MAX) == false)
			return (NULL);
		if (is_accessible(path, comand) == false)
			return (path);
		env_idx += path_size;
	}
	return (NULL);
}

char	*find_environment_variable(char *prefix, char **envp)
{
	int	result;
	int	line;

	line = 0;
	if (!prefix || !envp)
	{
		return (NULL);
	}
	while (envp[line] != NULL)
	{
		result = compare_prefix(prefix, envp[line]);
		if (result > 0)
		{
			return (envp[line]);
		}
		line++;
	}
	return (NULL);
}

char *get_absolute_path(char *prefix, char *comand, char **envp)
{
	char *environment_variable;
	char *absolute_path;
	int	prefix_size;

	if (!prefix || !comand || !envp)
		return (put_error("Error\nNull pointer in argument of 'get_absolute_path'\n"), NULL);
	environment_variable = NULL;
	absolute_path = NULL;
	prefix_size = string_lenght(prefix);
	if (!prefix_size)
		return (put_error("Error\nPrefix size == 0 in get_absolute_path\n"), NULL);
	environment_variable = find_environment_variable(prefix, envp);
	if (!environment_variable)
		return (put_error("Error\nFailed to get enviroment path in get_absolute_path\n"), NULL);
	absolute_path = find_absolute_path(environment_variable, comand, prefix_size);
	// if (!absolute_path)
	// 	return (put_error("Error\nFailed to get absolute_path in find_absolute_path\n"), NULL);
	return (absolute_path);
}