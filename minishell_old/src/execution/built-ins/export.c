/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 00:59:03 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/28 08:34:30 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

char *get_value(char *string, int beginning)
{
	char 	*result;
	int		size;
	int		index;

	if (!string || beginning < 0 || !string[beginning])
		return NULL;
	index = beginning;
	size = 0;
	while (string[index])
	{
		index++;
		size++;
	}
	result = malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	index = 0;
	while (string[beginning])
	{
		result[index] = string[beginning];
		index++;
		beginning++;
	}
	result[index] = '\0';
	return (result);
}

char *get_key(char *string, int	delimiter)
{
	char *result;
	int	index;
	
	if (!string || (delimiter < 0) || string[0] == ' ')
		return (NULL);
	index = 0;
	result = malloc((delimiter + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (string[index] && index < delimiter)
	{
		result[index] = string[index];
		index++;
	}
	result[index] = '\0';
	return (result);
}

int	identifie_case(t_env *env, char *string)
{
	char *key;
	char *new_value;
	char *old_value;
	int	index;

	if (!string || !env || !env->envp)
		return (-1);
	index = 0;
	key = NULL;
	new_value = NULL;
	old_value = NULL;
	while (string[index] && (string[index] != '=') && (*(short *)&(string[index]) != *(short *)&("+="[0])))
		index++;
	key = get_key(string, index);
	if (key != NULL)
	{
		if (string[index] != '=')
			old_value = get_value(find_environment_variable(key, env->envp), index);
		if ((string[index] == '=') || ((*(short *)&(string[index++]) == *(short *)&("+="[0])) && ++(index)))
			new_value = get_value(string, index);
	}
	env_update(env, key, old_value, new_value);
	free(key);
	free(old_value);
	free(new_value);
	return (1);
}

char **duplicate_envp(t_env *env_st)
{
	char **result;
	int	line;

	if (!env_st)
		return (NULL);
	result = malloc((env_st->size + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	line = 0;
	while (env_st->envp[line])
	{
		result[line] = env_st->envp[line];
		line++;
	}
	result[line] = NULL;
	return (result);
}

int	sort_env(char **env)
{
	int	line;
	int	smallest;
	int	finder;

	if (!env)
		return (0);
	line = 0;
	smallest = 0;
	finder = 0;
	while (env[line])
	{
		smallest = line;
		finder = line + 1;
		while (env[finder])
		{
			if (string_compare(env[smallest], env[finder]) > 0)
				smallest = finder;
			finder++;
		}
		if (line != smallest)
			swap_strings(&(env[line]), &(env[smallest]));
		line++;
	}
	return (1);
}

int	built_export(char **envp, t_comand *node, t_env *env)
{
	char **temp;
	int	line;

	if (!envp || !node || !node->args)
		return (0);
	line = 1;
	if (!node->args[line])
	{
		temp = duplicate_envp(env);
		sort_env(temp);
		env_show(temp, 1);
		free(temp);
		return (1);
	}
	else
	{
		while (node->args[line])
		{
			identifie_case(env, node->args[line]);
			line++;
		}
	}
	return (1);
}
