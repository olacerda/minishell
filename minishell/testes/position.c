/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_position.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 21:16:33 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/23 20:58:29 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	char *str = "teste";


	printf("%c\n", *(str++));
	printf("%c\n", *(str++));
	printf("%c\n", *(str++));
	printf("%c\n", *(str++));
	printf("%c\n", *(str++));
}