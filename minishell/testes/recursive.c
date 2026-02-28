/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 08:37:06 by olacerda          #+#    #+#             */
/*   Updated: 2026/02/28 10:10:03 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

char *string_duplicate(char *string, int *size)
{
	char *result;
	int	index;

	if (!string)
		return (NULL);
	if (string[*size])
	{
		(*size)++;
		return (result = string_duplicate(string, size));
	}
	else
	{
		result = malloc((*size + 1) * sizeof(char));
		if (!result)
			return (NULL);
		index = -1;
		while (string[++index])
			result[index] = string[index];
		result[index] = '\0';
		return (result);
		
	}
}

int	main(void)
{
	char *result;
	int	size = 0;

	result = string_duplicate("eai funcionou?", &size);
	printf("%s\n", result);
}