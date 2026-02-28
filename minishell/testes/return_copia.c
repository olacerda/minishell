/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_return_copia.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 02:51:58 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/16 02:57:10 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

char **return_pointer(void)
{
	char *string = "Oi, tudo bem\n\n";

	printf("Endereco conteudo: %p\n", string);
	printf("Endereco do pointer: %p\n", &string);
	return (&string);
}


int	main(void)
{
	char **string;

	string = return_pointer();
	if (!string)
		return (1);
	printf("Endereco conteudo: %p\n", **string);
	printf("Endereco do pointer: %p\n", *string);	
}