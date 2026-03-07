/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_increment_with_multiple_instance.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 04:52:05 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/07 04:54:25 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int	index = 0;
	char *string = "teste";
	int	size;
	while (string[size])
		size++;
	index = 0;
	while ((index++ < size) && string[index])
		write(1, &string[index], 1);
}