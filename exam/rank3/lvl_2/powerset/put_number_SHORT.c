/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_number_SHORT.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 02:07:01 by otlacerd          #+#    #+#             */
/*   Updated: 2025/12/07 02:49:01 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	putnbr(long nb)
{
	return (((nb < 0) && (write(1, "-", 1)) && (nb = -nb)), ((nb > 9)
			&& (putnbr(nb / 10))), write(1, &((char){(nb % 10) + 48}), 1), 1);
}

int	main(void)
{
	putnbr(-398099);
	write(1, "\n", 1);
}
