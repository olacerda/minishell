/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:08:39 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/21 03:15:59 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_g	x[FD_SETSIZE];

	if (F < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	*(t_w *)&x[F] = (t_w){0, -1, 0, 0, 0, x[F].e + ((x[F].b[x[F].e]) == 10)};
	if (x[F].rb <= 0 || x[F].s >= x[F].rb)
		x[F] = (t_g){0, -1, 0, 0, 0, B, B, 1, {0}};
	while (x[F].rb > 0 && (x[F].l == NULL || x[F].b[x[F].e] != 10))
	{
		(x[F].s >= x[F].rb) && (x[F].rb = read(F, x[F].b, BUFFER_SIZE));
		(x[F].s >= x[F].rb) && (x[F].rb > 0) && (*(long *)&x[F].e = 0);
		while ((x[F].e < x[F].rb) && (x[F].b[x[F].e] != 10) && ++(x[F].e))
			++(x[F].a);
		(x[F].rb > 0) && (x[F].n = malloc(x[F].a + 1 + (x[F].b[x[F].e] == 10)));
		(!x[F].n) && (x[F].rb = -2);
		while (++x[F].i < (x[F].a - x[F].e) && x[F].l && x[F].n && x[F].rb > 0)
			x[F].n[x[F].i] = x[F].l[x[F].i];
		while ((x[F].s <= x[F].e) && x[F].s < x[F].rb && x[F].rb > 0 && x[F].n)
			x[F].n[x[F].i++] = x[F].b[x[F].s++];
		free((char *)((long)x[F].l * ((x[F].rb < 0) || (x[F].rb > 0))));
		if (x[F].rb)
			*(t_z *)&x[F] = (t_z){(char *)((long)x[F].n * (x[F].rb >= 0)), -1};
	}
	return ((x[F].l) && (x[F].l[x[F].a + (x[F].b[x[F].e] == 10)] = 0), x[F].l);
}

// int main(void)
// {
//     char    *line;

//     while (1)
//     {
//         line = get_next_line(0);
//         if (!line)
//             break ;
// 		printf("You wrote: %s", line);
//         free(line);
//     }
// 	int fd1;
// 	int	fd2;
// 	int	fd3;

//     fd1 = open("./teste1.txt", O_RDONLY);
// 	fd2 = open("./teste2.txt", O_RDONLY);
// 	fd3 = open("./teste3.txt", O_RDONLY);

// 	char *line1 = get_next_line(fd1);
//     printf("GET1:  %s\n", line1);
// 	free(line1);
//     char *line2 = get_next_line(fd2);
//     printf("GET2:  %s\n", line2);
// 	free(line2);
//     char *line3 = get_next_line(fd3);
//     printf("GET3:  %s\n", line3);
// 	free(line3);
// 	line1 = get_next_line(fd1);
//     printf("GET1:  %s\n", line1);
// 	free(line1);
//     line2 = get_next_line(fd2);
//     printf("GET2:  %s\n", line2);
// 	free(line2);
//     line3 = get_next_line(fd3);
//     printf("GET3:  %s\n", line3);
// 	free(line3);
// 	line1 = get_next_line(fd1);
//     printf("GET1:  %s\n", line1);
// 	free(line1);
//     line2 = get_next_line(fd2);
//     printf("GET2:  %s\n", line2);
// 	free(line2);
//     line3 = get_next_line(fd3);
//     printf("GET3:  %s\n", line3);
// 	free(line3);
// 	line1 = get_next_line(fd1);
//     printf("GET1:  %s\n", line1);
// 	free(line1);
//     line2 = get_next_line(fd2);
//     printf("GET2:  %s\n", line2);
// 	free(line2);
//     line3 = get_next_line(fd3);
//     printf("GET3:  %s\n", line3);
// 	free(line3);
// 	line1 = get_next_line(fd1);
//     printf("GET1:  %s\n", line1);
// 	free(line1);
//     line2 = get_next_line(fd2);
//     printf("GET2:  %s\n", line2);
// 	free(line2);
//     line3 = get_next_line(fd3);
//     printf("GET3:  %s\n", line3);
// 	free(line3);

//     close(fd1);
//     close(fd2);
//     close(fd3);
// 	printf("\n\nAfter close\n\n");

//     fd1 = open("./teste1.txt", O_RDONLY);
// 	fd2 = open("./teste2.txt", O_RDONLY);
// 	fd3 = open("./teste3.txt", O_RDONLY);

// 	line1 = get_next_line(fd1);
//     printf("GET1:  %s\n", line1);
// 	free(line1);
//     line2 = get_next_line(fd2);
//     printf("GET2:  %s\n", line2);
// 	free(line2);
//     line3 = get_next_line(fd3);
//     printf("GET3:  %s\n", line3);
// 	free(line3);
// 	line1 = get_next_line(fd1);
//     printf("GET1:  %s\n", line1);
// 	free(line1);
//     line2 = get_next_line(fd2);
//     printf("GET2:  %s\n", line2);
// 	free(line2);
//     line3 = get_next_line(fd3);
//     printf("GET3:  %s\n", line3);
// 	free(line3);
// 	line1 = get_next_line(fd1);
//     printf("GET1:  %s\n", line1);
// 	free(line1);
//     line2 = get_next_line(fd2);
//     printf("GET2:  %s\n", line2);
// 	free(line2);
//     line3 = get_next_line(fd3);
//     printf("GET3:  %s\n", line3);
// 	free(line3);
// 	line1 = get_next_line(fd1);
//     printf("GET1:  %s\n", line1);
// 	free(line1);
//     line2 = get_next_line(fd2);
//     printf("GET2:  %s\n", line2);
// 	free(line2);
//     line3 = get_next_line(fd3);
//     printf("GET3:  %s\n", line3);
// 	free(line3);
// 	line1 = get_next_line(fd1);
//     printf("GET1:  %s\n", line1);
// 	free(line1);
//     line2 = get_next_line(fd2);
//     printf("GET2:  %s\n", line2);
// 	free(line2);
//     line3 = get_next_line(fd3);
//     printf("GET3:  %s\n", line3);
// 	free(line3);
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// }