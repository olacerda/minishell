/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 09:40:58 by olacerda          #+#    #+#             */
/*   Updated: 2025/12/18 11:02:57 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

char *gnl(int fd)
{
	static t_gnl	x;
	int				totalend;
	int				index;
	char			*line;
	char			*newline;
	
	if ((BUFFER_SIZE <= 0) || (fd < 0))
		return (NULL);
	totalend = 0;
	line = NULL;
	newline = NULL;
	if (x.start >= x.readbytes)
		x = (t_gnl){BUFFER_SIZE, 0, BUFFER_SIZE, {0}};
	while (((x.buff[x.end] != '\n') || (line == NULL)) && (x.readbytes > 0))
	{
		(void)((x.start >= x.readbytes) && (x.readbytes = read(fd, x.buff, BUFFER_SIZE)));
		(void)((x.start >= x.readbytes) && (*(long *)&x = 0));
		if (x.readbytes == -1)
			return (free(line), NULL);
		if (x.readbytes == 0)
			break ;
		while ((x.buff[x.end] != '\n') && (x.end < x.readbytes) && (++x.end))
			totalend++;
		newline = malloc((totalend + (x.buff[x.end] == '\n') + 1) * sizeof(char));
		if (!newline)
			return (free(line), NULL);
		index = -1;
		while ((++index < (totalend - x.end)) && (line))
			newline[index] = line[index];
		while ((x.start <= x.end) && (x.start < x.readbytes))
			newline[index++] = x.buff[x.start++];
		free(line);
		line = newline;
	}
	return ((void)((line) && (line[index] = '\0')), x.end += (x.buff[x.end] == '\n'), line);
}

int	main(void)
{
	char *line = " ";
	int	fd;

	// while(1)
	// {
	// 	line = gnl(0);
	// 	if (!line)
	// 		break ;
	// 	// write(1, "saiu\n", 5);
	// 	printf("result -> %s", line);
	// 	// fflush(stdout);
	// 	// free(line);
	// }
	// return (1);
	while (line != NULL)
	{
		line = gnl(0);
		if (line)
		{
			printf("Result-> %s", line);
			free(line);
		}
	}

	
	fd = open("teste.txt", O_RDONLY);
	line = " ";
	while (line != NULL)
	{
		line = gnl(fd);
		if (line)
		{
			printf("%s", line);
			free(line);
		}
	}
	return (0);	
}