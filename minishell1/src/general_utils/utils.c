/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:47:45 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/20 00:25:33 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

int	clear_buffer(char *string, int size)
{
	int	index;

	index = 0;
	if (!string || !size)
		return (0);
	while (index < size)
	{
		string[index] = 0;
		index++;
	}
	return (1);
}

int	string_lenght(char *string)
{
	int	size;

	size = 0;
	if (!string)
		return (0);
	while (string[size])
		size++;
	return (size);
}

char *string_copy(char *string)
{
	char *result;
	int	index;
	int	size;

	if (!string)
		return (NULL);
	size = string_lenght(string);
	result = malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	index = 0;
	while (string[index])
	{
		result[index] = string[index];
		index++;
	}
	result[index] = '\0';
	return (result);
}

int	string_compare(char *str1, char *str2)
{
	int	i;

	if (!str1 || !str2)
		return (0);
	i = 0;
	while ((str1[i] && str2[i]) && (str1[i] == str2[i]))
		i++;
	if ((str1[i] == '\n') || (str2[i] == '\n'))
		i--;
	return (str1[i] - str2[i]);
}

int	jump_words(int	quantity, char *string, int *index)
{
	int	count;

	if (!quantity || !string)
		return (-1);
	count = 0;
	while (count < quantity)
	{
		while ((string[*index]) && (string[*index] != ' ') && (string[*index] != '|'))
			(*index)++;
		count++;
		if (string[*index] == '\0')
			return (0) ;
		else if (string[*index] == ' ')
			(*index)++;
	}
	return (1);
}

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
