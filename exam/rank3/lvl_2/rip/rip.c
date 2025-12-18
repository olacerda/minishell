/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 08:40:32 by olacerda          #+#    #+#             */
/*   Updated: 2025/12/17 12:19:01 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rip.h"

int	print_string(char *string)
{
	int	index;

	if (!string)
		return (0);
	index = 0;
	while (string[index])
	{
		if ((string[index]) && ((string[index] == 'R') || (string[index] == 'L')))
			write(1, " ", 1);
		else
			write(1, &string[index], 1);
		index++;
	}
	write(1, "\n", 1);
	return (1);
}

int	refresh_string(char *string)
{
	int	index;

	if (!string)
		return (0);
	index = 0;
	while (string[index])
	{
		if (string[index] == 'R')
			string[index] = ')';
		else if (string[index] == 'L')
			string[index] = '(';
		index++;
	}
	return (1);
}

int	calculate_gap(char *string)
{
	int idx1;
	int idx2;

	if (!string)
		return (0);
	idx1 = 0;
	while (string[idx1])
	{
		if (string[idx1] == '(')
		{
			idx2 = idx1;
			while ((string[idx2]) && (string[idx2] != ')'))
				idx2++;
			if (string[idx2] == ')')
			{
				string[idx1] = 'L';
				string[idx2] = 'R';
			}
		}
		idx1++;
	}
	idx1 = 0;
	idx2 = 0;
	while (string[idx1])
	{
		if ((string[idx1] == '(') || (string[idx1] == ')'))
			idx2++;
		idx1++;
	}
	refresh_string(string);
	return (idx2);
}

int	string_lenght(char *string)
{
	int	size;

	if (!string)
		return (0);
	size = 0;
	while (string[size])
		size++;
	return (size);
}

long unsigned int	calculate_permutator(int gap)
{
	long unsigned int 	result;
	int					unit;

	if (!gap)
		return (0UL);
	unit = 1;
	result = 0;
	while (gap > 0)
	{
		result = (result + unit);
		unit++;
		gap--;
		if (gap > 0)
			result *= 10;
	}
	return (result);
}

int	check_result(char *string)
{
	int	flag;
	int	idx1;
	int	idx2;

	if (!string)
		return (0);
	idx1 = 0;
	while (string[idx1])
	{
		flag = 0;
		while ((string[idx1]) && ((string[idx1] == 'R') || (string[idx1] == 'L')))
			idx1++;
		if (string[idx1] == '(')
		{
			idx2 = idx1;
			idx2++;
			while ((string[idx2]) && ((string[idx2] == 'R') || (string[idx2] == 'L')))
				idx2++;
			if (string[idx2] == ')')
			{
				string[idx1] = 'L';
				string[idx2] = 'R';
				idx1 = 0;
				flag = 1;
			}
		}
		if (flag == 0)
			idx1++;
	}
	idx1 = 0;
	while(string[idx1])
	{
		if ((string[idx1] == '(') || (string[idx1] == ')'))
			return (0);
		idx1++;
	}
	return (1);
}

int	remove_parenteses(char *string, long unsigned int permutator)
{
	if (!string || !permutator)
		return (0);
	while (permutator > 0)
	{
		permutator -= 1;
		if (string[permutator % 10] == '(')
			string[permutator % 10] = 'L';
		else if (string[permutator % 10] == ')')
			string[permutator % 10] = 'R';
		permutator /= 10;
	}
	return (1);
}

int	calculate_number_size(long unsigned int permutator)
{
	int	size;

	if (!permutator)
		return (0);
	size = 0;
	while (permutator > 0)
	{
		size++;
		permutator /= 10;
	}
	return (size);
}


int	calculate_final_number(int number, int strlen)
{
	int	multiplier;
	int	result;

	if (!number)
		return (0);
	(void)strlen;
	result = 0;
	multiplier = 1;
	while (number > 0)
	{
		result = result + (strlen * multiplier);
		strlen--;
		multiplier *= 10;
		number--;
	}
	return (result);
}

int	permutate_once(long unsigned int *permutator, int gap, int strlen)
{
	int					last;
	int					addition;
	int					count;

	if (!(*permutator))
		return (0);
	addition = 1;
	count = 0;
	last = ((*permutator) % 10);
	if (last == strlen)
	{
		while ((((last == strlen) && (count < gap) && ((*permutator) > 0))) && (gap > 1))
		{
			(*permutator) = (*permutator) / 10;
			last = (*permutator) % 10;
			count++;
			strlen--;
		}
	}
	(*permutator)++;
	while (count > 0)
	{
		addition = (*permutator) % 10;
		(*permutator) = ((*permutator) * 10) + (addition + 1);
		count--;
	}
	return (1);
}


int	do_main_loop(char *string, long unsigned int permutator, int limit, int size, int strlen)
{
	int	check;

	if (!string)
		return (0);
	int	count = 0;
	while (1)
	{
		count++;
		// printf("permutator: %lu\n", permutator);
		remove_parenteses(string, permutator);
		check = check_result(string);
		if (check == 1)
		{
			refresh_string(string);
			remove_parenteses(string, permutator);
			print_string(string);
		}
		refresh_string(string);
		permutate_once(&permutator, size, strlen);
		if (permutator > (long unsigned int)limit)
		{
			printf("count: %d\n", count);
			break ;
		}
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	char 				*original;
	int					strlen;
	long unsigned int	permutator;
	int					gap;
	int					limit;

	if (argc != 2)
		return (1);
	original = argv[1];
	gap = calculate_gap(original);
	permutator = calculate_permutator(gap);
	strlen = string_lenght(original);
	if (!strlen || strlen > 9)
		return (1);
	limit = calculate_final_number(gap, strlen);
	if (!gap)
		print_string(original);
	else
		do_main_loop(original, permutator, limit, gap, strlen);	
	return (0);
}