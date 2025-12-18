/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 01:09:31 by olacerda          #+#    #+#             */
/*   Updated: 2025/12/17 03:54:00 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rip.h"


int	permutate_once(long unsigned int permutator, int size)
{
	int					addition;
	int					last;
	int					count;
	int					previous;

	if (!permutator)
		return (0);
	addition = 1;
	count = 1;
	last = (permutator % 10);
	previous = ((permutator / 10) % 10);
	while ((last == 9) || ((previous == (last - 1)) && !(count > size) && (permutator > 0)))
	{
		permutator = permutator / 10;
		previous = ((permutator / 10) % 10);
		last = permutator % 10;
		count++;
	}
	permutator = ((permutator / 10) + 1);
	while (count > 0)
	{
		addition = permutator % 10;
		permutator = (permutator * 10) + (addition + 1);
		count--;
	}
	return (1);
}

// int	permutate_once(long unsigned int permutator, int limit, int size)
// {
// 	int					multiplier;
// 	int					addition;
// 	int					nbr_focused;
// 	int					count;
// 	int					backup;
// 	int					next;

// 	if (!permutator)
// 		return (-1);
// 	if (permutator >= (long unsigned int)limit)
// 		return (0);
// 	multiplier = 1;
// 	addition = 1;
// 	count = 0;
// 	nbr_focused = ((permutator / multiplier) % 10);
// 	next = -1;
// 	if (nbr_focused == 9)
// 	{
// 		while (((nbr_focused == (next - 1)) && !(count > size) && (permutator > 0)) || (next == -1))
// 		{
// 			printf("permutator: %lu\n\n", permutator);
// 			next = nbr_focused;
// 			multiplier *= 10;
// 			nbr_focused = ((permutator / multiplier) % 10);
// 			printf("nbr_focused: %d\n\n", nbr_focused);
// 			count++;
// 		}
// 		permutator = (permutator + multiplier);
// 	}
// 	backup = count;
// 	while (count > 0)
// 	{
// 		permutator /= 10;
// 		count--;
// 	}
// 	while (backup > 0)
// 	{
// 		addition = permutator % 10;
// 		permutator = (permutator * 10) + (addition + 1);
// 		backup--;
// 	}
// 	printf("permutator after: %lu\n\n", permutator);
// 	return (1);
// }

int	main(void)
{
	long unsigned int	permutator = 14789;
	int					limit = 56789;
	int					size = 5;

	write(1, "test\n", 5);
	printf("result: %d\n\n", permutate_once(permutator, limit, size));
}