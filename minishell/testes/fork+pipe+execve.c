/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork+pipe+execve_teste.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 21:35:07 by otlacerd          #+#    #+#             */
/*   Updated: 2025/11/17 20:04:19 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int *create_pipe()
{
	int	*fds;

	fds = malloc(2 * (sizeof(int)));
	if (!fds)
		return (NULL);
	pipe(fds);
	
}

char **create_args(char *string)
{
	char **result;
	int	line;
	int	index1;
	int	index2;
	int	count;

	if (!string)
		return (NULL);
	index1 = 0;
	count = 0;
	while (string[index1] != '\0')
	{
		if (string[index1] == ' ')
			while ((string[index1]) && (string[index1] == ' '))
				index1++;
		if ((string[index1] != '\0') && (string[index1] != ' '))
		{
			while ((string[index1] != ' ') && (string[index1] != '\0'))
				index1++;
			count++;
		}
	}
	result = malloc((count + 1) * (sizeof(char *)));
	if (!result)
		return (NULL);
	index1 = 0;
	line = 0;
	while (string[index1] != '\0')
	{
		count = 0;
		while ((string[index1] != '\0') && (string[index1] == ' '))
			index1++;
		if ((string[index1] != '\0') && (string[index1] != ' '))
		{
			index2 = index1;
			while ((string[index1] != '\0') && (string[index1++] != ' '))
				count++;
			result[line] = malloc((count + 1) * (sizeof(char)));
			if (!result[line])
				return (NULL);
			while ((string[index2] != '\0') && (string[index2] != ' '))
				result[line][count++] = string[index2++];
			result[line][count] = '\0';
			line++;
		}
	}
	result[line] = NULL;
	return (result);
}

void	clean_args(char **args)
{
	int	line;

	line = 0;
	if (!args)
		return ;
	while (args[line] != NULL)
	{
		free(args[line]);
		line++;
	}
	free(args[line]);
}

int	get_pipe_position(char **args)
{
	int	line;

	line = 0;
	while (args[line] != NULL)
	{
		if (args[line][0] == '|')
			return (line);
		line++;
	}
	return (-1);
}

int	main(int argc, char *argv[], char **envp)
{
	char *line;

	line = readline()
}