/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 01:40:43 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/27 02:09:37 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <unistd.h>

// int	main(void)
// {
// 	int	column;

// 	column = 8;
// 	write(1, &(char){column + 48}, 1);
// 	write(1, "\n", 1);
// }

int	main(void)
{
	printf("min_int: %d     max int: %li\n\n", (1 << 31), (1L << 31) - 1);
}