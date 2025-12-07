/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_wise.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 22:09:44 by otlacerd          #+#    #+#             */
/*   Updated: 2025/12/06 22:55:13 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	print_string2(char *string)
{
	int	index;

	index = 0;
	if (!string)
		return (1);
	while (string[index])
	{
		write(1, &string[index], 1);
		index++;
	}
	write(1, "\n", 1);
	return (0);
}

int	print_string(char *string)
{
	int	index;

	index = 0;
	if (!string)
		return (0);
	while (string[index])
	{
		write(1, &string[index], 1);
		index++;
	}
	write(1, "\n", 1);
	return (1);
}

int	main(void)
{
	char *string = "maca";
	char *string2 = "banana";
	char *string3 = "abacate";

	// int	pipeFirst[2];
	// pipeFirst[0] = 4;
	// pipeFirst[1] = 5;
	// int	pipeSecond[2];
	// pipeSecond[0] = 6;
	// pipeSecond[1] = 7;
	// *(long*)pipeFirst = *(long*)pipeSecond;
	
	// char *string1 = ">";
	// char *string2 = "ab";

	// if (*(short*)string1 == *(short*)">\0")




	
	


	
	if (print_string(string2) && (print_string2(string)
			& print_string(string3)))
		write(1, "result 1\n", 9);
	else
		write(1, "result 2\n", 9);
}