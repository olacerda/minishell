/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_teste.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 01:14:41 by otlacerd          #+#    #+#             */
/*   Updated: 2025/11/15 04:38:49 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			count = 0;
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
	free(args);
}

int	main(void)
{
	char *teste = "tralarero tralala un poco aqui un poco la       ";
	char **args;
	int	line;

	line = 0;
	args = create_args(teste);
	if (!args)
	{
		write(2, "Error\nUnable to create args\n", 28);
		return (0);
	}
	while (args[line] != NULL)
	{
		printf("%s\n", args[line]);
		line++;
	}
	clean_args(args);
	return (0);
	// write(1, "teste", 5);
	// write(1, "test\n", 5);
}