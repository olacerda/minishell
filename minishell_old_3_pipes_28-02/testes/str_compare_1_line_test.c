/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_compare_1_line_test.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 01:34:34 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/24 01:55:16 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	char *string = "Isso = e + um teste += outro testeeeeee";
	// char *string = "Isso = e + um teste += outro += testeeeeee";
	int	index = 0;

	while (string[index])
	{
		if ((string[index] == '+') || (string[index] == '='))
		{
			// printf("achou\n");
			if (*(short *)&string[index] == ((short *)"+=")[0])
			{
				while (string[index])
					printf("%c", string[index++]);
				printf("\n");
				return (0);
			}
		}
		index++;
	}
	printf("terminou\n");
}