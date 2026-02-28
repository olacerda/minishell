/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 22:15:51 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/23 22:42:34 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	rev_int_tab(int *array, int size)
{
	size--;
	while (size > 0)
	{
		*array = *array + array[size];
		array[size] = *array - array[size];
		*array = *array - array[size];
		array++;
		size -= 2;
	}
}

int	main(void)
{
	int	array[] = {1, 2, 3, 4, 5};
	int	*array2;
	char *string = "Isso e um teste";
	array2 = array;

	int	count = 0;
	while (count < 5)
		printf("%d\n", array[count++]);

	rev_int_tab(array, 5);
	printf("\n\nafter\n\n");	

	count = 0;
	while (count < 5)
		printf("%d\n", array[count++]);

	// int count = 1;
	// printf("%d\n", (array2++)[count]);
	// printf("%d\n", (array2)[count - 1]);
}