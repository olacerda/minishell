/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline_FINAL.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:00:46 by olacerda          #+#    #+#             */
/*   Updated: 2025/12/07 04:45:32 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "getnextline_FINAL.h"

char	*get_next_line(int fd)
{
	static 			t_g	x;
	static	char	x.buff[BUFFER_SIZE + 1];

	printf("buffer[end]: %c\nend: %d\nreadbytes: %d\n\n", x.buff[x.end], x.end, x.rbts);
	if ((fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > MAX))
		return (NULL);
	*(t_w *)&x = (t_w){0, 0, -1, 0, 0, x.end + ((x.buff[x.end]) == 10)};
	printf("buffer[end]: %c\nend: %d\nreadbytes: %d\n\n", x.buff[x.end], x.end, x.rbts);
	printf("start: %d\nend: %d\nreadbytes: %d\nindex: %d\nallend: %d\n\n", x.start, x.end, x.rbts, x.index, x.allend);
	if (x.rbts <= 0 || x.start >= x.rbts)
	{
		x = (t_g){NULL, NULL, -1, 0, 0, BUFFER_SIZE, BUFFER_SIZE, 1, {0}, 0};
		printf("start: %d\nend: %d\nreadbytes: %d\nindex: %d\nallend: %d\n\n", x.start, x.end, x.rbts, x.index, x.allend);
	}		
	while ((x.line == NULL || x.buff[x.end] != 10) && x.rbts > 0)
	{
		(x.start >= x.rbts) && (x.rbts = read(fd, x.buff, BUFFER_SIZE));
		(x.start >= x.rbts) && (*(long *)&x.end = 0);
		printf("buffer[end]: %c\nend: %d\nreadbytes: %d\n\n", x.buff[x.end], x.end, x.rbts);
		exit (1);
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
		printf("start antes de t_z: %d\n\n", x.start);
		*(t_z *)&x = (t_z){(void *)((long)x.nln * (x.rbts > 0)), x.nln, -1, 0};
		printf("start depois de t_z: %d\n\n", x.start);
		exit(1);
		printf("index: %d\n\n", x.index);
	}
	return (free((char *)((long)x.nln * (x.rbts <= 0))), x.line);
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

