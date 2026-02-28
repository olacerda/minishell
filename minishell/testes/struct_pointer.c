/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_struct_pointer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 05:16:32 by olacerda          #+#    #+#             */
/*   Updated: 2026/02/26 05:17:53 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef struct s_teste
{
	int	a;
	int	b;
}				t_teste;

int	main(void)
{
	t_teste bola;

	bola.a = 1;
	bola.b = 2;
	printf("%d\n%d\n\n", bola.a, bola.b);
}