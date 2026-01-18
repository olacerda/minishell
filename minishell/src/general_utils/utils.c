/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:47:45 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/16 21:49:58 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

int	clear_buffer(char *string, int size)
{
	int	index;

	index = 0;
	if (!string || !size)
		return (0);
	while (index < size)
	{
		string[index] = 0;
		index++;
	}
	return (1);
}

int	string_lenght(char *string)
{
	int	size;

	size = 0;
	if (!string)
		return (0);
	while (string[size])
		size++;
	return (size);
}

char *string_copy(char *string)
{
	char *result;
	int	index;
	int	size;

	if (!string)
		return (NULL);
	size = string_lenght(string);
	result = malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	index = 0;
	while (string[index])
	{
		result[index] = string[index];
		index++;
	}
	result[index] = '\0';
	return (result);
}