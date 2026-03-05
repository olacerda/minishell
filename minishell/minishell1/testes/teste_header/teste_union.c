/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_union.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:36:59 by olacerda          #+#    #+#             */
/*   Updated: 2026/02/27 08:45:06 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef union s_test
{
	int a;
	char b;
}			t_test;


int	main(void)
{
	// union {int a; char b;} a;
	t_test a;

	int	index = 99;
	char letter = 'z';

	a.b = letter;
	a.a = index;
	printf("%li\n", sizeof(a));
	printf("%li\n", sizeof(a.a));
	printf("%li\n", sizeof(a.b));
	printf("\n\n%d\n", a.a);
	printf("%c\n", a.b);
	printf("%d\n", a);
	// if (sizeof())
}