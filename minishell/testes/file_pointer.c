/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:59:22 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/15 22:47:14 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	main(void)
{
	long array[2] = {1, 2};
	long	*int1;
	long	*int2;
	int a;
	int b;
	int c;
	
	unsigned long stout = (unsigned long)stdout;
	unsigned long stin = (unsigned long)stdin;
	unsigned long sterr = (unsigned long)stderr;
	int1 = &array[0];
	int2 = &array[1];
	printf("a: %p\nb: %p\nc: %p\n\n", &a, &b, &c);
	printf("Array1: %p\nArray2: %p\n\n", array[0], array[1]);
	printf("int1: %p\nint2: %p\n\n", int1, int2);
	
	printf("out: %u  in: %u   err: %u\n\n", stout, stin, sterr);
	
	
	printf("out - in: %u\n\n", stout - stin);
	printf("err - out: %u\n\n", stout - sterr);

	
	printf("Size of FILE*: %u\n\n", stdout - stdin);
	printf("Size of FILE*: %u\n\n", stdin);
	printf("Size of FILE*: %u\n\n", stdout);
	printf("Size of FILE*: %u\n\n", stderr);
}	
