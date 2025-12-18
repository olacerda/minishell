/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:00:46 by olacerda          #+#    #+#             */
/*   Updated: 2025/12/18 15:10:06 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_g	x;

	*(t_w *)&x = (t_w){0, -1, x.st, x.end + ((x.buff[x.end]) == 10), 0, 0};
	(x.rb <= 0 || x.st >= x.rb) && (x = (t_g){0, -1, BF, BF, 0, 0, 1, {0}}, 1);
	((fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > MAX)) && (x.rb = 0);
	while ((x.line == NULL || x.buff[x.end] != 10) && x.rb > 0)
	{
		(x.st >= x.rb) && (x.rb = read(fd, x.buff, BF));
		(x.st >= x.rb) && (*(long *)&x.st = 0);
		while ((x.end < x.rb) && (x.buff[x.end] != 10) && ++(x.end) && x.rb > 0)
			++(x.allend);
		(x.rb > 0) && (x.new = malloc(x.allend + 1 + (x.buff[x.end] == 10)));
		(!x.new) && (x.rb = -2);
		while (++x.idx < (x.allend - x.end) && x.line && x.rb > 0)
			x.new[x.idx] = (x.line)[x.idx];
		while ((x.st <= x.end) && (x.st < x.rb) && x.rb > 0)
			x.new[x.idx++] = x.buff[x.st++];
		free((char *)((long)x.line * ((x.rb > 0) || (x.rb == -2))));
		x.rb && (*(t_z *)&x = (t_z){(char *)((long)x.new * (x.rb > 0)), -1}, 1);
	} 
	return ((x.line) && (x.line[x.allend + (x.buff[x.end] == 10)] = 0), x.line);
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

