/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:37:25 by otlacerd          #+#    #+#             */
/*   Updated: 2025/08/27 10:57:47 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "getnextline_bonus_FINAL.h"

char	*get_next_line(int fd)
{
	static t_g	x[FD_SETSIZE];

	*(t_w *)&x[fd].s = (t_w){x[fd].e += x[fd].b[x[fd].e] == 10, 0, 0, 0};
	if ((fd < 0 || BF <= 0 || BF > MAX))
		return (NULL);
	if (x[fd].rb <= 0 || x[fd].s >= x[fd].rb)
		x[fd] = (t_g){BF, BF, 0, 0, 0, -1,{0}, 1};
	while ((x[fd].ln == NULL || x[fd].b[x[fd].e] != 10) && x[fd].rb > 0)
	{
		(x[fd].s >= x[fd].rb) && (x[fd].rb = read(fd, x[fd].b, BUFFER_SIZE));
		(x[fd].s >= x[fd].rb) && (*(long *)&(x[fd].s) = 0);
		while ((x[fd].b[x[fd].e] != 10) && (x[fd].e < x[fd].rb) && ++(x[fd].e))
			++(x[fd].t);
		x[fd].n = malloc(x[fd].t + 1 + (x[fd].b[x[fd].e] == 10) * sizeof(char));
		if (!x[fd].n)
			return (NULL);
		while (++x[fd].i < (x[fd].t - x[fd].e) && x[fd].ln && x[fd].rb > 0)
			x[fd].n[x[fd].i] = (x[fd].ln)[x[fd].i];
		while ((x[fd].s <= x[fd].e) && (x[fd].s < x[fd].rb) && x[fd].rb > 0)
			x[fd].n[x[fd].i++] = x[fd].b[x[fd].s++];
		x[fd].n[x[fd].i] = '\0';
		free(x[fd].ln);
		*(t_z *)&x[fd].ln = (t_z){(void *)((long)x[fd].n * (x[fd].rb > 0)), -1};
	}
	return (free((void *)((long)x[fd].n * (x[fd].rb <= 0))), x[fd].ln);
}
