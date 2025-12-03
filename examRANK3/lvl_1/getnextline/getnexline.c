/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnexline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 07:05:04 by olacerda          #+#    #+#             */
/*   Updated: 2025/11/27 17:49:48 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "getnextline.h"

char *getnextline(int fd)
{
	static t_gnl x = {BUFFER_SIZE, 0, BUFFER_SIZE};
	static char buffer[BUFFER_SIZE];
	char *line;
	char *newline;
	int	totalend;
	int	index;

	line = NULL;
	newline = NULL;
	totalend = 0;
	if (BUFFER_SIZE <= 0 || fd <= 0)
		return (NULL);
	if (x.readbytes <= 0 || x.start >= x.readbytes)
		x = (t_gnl){BUFFER_SIZE, 0, BUFFER_SIZE};
	while ((buffer[x.end] != '\n' || line == NULL) && x.readbytes > 0)
	{
		if (x.start >= x.readbytes)
		{
			x.readbytes = read(fd, buffer, BUFFER_SIZE);
			x.start = 0;
			x.end = 0;
		}
		if (x.readbytes == -1)
			return (free(line), NULL);
		if (x.readbytes == 0)
			break ;
		while ((buffer[x.end] != '\n') && (x.end < BUFFER_SIZE))
		{
			x.end++;
			totalend++;
		}
		newline = malloc((totalend + 1 + (buffer[x.end] == '\n')) * sizeof(char));
		if (!newline)
			return (free(line), NULL);
		index = 0;
		while ((index < (totalend - x.end)) && (line))
		{
			newline[index] = line[index];
			index++;
		}
		while ((x.start <= x.end) && (x.start < x.readbytes))
			newline[index++] = buffer[x.start++];
		newline[index] = '\0';
		free(line);
		line = newline;
	}
	x.end += (buffer[x.end] == '\n');
	return (line);
}

int	main(void)
{
	char *result;
	int	fd;

	fd = open("teste1.txt", O_RDONLY);
	result = " ";
	while (result != NULL)
	{
		result = getnextline(fd);
		if (result != NULL)
			printf("%s", result);
		free(result);
	}
	// result = getnextline(fd);
	// if (result != NULL)
	// 	printf("%s", result);
	// free(result);
	// result = getnextline(fd);
	// if (result != NULL)
	// 	printf("%s", result);
	// write(1, "\n", 1);
	return (0);
}