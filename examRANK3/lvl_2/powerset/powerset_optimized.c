/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset_optimized.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 22:51:41 by olacerda          #+#    #+#             */
/*   Updated: 2025/12/06 20:25:07 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "powerset.h"
#include <sys/time.h>

void	print_number(int number)
{
	if (number < 0)
	{
		number = -number;
		write(1, "-", 1);
	}
	if (number > 9)
		print_number(number / 10);
	write(1, &"0123456789"[number % 10], 1);
}

int	*create_array(char *argv[], int argc, int size)
{
	int *array;
	int index;
	int index2;

	if (!argv || (size <= 0))
		return (NULL);
	array = malloc((size) * sizeof(int));
	if (!array)
		return (NULL);
	index = 0;
	index2 = 2;
	while ((index < size) && (index2 < argc))
	{
		array[index] = atoi(argv[index2]);
		index++;
		index2++;
	}
	return (array);
}

int	*create_dup(int size)
{
	int *array;
	int index;

	if (size <= 0)
		return (NULL);
	array = malloc((size) * sizeof(int));
	if (!array)
		return (NULL);
	index = 0;
	while (index < size)
	{
		array[index] = 0;
		index++;
	}
	return (array);
}

int	add_number(int *dup, int *array, int size, int *pos, int *focused)
{
	if (!dup || !array || !size)
		return (-1);
	if (((*focused) >= size) || ((*pos) >= size))
		return (0);
	dup[*focused] = array[*pos];
	(*pos)++;
	(*focused)++;
	return (1);
}

int	increment_number(int *dup, int *focused, int *array, int size, int *pos)
{
	int index;
	int target;

	if (!dup || !array || !size)
		return (-1);
	index = 0;
	(*focused)--;
	if (((*focused) < 0) || (dup[(*focused)] == array[size - 1]))
	{
		(*focused)++;
		return (0);
	}
	target = dup[(*focused)];
	while ((index < size) && (array[index] != target))
		index++;
	if (((index + 1) < size) && (array[index] == target))
		dup[(*focused)] = array[index + 1];
	(*pos) = index + 2;
	(*focused)++;
	return (1);
}

int	print_array(int *array, int size)
{
	int index;

	if (!array || !size)
		return (0);
	index = 0;
	while (index < size)
	{
		print_number(array[index]);
		if (index < (size - 1))
			write(1, " ", 1);
		index++;
	}
	write(1, "\n", 1);
	return (1);
}

int	remove_number(int *dup, int *focused)
{
	if (!dup)
		return (0);
	(*focused)--;
	if ((*focused) < 0)
		return (0);
	dup[*focused] = 0;
	return (1);
}

int	check_result(int *array, int target, int focused)
{
	int index;
	int	result;

	if (!array)
		return (0);
	result = 0;
	index = 0;
	while (index < focused)
	{
		result += array[index];
		index++;
	}
	if (result == target)
		return (1);
	if (result > target)
		return (-1);
	return (0);
}

int	do_main_loop(int *array, int *dup, int size, int target)
{
	t_time time;
	static long now;
	static long then;
	int pos;
	int	focused;
	int	add;
	int	increment;
	int	check;
	int result;

	if (!array || !dup || !size)
		return (0);
	focused = 0;
	pos = 0;
	add = 0;
	increment = 0;
	check = 0;
	gettimeofday(&time, NULL);
	now = time.tv_sec;
	result = 0;
	while (1)
	{
		add = add_number(dup, array, size, &pos, &focused);
		if (!add)
		{
			result -= dup[focused - 1];
			increment = increment_number(dup, &focused, array, size, &pos);
			if (!increment)
			{
				if (!remove_number(dup, &focused))
				{
					gettimeofday(&time, NULL);
					then = time.tv_sec;
					printf("timer: %li\n\n", then - now);
					break ;
				}
			}
			else
				result += dup[focused - 1];
		}
		else
			result += dup[focused - 1];
		// check = check_result(dup, target, focused);
		if (result == target)
		{
			print_array(dup, focused);
			result -= dup[focused - 1];
			if (!remove_number(dup, &focused))
			{
				gettimeofday(&time, NULL);
				then = time.tv_sec;
				printf("timer: %li\n\n", then - now);				
				break ;
			}
		}
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	
	system("date +\"%N\" >> log");
	int *array;
	int *dup;
	int	target;
	int size;

	if (argc < 2)
		return (1);
	size = argc - 2;
	target = atoi(argv[1]);
	array = create_array(argv, argc, size);
	if (!array)
		return (1);
	dup = create_dup(size);
	if (!dup)
		return (free(array), 1);
	do_main_loop(array, dup, size, target);
	free(array);
	free(dup);
	system("date +\"%N\" >> log");
}
 