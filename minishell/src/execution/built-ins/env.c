/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:13:30 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/26 03:22:39 by olacerda         ###   ########.fr       */
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

	if (!env_st || !env_st->envp || !key || !string)
		return (0);
	if (line >= env_st->capacity)
	{
		env_st->envp = re_allocker(env_st->envp, env_st->size + 1, env_st->size + ENV_INCREMENT + 1, sizeof(char *));
		if (!env_st->envp)
			return (0);
		env_st->capacity = env_st->size + ENV_INCREMENT;
	}
	size = (string_lenght(key) + string_lenght(string));
	env_st->envp[line] = malloc((size + 1) * sizeof(char));
	if (!env_st->envp[line])
		return (0);
	string_copy(env_st->envp[line], key);
	string_cat(env_st->envp[line], size, string);
	env_st->envp[++line] = NULL;
	env_st->size = line;
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

int	env_show(char **envp)
{
	int	line;

	if (!envp)
		return (0);
	line = 0;
	while (envp[line])
	{
		put_string(envp[line]);
		write(1, "\n", 1);
		line++;
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

int	env_update(char **envp, char *key, char *new_value)
{
	int	line;
	int	value_size;
	int	key_size;

	if (!key || !envp || !new_value)
		return (0);
	line = env_find(key, envp);
	if (line == -1)
		return (0);
	value_size = 0;
	while (new_value[value_size] != '\0')
		value_size++;
	key_size = 0;
	while (key[key_size] != '\0')
		key_size++;
	free(envp[line]);
	envp[line] = malloc((key_size + value_size + 1) * sizeof(char));
	if (!envp[line])
		return (0);
	clear_string(envp[line], (key_size + value_size + 1));
	string_cat(envp[line], (key_size + value_size + 1), key);
	string_cat(envp[line], (key_size + value_size + 1), new_value);
	return (1);
	return (0);
}

int	assign_env_struct(t_minishellinfo *all)
{
	int	capacity;
	
	if (!all || !all->my_env)
		return (0);
	capacity = 0;
	// all->my_env->envp = create_env((char *[]){"Oi", "Meu chapa", NULL}, &capacity);
	all->my_env->envp = create_env(all->envp, &capacity);
	if (!all->my_env->envp)
		return (0);
	all->my_env->capacity = capacity;
	all->my_env->size = capacity - ENV_INCREMENT;
	return (1);
}

int	built_env(char **envp, char **args)
{
	(void)args;
	if (!envp)
		return (0);
	// printf("\n\n\nentrou na funcao built env\n\n\n");
	env_show(envp);
	// printf("\n\n\nentrou na funcao built env\n\n\n");
	return (1);	
}