/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_with_max_min_protection.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 09:26:32 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/03 09:38:06 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>

int	ascii_to_int(char *string)
{
	long	result;
	int	minus;
	int	index;

	if (!string)
		return (-1);
	index = 0;
	while ((string[index]) && ((string[index] >= 9 && (string[index] <= 13)) || (string[index] == 32)))
		index++;
	minus = 0;
	if ((string[index] == '+') || (string[index] == '-'))
	{
		if (string[index] == '-')
			minus = 1;
		index++;
	}
	result = 0;
	while ((string[index]) && ((string[index] >= '0') && (string[index] <= '9')))
		result = ((result * 10) + (string[index++] - 48));
	if (minus == true)
		result = -result;
	if ((result < (1 << 31)) || (result > ((1L << 31) - 1)))
		return (0);
	return (result);
}

int	main(void)
{
	printf("%d\n", ascii_to_int("0"));
	printf("%d\n", ascii_to_int("100"));
	printf("%d\n", ascii_to_int("-100"));
	printf("%d\n", ascii_to_int("-2147483648"));
	printf("%d\n", ascii_to_int("2147483647"));
	printf("%d\n", ascii_to_int("-2147483649"));
	printf("%d\n", ascii_to_int("2147483648"));
}