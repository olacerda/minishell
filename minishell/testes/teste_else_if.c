/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_else_if.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 09:49:51 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/01 09:51:12 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	int	a = 5;

	if (a == 9)
		printf("nove\n");
	else
		printf("qualquer valor");
	else if (a == 3)
		printf("tres\n");
}