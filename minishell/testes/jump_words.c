/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_jump_words.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 03:38:16 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/19 04:03:34 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	print_string_from_index(char *string, int index)
{
	if (!string)
		return ;
	if (string[index] == ' ')
	{
		printf("e espaco\n");
		return ;
	}
	while (string[index])
		write(1, &string[index++], 1);	
	write(1, "\n", 1);
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
		else if (string[*index] == ' ');
			(*index)++;
	}
	return (1);
}

int	main(void)
{
	char *string = "oi tudo bem com voce";
	int	index = 0;
	jump_words(2, string, &index);
	print_string_from_index(string, index);
}