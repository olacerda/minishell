/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset_debug.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 22:51:41 by olacerda          #+#    #+#             */
/*   Updated: 2025/12/03 04:12:32 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "powerset.h"

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
		// print_number(array[index]);
		printf("%d", array[index]);
		fflush(stdout);
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
	// printf("target: %d\n", target);
	// write(1, "check_result: ", 14);
	// print_array(array, focused);
	while (index < focused)
	{
		result += array[index];
		// printf("array[index]: %d\n", array[index]);
		index++;
	}
	// printf("result: %d\n", result);
	if (result == target)
		return (1);
	if (result > target)
		return (-1);
	return (0);
}

int	do_main_loop(int *array, int *dup, int size, int target)
{
	int pos;
	int	focused;
	int	add;
	int	increment;
	int	check;

	if (!array || !dup || !size)
		return (0);
	focused = 0;
	pos = 0;
	add = 0;
	increment = 0;
	check = 0;
	// printf("array[size - 1]: %d\n\n", array[size - 1]);
	// exit (1);
	// int	count = 0;//
	while (1)
	{
		write(1, "1main ", 7);//
		print_array(dup, size);//
		add = add_number(dup, array, size, &pos, &focused);
		printf("add: %d\n", add);//
		if (!add)
		{
			increment = increment_number(dup, &focused, array, size, &pos);
			printf("increment: %d\n", increment);//
			if (!increment)
				if (!remove_number(dup, &focused))
					break ;
		}
		write(1, "2main: ", 7);//
		print_array(dup, size);//
		check = check_result(dup, target, focused);
		printf("check: %d\n", check);//
		if (check == 1)
		{
			print_array(dup, focused);
			if (!remove_number(dup, &focused))
				break ;
		}
		write(1, "3main ", 7);//
		print_array(dup, size);//
		write(1, "\n", 2);//
		printf("dup[0]: %d   array[size-1]:  %d\n\n", dup[0], array[size-1]);//
		// if (count > 30)//
		// {
		// 	write(1, "CARALHO2\n\n\n", 11);//
		// 	break ;//
		// }
		// count++;//
	}
	return (1);
}

int	main(int argc, char *argv[])
{
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
	printf("size: %d\n\n", size);
	printf("target: %d\n\n", target);
	do_main_loop(array, dup, size, target);
	write(1, "teste\n", 6);

	
	// int	index = 0;
	// printf("target: %d\n\n", target);
	// printf("size: %d\n\n", size);
	// while (index < size)
	// {
	// 	printf("%d", array[index]);
	// 	fflush(stdout);
	// 	if (index < (size - 1))
	// 		write(1, " ", 1);
	// 	index++;
	// }
	// write(1, "\n\n", 2);
	// index = 0;
	// while (index < size)
	// {
	// 	printf("%d", dup[index]);
	// 	fflush(stdout);
	// 	if (index < (size - 1))
	// 		write(1, " ", 1);
	// 	index++;
	// }
	// write(1, "\n", 1);

	if (array != NULL)
		free(array);
	if (dup != NULL)
		free(dup);
}