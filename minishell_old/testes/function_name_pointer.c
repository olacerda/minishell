/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_name_pointer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:05:59 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/03 18:16:35 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	aleatory_function(char **pointer_to_string)
{
	return (*pointer_to_string = __func__, printf("%s\n", __func__), 1);
}

int	main(void)
{
	char *pointer;

	pointer = NULL;
	aleatory_function(&pointer);
	printf("Main function: %s\n", pointer);
}