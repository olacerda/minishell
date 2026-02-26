/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 06:11:51 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/16 06:12:53 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

typedef struct s_test
{
	int a;
	int b;
}			t_test;

int	main(void)
{
	t_test test;

	test.a = 5;
	test.b = 3;
	printf("a: %d\nb: %d\n", test.a, test.b);
}