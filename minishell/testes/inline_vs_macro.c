/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inline_vs_macro.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 21:00:29 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/08 21:17:59 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	my_stop(void);

inline void	my_stop(void)
{
	return ;
}

int	main(void)
{
	int	count = 0;
	while(count < 10)
	{
		write(1, "ola\n", 4);
		count++;
		write(1, &(char){count + 48}, 1);
		write(1, "\n\n", 2);
		my_stop();
	}
}