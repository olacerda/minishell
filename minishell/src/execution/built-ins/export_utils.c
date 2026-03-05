/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:36:08 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/04 15:36:41 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built-ins.h>

char *get_value(char *prefix, char **env)
{
	char 	*result;
	int 	size;

	if (!prefix || !env)
		return (NULL);
	size = 0;
	while (prefix[size])
		size++;
	result = env_find_pointer(prefix, env);
	if (!result)
		return (NULL);
	result += size;
	if (*result == '=')
		result++;
	return (result);
}

char *value_dup(char *string, int beginning)
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

char *key_dup(char *string, int	delimiter)
{
	char *result;
	int	index;
	
	if (!string || (delimiter < 0) || string[0] == ' ')
		return (NULL);
	index = 0;
	result = malloc((delimiter + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (string[index] && (index < delimiter))
	{
		result[index] = string[index];
		index++;
	}
	result[index] = '\0';
	return (result);
}