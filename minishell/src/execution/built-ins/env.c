/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:13:30 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/28 12:11:09 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

int	env_free(char **buffer, int size)
{
	int	line;

	if (!buffer)
		return (0);
	line = 0;
	while ((size && (line < size)) || buffer[line])
	{
		free(buffer[line]);
		line++;
	}
	free(buffer);
	return (1);
}

char	**create_env(char **envp, int *capacity)
{
	char **result;
	int	line_count;
	int	line;

	if (!envp)
		return (NULL);
	line_count = 0;
	while (envp[line_count])
		line_count++;
	*capacity = line_count + ENV_INCREMENT;
	result = malloc((*capacity + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	line = 0;
	while (envp[line])
	{
		result[line] = string_duplicate(envp[line]);
		if (!result[line])
			return (env_free(result, line), NULL);
		line++;
	}
	result[line] = NULL;
	return (result);
}

int	env_add(t_env *env_st, int line, char *key, char *string)
{
	int	size;

	if (!env_st || !env_st->envp || !key)
		return (0);
	if (line >= env_st->capacity)
	{
		env_st->envp = re_allocker(env_st->envp, env_st->size + 1, env_st->size + ENV_INCREMENT + 1, sizeof(char *));
		if (!env_st->envp)
			return (0);
		env_st->capacity = env_st->size + ENV_INCREMENT;
	}
	size = (string_lenght(key) + string_lenght(string));
	free(env_st->envp[line]);
	env_st->envp[line] = malloc((size + 1) * sizeof(char));
	if (!env_st->envp[line])
		return (0);
	string_copy(env_st->envp[line], key);
	string_cat(env_st->envp[line], size, string);
	if (line >= env_st->size)
	{
		env_st->envp[++line] = NULL;
		env_st->size = line;
	}
	return (1);	
}

int	env_remove(t_env *env_st, char *key)
{
	int	line;

	if (!env_st || !key)
		return (0);
	line = 0;
	while (env_st->envp[line] != NULL)
	{
		if (compare_prefix(key, env_st->envp[line]) == true)
		{
			free(env_st->envp[line]);
			while (line < env_st->size)
			{
				env_st->envp[line] = env_st->envp[line + 1];
				line++;
			}
			env_st->size--;
			break ;
		}
		line++;
	}
	if ((env_st->capacity - env_st->size) >= (2 * ENV_INCREMENT))
	{
		env_st->envp = re_allocker(env_st->envp, env_st->size + 1, (env_st->capacity - ENV_INCREMENT) + 1, sizeof(char *));
		env_st->capacity = env_st->capacity - ENV_INCREMENT;
	}
	return (0);
}

int	env_show(char **envp, int is_export)
{
	int	line;
	int	size;

	if (!envp)
		return (0);
	line = -1;
	while (envp[++line])
	{
		if (is_export == true)
			write(1, "export ", 7);
		size = 0;
		while (envp[line][size] && (envp[line][size] != '='))
			size++;
		write(1, envp[line], size);
		if (envp[line][size] == '=')
		{
			write(STDOUT_FILENO, &envp[line][size++], 1);
			(void)((is_export == true) && (write(STDOUT_FILENO, "\"", 1)));
			while(envp[line][size])
				write(1, &envp[line][size++], 1);
			(void)((is_export == true) && (write(STDOUT_FILENO, "\"", 1)));
		}
		write(1, "\n", 1);
	}
	return (1);
}

int	env_find(char *key, char **envp)
{
	int	line;

	if (!key || !envp)
		return (-1);
	line = 0;
	while (envp[line] != NULL)
	{
		if (compare_prefix(key, envp[line]) == true)
			return (line);
		line++;
	}
	return (-1);
}

int	env_update(t_env *env_st, char *key, char *new_value1, char *new_value2)
{
	char *result;
	int	line;
	int	total_size;

	if (!key || !env_st->envp)
		return (0);
	result = NULL;
	line = env_find(key, env_st->envp);
	if (line == -1)
		line = env_st->size;
	total_size = 0;
	total_size += string_lenght(new_value1);
	total_size += string_lenght(new_value2);
	if (total_size > 0)
	{
		result = malloc((total_size + 1) * sizeof(char));
		if (!result)
			return (0);
	}
	clear_string(result, (total_size + 1));
	string_cat(result, (total_size + 1), new_value1);
	string_cat(result, (total_size + 1), new_value2);
	env_add(env_st, line, key, result);
	free(result);
	return (1);
}

int	assign_env_struct(t_minishellinfo *all)
{
	int	capacity;
	
	if (!all || !all->my_env)
		return (0);
	capacity = 0;
	all->my_env->envp = create_env(all->envp, &capacity);
	if (!all->my_env->envp)
		return (0);
	all->my_env->capacity = capacity;
	all->my_env->size = capacity - ENV_INCREMENT;
	return (1);
}

int	built_env(char **envp, t_comand *node, t_env *env)
{
	if (!envp)
		return (0);
	(void)node;
	(void)env;
	env_show(envp, 0);
	return (1);	
}

// int	env()
// {
	
// }