/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:47:45 by otlacerd          #+#    #+#             */
/*   Updated: 2025/11/11 02:48:06 by otlacerd         ###   ########.fr       */
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