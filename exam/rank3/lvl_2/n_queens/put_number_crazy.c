/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_number_crazy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 07:51:35 by olacerda          #+#    #+#             */
/*   Updated: 2025/12/18 08:05:50 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	put_number(int number)
{
	int	result;
	int	save;
	int	backup;

	save = number;
	backup = 0;
	while (save % 10 == 0)
	{
		backup++;
		save /= 10;		
	}
	(void)((number < 0) && (write(1, "-", 1)) && (number = -number));
	while (number > 0)
	{
		result = (result * 10) + (number % 10);
		number /= 10;
	}
	while (result > 0)
	{
		write(1, &(char){result % 10 + 48}, 1);
		result /= 10;
	}
	while (backup-- > 0)
		write(1, "0", 1);
}

int	main(void)
{
	put_number(-548000);
}