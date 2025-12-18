/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 08:18:00 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/29 08:23:52 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

int	ascii_to_int(char *string)
{
	long	result;
	int		minus;
	int		index;

	index = 0;
	minus = 0;
	result = 0;
	if (!string)
		return (0);
	while (string[index] && ((string[index] >= 9 && string[index] <= 13) || string[index] == 32))
		index++;
	if (string[index] == '+' || string[index] == '-')
	{
		if (string[index] == '-')
			minus = 1;
		index++;
	}
	while (string[index] && (string[index] >= '0' && string[index] <= '9'))
	{
		result = (result * 10) + (string[index] - 48);
		index++;
	}
	if (minus > 0)
		result = -result;
	if ((result > (1 << 31)) || (result < ((1L << 31) - 1)))
		return (0);
	return ((int){result});
}