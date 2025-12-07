/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline_FINAL.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:00:46 by olacerda          #+#    #+#             */
/*   Updated: 2025/12/07 03:26:05 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "getnextline_FINAL.h"

char	*get_next_line(int fd)
{
	static t_cast	x;

	if ((fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > MAX))
		return (NULL);
	x.w = (t_w){0, -1, x.g.start, x.g.end + ((x.g.buff[x.g.end]) == 10), 0, 0};
	if (x.g.rbts <= 0 || x.g.start >= x.g.rbts)
		x.g = (t_g){NULL, -1, BUFFER_SIZE, BUFFER_SIZE, NULL, 0, 1, {0}};
	while ((x.g.line == NULL || x.g.buff[x.g.end] != 10) && x.g.rbts > 0)
	{
		(x.g.start >= x.g.rbts) && (x.g.rbts = read(fd, x.g.buff, BUFFER_SIZE));
		(x.g.start >= x.g.rbts) && (*(long *)&x.g.start = 0);
		while ((x.g.end < x.g.rbts) && (x.g.buff[x.g.end] != 10) && ++(x.g.end))
			++(x.g.allend);
		x.g.nline = malloc(x.g.allend + 1 + (x.g.buff[x.g.end] == 10));
		if (!x.g.nline)
			return (NULL);
		while (++x.g.index < (x.g.allend - x.g.end) && x.g.line && x.g.rbts > 0)
			x.g.nline[x.g.index] = (x.g.line)[x.g.index];
		while ((x.g.start <= x.g.end) && (x.g.start < x.g.rbts) && x.g.rbts > 0)
			x.g.nline[x.g.index++] = x.g.buff[x.g.start++];
		x.g.nline[x.g.index] = '\0';
		free(x.g.line);
		x.z = (t_z){(void *)((long)x.g.nline * (x.g.rbts > 0)), -1};
	}
	return (free((char *)((long)x.g.nline * (x.g.rbts <= 0))), x.g.line);
}

int	main(void)
{
	int fd;
	char *line1 = "";

	fd = open("./teste1.txt", O_RDONLY);
	while (line1 != NULL)
	{
		line1 = get_next_line(0);
		if(line1 != NULL)
			printf("You wrote ->%s", line1);
		free(line1);
	}
	printf("open %i\n", fd);
	line1 = get_next_line(fd);
	printf("GET1:  %s\n", line1);
	free(line1);
	char *line2 = get_next_line(fd);
	printf("GET2:  %s\n", line2);
	free(line2);
	char *line3 = get_next_line(fd);
	printf("GET3:  %s\n", line3);
	free(line3);
	char *line4 = get_next_line(fd);
	printf("GET4:  %s\n", line4);
	free(line4);
	char *line5 = get_next_line(fd);
	printf("GET5:  %s\n\n", line5);
	free(line5);
	printf("After close:\n\n");

	close(fd);
	fd = open("./teste1.txt", O_RDONLY);
	printf("open %i\n", fd);
	line1 = get_next_line(fd);
	printf("GET1:  %s\n", line1);

	line2 = get_next_line(fd);
	printf("GET2:  %s\n", line2);

	line3 = get_next_line(fd);
	printf("GET3:  %s\n", line3);

	line4 = get_next_line(fd);
	printf("GET4:  %s\n", line4);

	line5 = get_next_line(fd);
	printf("GET5:  %s\n\n", line5);
	free(line1);
	free(line2);
	free(line3);
	free(line4);
	free(line5);
}

