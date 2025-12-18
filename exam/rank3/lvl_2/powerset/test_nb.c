/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_nb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 07:25:41 by olacerda          #+#    #+#             */
/*   Updated: 2025/12/14 07:47:28 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	pn(long n)
{
	return ((void)((n < 0) && (write(1, "-", 1) && (n = -n))),
		(n > 9) && pn(n / 10), (write(1, &(char){n % 10 + 48}, 1)));
}

void	ft_put_nbr(int nbr)
{
	char result;
	long nb;

	nb = nbr;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb > 9)
		ft_put_nbr(nb / 10);
	result = nb % 10 + 48;
	write(1, &result, 1);
}

int	main(void)
{
	pn(-148001);
	write(1, "\n", 1);
	ft_put_nbr(-148001);
}