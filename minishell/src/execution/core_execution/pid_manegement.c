/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_manegement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:15:59 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/22 19:29:53 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core_execution.h>

int	create_buffer_children_pids(int **children_pids, int size)
{
	int	index;

	if (!children_pids || !size)
		return (0);
	index = 0;
	*children_pids = malloc(size * sizeof(int));
	while (index < size)
	{
		(*children_pids)[index] = -1;
		index++;
	}
	return (1);
}

int	wait_all_children(int *children_pids, int size)
{
	int	check_wait;
	int	index;

	if (!children_pids)
		return (0);
	index = 0;
	check_wait = 0;
	while (index < size)
	{
		check_wait = waitpid(children_pids[index], NULL, 0);
		if (check_wait == -1)
			return (0); //funcao de tratar erros... quando 2º argumento de waitpid != NULL (&status)
		index++;
	}
	return (1);
}