/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 07:21:00 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/06 06:31:37 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <utils.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../../minishell.h"

static char *liner(t_gnl *gnl, int *total_end, char **line)
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
	while ((gnl->start <= gnl->end) && (gnl->start < gnl->readbytes) && newline)
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
			// if ((line && line[total_end] != '\n'))
			// 	break ;
			gnl[fd].readbytes = read(fd, gnl[fd].buffer, BUFFER_SIZE);
			// dprintf(2, "readbytes: %d\n", gnl[fd].readbytes);
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

// char *get_next_line(int fd, int *size, int *sig)
// {
// 	static	t_gnl gnl[FD_SETSIZE];
// 	char *line;
// 	int	total_end;

// 	if ((BUFFER_SIZE <= 0) || (fd < 0))
// 		return (NULL);
// 	if ((gnl[fd].readbytes <= 0) || (gnl[fd].start >= gnl[fd].readbytes))
// 		gnl[fd] = (t_gnl){BUFFER_SIZE, 0, BUFFER_SIZE, {0}};
// 	total_end = 0;
// 	line = NULL;
// 	while (((gnl[fd].buffer[gnl[fd].end] != '\n') || (line == NULL))
// 		&& !((gnl[fd].readbytes == 0) && (line == NULL)) && (*sig != SIGINT))
// 	{
// 		if (gnl[fd].start >= gnl[fd].readbytes)
// 		{
// 			gnl[fd].readbytes = read(fd, gnl[fd].buffer, BUFFER_SIZE);
// 			// dprintf(2, "foi interrompido\n");
// 			if (gnl[fd].readbytes == -1)
// 				return (free(line), NULL);
// 			*(long *)&(gnl[fd].start) = 0;
// 		}
// 		(void)((gnl[fd].readbytes > 0) && (line = liner(&gnl[fd], &total_end, &line)));
// 		(void)((gnl[fd].readbytes > 0) && (*size = total_end));
// 	}
// 	// dprintf(2, "saiu do getnextline\n");
// 	return (gnl[fd].end += (gnl[fd].buffer[gnl[fd].end] == '\n'), line);
// }
