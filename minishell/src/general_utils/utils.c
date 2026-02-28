/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:47:45 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/28 11:51:30 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

int	clear_string(char *string, int size)
{
	int	index;

	if (!string || (size <= 0))
		return (0);
	index = 0;
	while (index < size)
	{
		string[index] = '\0';
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

int	print_string(char *string)
{
	int	size;

	if (!string)
		return (0);
	size = 0;
	while (string[size])
		size++;
	write(1, string, size);
	return (1);
}

int	string_copy(char *str1, char *str2)
{
	int	index;

	if (!str1 || !str2)
		return (0);
	index = 0;
	while (str2[index] != '\0')
	{
		str1[index] = str2[index];
		index++;
	}
	str1[index] = '\0';
	return (1);
}

int	string_cat(char *string1, int size, char *string2)
{
	int	x1;
	int x2;
	
	if (!string1 || !string2)
		return (0);
	x1 = 0;
	while (string1[x1] != '\0')
		x1++;
	x2 = 0;
	while ((string2[x2] != '\0'))
	{
		if (x1 >= size)
			break;
		string1[x1] = string2[x2];
		x1++;
		x2++;
	}
	string1[x1] = '\0';
	return (1);
}

char *string_duplicate(char *string)
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
	while ((str1[i] && str2[i]) && (str1[i] == str2[i])
				&& (str1[i + 1] != '\n'))
		i++;
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

void	*re_allocker(void *pointer, long size, long new_size, long type_size)
{
	void 	*new_pointer;
	long 	x1;
	long	x2;

	if (!pointer || !new_size || !type_size)
		return (NULL);
	new_pointer = malloc(new_size * type_size);
	if (!new_pointer)
		return (NULL);
	size = size * type_size;
	new_size = new_size * type_size;
	x1 = -1;
	while (++x1 < new_size)
		((char *)new_pointer)[x1] = '\0';
	x1 = -1;
	x2 = -1;
	while ((++x1 < new_size) && (++x2 < size))
		((char *)new_pointer)[x1] = ((char *)pointer)[x2];
	free(pointer);
	return (new_pointer);
}
int	swap_strings(char **str1, char **str2)
{
	char *temp;

	if (!str1 || !str2)
		return (0);
	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
	return (1);
}
