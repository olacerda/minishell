/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal_divided_by_ten.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 12:22:10 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/03 12:31:37 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	int a = 5;
	int b = -5;

	printf("a\nbefore: %d\n", a);
	a = a / 10;
	printf("after: %d\n\n", a);

	printf("b\nbefore: %d\n", b);
	b = b / 10;
	printf("before: %d\n\n", b);
	
	printf("result: %d\n", (5 * 5));
	printf("result: %d\n", (-5 * 5));
}