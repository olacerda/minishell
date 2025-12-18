/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 05:11:03 by olacerda          #+#    #+#             */
/*   Updated: 2025/12/08 05:40:05 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	count_words(char *string, char sep)
{
	int	result;
	int	index;

	if (!string || !sep)
		return (0);
	index = 0;
	result = 0;
	while(string[index])
	{
		if ((string[index]) && (string[index] != sep))
		{
			while ((string[index]) && (string[index] != sep))
				index++;
			result++;
		}
		else
			index++;
	}
	return (result);
}

char	*create_word(char *original, char sep, int *index)
{
	char *string;
	int	temp;
	int	size;

	if (!original || !sep)
		return (NULL);
	temp = (*index);
	size = 0;
	while(original[temp] && (original[temp] != sep))
	{
		size++;
		temp++;
	}
	string = malloc((size + 1) * sizeof(char));
	if (!string)
		return (NULL);
	temp = 0;
	while(original[(*index)] && (original[(*index)] != sep))
	{
		string[temp] = original[(*index)];
		temp++;
		(*index)++;
	}
	string[temp] = '\0';
	return (string);
}

char	**split(char *original, char sep)
{
	char **result;
	int	index;
	int	line;

	if (!original || !sep)
		return (NULL);
	result = malloc((count_words(original, sep) + 1) * (sizeof(char *)));
	if (!result)
		return (NULL);
	index = 0;
	line = 0;
	while (original[index])
	{
		if ((original[index]) && (original[index] != sep))
		{
			result[line] = create_word(original, sep, &index);
			if (!result[line])
				return (clean_split(result), NULL);
			line++;
		}
		while (original[index] && (original[index] == sep))
			index++;
	}
	result[line] = NULL;
	return (result);
}

void	clean_split(char **string)
{
	int	line;

	if (!string)
		return ;
	line = 0;
	while (string[line] != NULL)
	{
		free(string[line]);
		line++;
	}
	free(string[line]);
	free(string);
}

int	main(void)
{
	char **result;
	int	line;

	line = 0;
	result = split("oi isso e um teste", ' ');
	if (!result)
		return (1);
	while(result[line] != NULL)
	{
		printf("%s\n", result[line]);
		line++;
	}
	return (0);
}