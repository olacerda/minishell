/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_getnextline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:34:51 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/19 17:15:58 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *liner(t_gnl *gnl, int *total_end, char **line)
{
	char 	*newline;
	int		index;

	newline = NULL;
	while ((gnl->end < gnl->readbytes) && (gnl->buffer[gnl->end] != '\n'))
	{
		gnl->end++;
		(*total_end)++;
	}
	newline = malloc((*total_end + (gnl->buffer[gnl->end] == '\n') + 1));
	if (!newline)
		return (free(*line), NULL);
	index = 0;
	while ((index < (*total_end - gnl->end)) && (newline) && (*line))
	{
		newline[index] = (*line)[index];
		index++;
	}
	while ((gnl->start <= gnl->end) && (gnl->start < gnl->readbytes) && (newline))
	{
		newline[index] = gnl->buffer[gnl->start];
		index++;
		gnl->start++;
	}
	return (newline[index] = '\0', free(*line), newline);
}

char *get_next_line(int fd)
{
	static	t_gnl gnl[FD_SETSIZE];
	char *line;
	int	total_end;

	if ((BUFFER_SIZE <= 0) || (fd < 0))
		return (NULL);
	if ((gnl[fd].readbytes <= 0) || (gnl[fd].start >= gnl[fd].readbytes))
		gnl[fd] = (t_gnl){BUFFER_SIZE, 0, BUFFER_SIZE, {0}};
	total_end = 0;
	line = NULL;
	while (((gnl[fd].buffer[gnl[fd].end] != '\n') || (line == NULL))
		&& (gnl[fd].readbytes > 0))
	{
		if (gnl[fd].start >= gnl[fd].readbytes)
		{
			gnl[fd].readbytes = read(fd, gnl[fd].buffer, BUFFER_SIZE);
			if (gnl[fd].readbytes == -1)
				return (free(line), NULL);
			if (gnl[fd].readbytes == 0)
				break ;
			*(long *)&(gnl[fd].start) = 0;
		}
		line = liner(&gnl[fd], &total_end, &line);
	}
	return (gnl[fd].end += (gnl[fd].buffer[gnl[fd].end] == '\n'), line);
}

int main(void)
{
    char    *line;

    while (1)
    {
        line = get_next_line(0);
        if (!line)
            break ;
		printf("You wrote: %s", line);
        // free(line);
    }
	int fd1;
	int	fd2;
	int	fd3;

    fd1 = open("./teste1.txt", O_RDONLY);
	fd2 = open("./teste2.txt", O_RDONLY);
	fd3 = open("./teste3.txt", O_RDONLY);

	char *line1 = get_next_line(fd1);
    printf("GET1:  %s\n", line1);
	free(line1);
    char *line2 = get_next_line(fd2);
    printf("GET2:  %s\n", line2);
	free(line2);
    char *line3 = get_next_line(fd3);
    printf("GET3:  %s\n", line3);
	free(line3);
	line1 = get_next_line(fd1);
    printf("GET1:  %s\n", line1);
	free(line1);
    line2 = get_next_line(fd2);
    printf("GET2:  %s\n", line2);
	free(line2);
    line3 = get_next_line(fd3);
    printf("GET3:  %s\n", line3);
	free(line3);
	line1 = get_next_line(fd1);
    printf("GET1:  %s\n", line1);
	free(line1);
    line2 = get_next_line(fd2);
    printf("GET2:  %s\n", line2);
	free(line2);
    line3 = get_next_line(fd3);
    printf("GET3:  %s\n", line3);
	free(line3);
	line1 = get_next_line(fd1);
    printf("GET1:  %s\n", line1);
	free(line1);
    line2 = get_next_line(fd2);
    printf("GET2:  %s\n", line2);
	free(line2);
    line3 = get_next_line(fd3);
    printf("GET3:  %s\n", line3);
	free(line3);
	line1 = get_next_line(fd1);
    printf("GET1:  %s\n", line1);
	free(line1);
    line2 = get_next_line(fd2);
    printf("GET2:  %s\n", line2);
	free(line2);
    line3 = get_next_line(fd3);
    printf("GET3:  %s\n", line3);
	free(line3);

    close(fd1);
    close(fd2);
    close(fd3);
	printf("\n\nAfter close\n\n");

    fd1 = open("./teste1.txt", O_RDONLY);
	fd2 = open("./teste2.txt", O_RDONLY);
	fd3 = open("./teste3.txt", O_RDONLY);

	line1 = get_next_line(fd1);
    printf("GET1:  %s\n", line1);
	free(line1);
    line2 = get_next_line(fd2);
    printf("GET2:  %s\n", line2);
	free(line2);
    line3 = get_next_line(fd3);
    printf("GET3:  %s\n", line3);
	free(line3);
	line1 = get_next_line(fd1);
    printf("GET1:  %s\n", line1);
	free(line1);
    line2 = get_next_line(fd2);
    printf("GET2:  %s\n", line2);
	free(line2);
    line3 = get_next_line(fd3);
    printf("GET3:  %s\n", line3);
	free(line3);
	line1 = get_next_line(fd1);
    printf("GET1:  %s\n", line1);
	free(line1);
    line2 = get_next_line(fd2);
    printf("GET2:  %s\n", line2);
	free(line2);
    line3 = get_next_line(fd3);
    printf("GET3:  %s\n", line3);
	free(line3);
	line1 = get_next_line(fd1);
    printf("GET1:  %s\n", line1);
	free(line1);
    line2 = get_next_line(fd2);
    printf("GET2:  %s\n", line2);
	free(line2);
    line3 = get_next_line(fd3);
    printf("GET3:  %s\n", line3);
	free(line3);
	line1 = get_next_line(fd1);
    printf("GET1:  %s\n", line1);
	free(line1);
    line2 = get_next_line(fd2);
    printf("GET2:  %s\n", line2);
	free(line2);
    line3 = get_next_line(fd3);
    printf("GET3:  %s\n", line3);
	free(line3);
	close(fd1);
	close(fd2);
	close(fd3);
}