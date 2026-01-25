/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:08:39 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/22 19:52:32 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_g	x;

	*(t_w *)&x = (t_w){0, -1, 0, 0, 0, x.end + ((x.buff[x.end]) == 10)};
	(x.rb <= 0 || x.st >= x.rb) && (x = (t_g){0, -1, 0, 0, 0, B, B, 1, {0}}, 0);
	((fd < 0 || BUFFER_SIZE <= 0)) && (x.rb = 0);
	while ((x.rb > 0) && (x.line == NULL || x.buff[x.end] != 10))
	{
		(x.st >= x.rb) && (x.rb = read(fd, x.buff, B), *(long *)&x.end = 0, 0);
		while ((x.end < x.rb) && (x.buff[x.end] != 10) && ++(x.end))
			++(x.allend);
		(x.rb > 0) && (x.l2 = malloc(x.allend + 1 + (x.buff[x.end] == 10)));
		(!x.l2) && (x.rb = -2);
		while (++x.index < (x.allend - x.end) && x.line && x.rb > 0)
			x.l2[x.index] = x.line[x.index];
		while ((x.st <= x.end) && (x.st < x.rb) && x.rb > 0 && x.l2)
			x.l2[x.index++] = x.buff[x.st++];
		free((char *)((long)x.line * (x.rb != 0)));
		x.rb && (*(t_z *)&x = (t_z){(char *)((long)x.l2 * (x.rb > 0)), -1}, 0);
	}
	return ((x.line) && (x.line[x.allend + (x.buff[x.end] == 10)] = 0), x.line);
}

int	main(void)
{
	int fd;
	char *line1 = "";

	fd = open("./teste1.txt", O_RDONLY);
	line1 = get_next_line(0);
	if(line1 != NULL)
		printf("You wrote ->%s", line1);
	free(line1);
	// while (line1 != NULL)
	// {
	// }
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
	free(line5);

	// line5 = get_next_line(fd);
	// printf("GET6:  %s\n\n", line5);
	free(line1);
	free(line2);
	free(line3);
	free(line4);
	free(line5);
}
