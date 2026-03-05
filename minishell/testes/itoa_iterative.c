/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_iterative.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 11:56:44 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/03 13:40:05 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

char	*int_to_ascii(int nbr)
{
	char *result;
	int		size;
	long	temp;
	int		minus;

	size = 0;
	temp = 0;
	minus = 1;
	if ((nbr < 0) && ++(size))
		minus = -1;
	while ((nbr != 0) && ++(size))
	{
		temp = ((temp * 10) + ((nbr % 10) * (minus * ((nbr % 10) != 0))));
		nbr /= 10;
	}
	result = malloc((size + 1) * sizeof(char));
	if(!result)
		return (NULL);
	nbr = -1 + (minus == -1);
	while ((++nbr < (size + 1)) && ((temp != 0) || (temp == 0 && nbr == 0)))
	{
		result[nbr] = ((temp % 10) + 48);
		temp /= 10;
	}
	return (result[nbr] = '\0', (void)((minus == -1) && (result[0] = '-')), result);
}

void	put_number(int	nbr)
{
	long	result;

	result = 0;
	if (nbr < 0)
		write(1, "-", 1);
	while (nbr != 0)
	{
		result = (result * 10) + ((nbr % 10) + (((nbr < 0) * 2) * -(nbr % 10)));
		nbr /= 10;
	}
	while (result != 0)
	{
		write(1, &(char){(result % 10) + 48}, 1);
		result /= 10;
	}
	write(1, "\n", 1);
}

int	main(void)
{
	char *result;

	put_number(-188);
	
	printf("%s\n", int_to_ascii(0));
	printf("%s\n", int_to_ascii(1));
	printf("%s\n", int_to_ascii(2));
	printf("%s\n", int_to_ascii(198));
	printf("%s\n", int_to_ascii(-198));
	printf("%s\n", int_to_ascii(1 << 31));
	printf("%s\n", int_to_ascii(((1L << 31) - 1)));
}