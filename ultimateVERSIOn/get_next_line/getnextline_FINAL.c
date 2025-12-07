/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline_FINAL.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:00:46 by olacerda          #+#    #+#             */
/*   Updated: 2025/12/07 04:58:26 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "getnextline_FINAL.h"

char	*get_next_line(int fd)
{
	static t_g	x;

	if ((fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > MAX))
		return (NULL);
	*(t_w *)&x = (t_w){0, 0, -1, 0, 0, x.end + ((x.buff[x.end]) == 10)};
	if (x.rbts <= 0 || x.start >= x.rbts)
		x = (t_g){NULL, NULL, -1, 0, 0, BUFFER_SIZE, BUFFER_SIZE, 1, {0}, 0};
	while ((x.line == NULL || x.buff[x.end] != 10) && x.rbts > 0)
	{
		(x.start >= x.rbts) && (x.rbts = read(fd, x.buff, BUFFER_SIZE));
		(x.start >= x.rbts) && (*(long *)&x.end = 0);
		while ((x.end < (x.rbts)) && (x.buff[x.end] != 10) && ++(x.end))
			++(x.allend);
		x.nln = malloc(x.allend + 1 + (x.buff[x.end] == 10));
		if (!x.nln)
			return (NULL);
		while (++x.index < (x.allend - x.end) && x.line && x.rbts > 0)
			x.nln[x.index] = (x.line)[x.index];
		while ((x.start <= x.end) && (x.start < x.rbts) && x.rbts > 0)
			x.nln[x.index++] = x.buff[x.start++];
		x.nln[x.index] = '\0';
		free(x.line);
		*(t_z *)&x = (t_z){(void *)((long)x.nln * (x.rbts > 0)), x.nln, -1, 0};
	}
	return (free((char *)((long)x.nln * (x.rbts <= 0))), x.line);
}
