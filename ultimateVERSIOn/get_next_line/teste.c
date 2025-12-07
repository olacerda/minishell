/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 03:14:52 by otlacerd          #+#    #+#             */
/*   Updated: 2025/12/07 04:02:28 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "getnextline_FINAL.h"

int	main(void)
{
	struct t_teste {int a, b;} teste = {4, 6};
	int array[] = {4, 6};

	printf("array[0]: %d   array[1]: %d\n\n", array[0], array[1]);
	*(long *)&array[0] = (999000) + (587L << 32);
	printf("array[0]: %d   array[1]: %d\n\n\n\n\n", array[0], array[1]);
	// printf("a: %d   b: %d\n\n", teste.a, teste.b);
	// *(long *)&teste.a = 1 << 31;
	// printf("a: %d   b: %d\n\n", teste.a, teste.b);
	printf("t_g: %d\nt_w: %d\nt_z: %d", sizeof(t_g), sizeof(t_w), sizeof(t_z));
}