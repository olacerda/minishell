/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realock_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 11:48:30 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/07 15:42:59 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	string_length(char *string)
{
	int	size;

	if (!string)
		return (0);
	size = 0;
	while (string[size])
		size++;
	return (size);
}

int	string_copy(char *string, char *to_copy)
{
	int	index;

	if (!string)
		return (0);
	index = -1;
	while (to_copy[++index])
		string[index] = to_copy[index];
	// printf("putting char nul in index: %d\n", index);
	return (string[index] = '\0', 1);
}

void	*re_allocker(void *pointer, long size, long new_size, long type_size)
{
	void 	*new_pointer;
	long 	x1;
	long	x2;

	// printf("inicio\n");
	if (!pointer || !new_size || !type_size)
		return (NULL);
	new_pointer = malloc(new_size * type_size);
	// printf("newsize * type = %li\n", (new_size * type_size));
	if (!new_pointer)
		return (NULL);
	size = size * type_size;
	new_size = new_size * type_size;
	x1 = -1;
	// printf("meio\n");
	while (++x1 < new_size)
		((char *)new_pointer)[x1] = '\0';
	x1 = -1;
	x2 = -1;
	while ((++x1 < new_size) && (++x2 < size))
		((char *)new_pointer)[x1] = ((char *)pointer)[x2];
	free(pointer);
	// printf("fim\n");

	return (new_pointer);
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

int	realloc_appender(char **string, char *content)
{
	int	index;
	int	string_size;
	int	new_size;
	
	if (!string || !(*string))
		return (-1);
	new_size = 0;
	string_size += string_length(*string);
	new_size += string_size;
	new_size += string_length(content);
	*string = re_allocker(*string, (string_size + 1), (new_size + 1), sizeof(char));
	if (!(*string))
		return (printf("oi\n"), 0);
	string_cat(*string, (new_size + 1), content);
	return (1);
}



int	main(void)
{
	char *line = NULL;
	char *to_copy = "abcd";

	line = malloc((string_length(to_copy) + 1) * sizeof(char));
	if (!line)
		return (0);
	string_copy(line, to_copy);
	printf("line:\n%s\n", line);
	printf("Colado na de cima\n\n");

	realloc_appender(&line, "  eai  xuxu\n");
	
	printf("line:\n%s\n", line);
	printf("Colado na de cima\n\n");
}