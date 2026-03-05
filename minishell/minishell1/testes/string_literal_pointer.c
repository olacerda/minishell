/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_literal_pointer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 13:20:22 by olacerda          #+#    #+#             */
/*   Updated: 2026/02/28 13:26:46 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	char *pointer;
	int	index;
	printf("%p\n\n\n", "teste");
	while ("teste"[index])
	{
		printf("%p\n", &"teste"[index]);
		index++;
	}
}