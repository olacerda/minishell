/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_pointer_test.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 05:49:21 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/16 05:56:59 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef int (funcao)(int a, int b);
typedef ssize_t (writers)(int __fd, const void *__buf, size_t __n);

int	add(int a, int b)
{
	return (a - b);
}

int	(*funcao_returner(void))(int a, int b)
{
	return (add);
}

int	main(void)
{
	funcao *pointer;
	writers *oi;

	oi = write;
	write(1, "oi\n", 3);
	oi(1, "teste123\n\n", 10);
	pointer = funcao_returner();
	printf("%d\n", pointer(5, 4));
}