#include "permutations.h"

t_all *init_structure()
{
	t_all *all;

	all = malloc(sizeof(t_all));
	if (!all)
		return (NULL);
	*all = (t_all){0};
	return (all);
}

void	end_structure(t_all *all, int status)
{
	if (!all)
		return ;
	if (all->dup)
		free(all->dup);
	if (all)
		free(all);
	if (status == 0)
		exit (0);
	if (status == 1)
		exit (1);
}

void	fill_struct(t_all *all, char *argv[])
{
	all->original = argv[1];
	order_string(all->original);
	all->size = stringlenght(all->original);
	all->dup = string_dup(all, all->original, all->size);
	if (!all->dup)
		end_structure(all, 1);
}

char *string_dup(t_all *all, char *string, int size)
{
	char *dup;
	int	index;

	if (!all || !string || !size)
		return (NULL);
	dup = malloc((size + 1) * sizeof(char));
	if (!dup)
		end_structure(all, 1);
	index = 0;
	while (string[index])
	{
		dup[index] = string[index];
		index++;
	}
	dup[index] = '\0';
	return (dup);
}

int	stringlenght(char *string)
{
	int	size;

	if (!string)
		return (0);
	size = 0;
	while (string[size])
		size++;
	return (size);
}

int	print_string(char *string, int size)
{
	if (!string)
		return (0);
	// printf("size: %d\n\nstring: %s\n\n", size, string);
	// exit (1);
	write(1, string, size);
	write(1, "\n", 1);
	return (1);
}

int	swap_last_characters(char *string, int size)
{
	char temp;

	if (!string || !size)
		return (0);
	temp = string[size - 1];
	string[size - 1] = string[size - 2];
	string[size - 2] = temp;
	return (1);
}

int	do_last_double(char *string, int size)
{
	if (!string || !size)
		return (0);
	print_string(string, size);
	swap_last_characters(string, size);
	print_string(string, size);
	return (1);
}

int	check_for_doubles_left(char *dup, int focused)
{
	int	index;

	if (!dup || !focused)
		return (0);
	index = 0;
	while ((index < focused) && (dup[focused]) && (dup[index]))
	{
		if (dup[index] == dup[focused])
			return (1);
		index++;
	}
	return (0);
}

int	increment_letter(int focused, char *original, char *dup, int size)
{
	int	index;
	char target;

	if (!original || !dup)
		return (-1);
	target = dup[focused];
	if ((target == original[size - 1]))
			return (0);
	index = 0;
	while ((original[index]) && (original[index] != target))
		index++;
	if ((original[index]) && (original[index] == target))
	{
		dup[focused] = original[index + 1];
		return (1);
	}
	// write(1, "ue? funcao increment_letter agindo estranho\n", 44);
	return (1);
}

int	check_n_swap_right(char *dup, int focused, char temp)
{
	char target;
	int	index;

	if (!dup || !dup[focused] || !temp)
		return (0);
	index = focused + 1;
	target = dup[focused];
	while (dup[index])
	{
		if (dup[index] == target)
		{
			dup[index] = temp;
			return (1);
		}
		index++;
	}
	return (0);
}

int	order_right_letters(char *dup, int focused)
{
	char temp;
	int	index;

	if (!dup || !dup[focused])
		return (0);
	index = focused + 1;
	while (dup[index])
	{
		if ((dup[index + 1] != '\0') && (dup[index] > dup[index + 1]))
		{
			temp = dup[index];
			dup[index] = dup[index + 1];
			dup[index + 1] = temp;
			index = focused + 1;
		}
		else
			index++;
	}
	return (1);
}

int do_main_loop(char *original, char *dup, int size)
{
	int	focused;
	char temp;
	int	left;
	int	result;

	if (!original || !dup || !size)
		return (0);
	focused = size - 3;
	left = 1;
	result = 1;
	while (focused >= 0)
	{
		do_last_double(dup, size);
		temp = dup[focused];
		left = 1;
		while ((focused >= 0) && (left == 1))
		{
			result = increment_letter(focused, original, dup, size);
			if (!result)
			{
				dup[focused] = temp;
				focused--;
				if (focused < 0)
					return (1) ;
				temp = dup[focused];
			}
			else
				left = check_for_doubles_left(dup, focused);			
		}
		check_n_swap_right(dup, focused, temp);
		order_right_letters(dup, focused);
		focused = size - 3;
	}
	return (1);
}

int	order_string(char *string)
{
	int		index;
	char	temp;

	if (!string)
		return (0);
	index = 0;
	while (string[index])
	{
		if ((string[index + 1]) && (string[index] > string[index + 1]))
		{
			temp = string[index];
			string[index] = string[index + 1];
			string[index + 1] = temp;
			index = 0;
		}
		else
			index++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_all *all;

	if (argc != 2)
		return (1);
	all = init_structure();
	if (!all)
		return (1);
	fill_struct(all, argv);
	// order_string(all->dup);

// //--------do_last_double---------------
// 	char *string = string_dup(all, argv[1], all->size);
// 	printf("dup: %s\n\n", string);

// 	int size = stringlenght(string);
// 	printf("%d\n\n", size);
	
// 	do_last_double(string, size);
// //-------------------------------------

// //---------increment_letter---------------
// 	int	result = 0;
// 	printf("before:\n%s\n\n", all->dup);
// 	result = increment_letter(2, all->original, all->dup, all->size);
// 	printf("%d\n\n", result);
// 	printf("after:\n%s\n\n", all->dup);
// 	exit (1);
// //----------------------------------------

	// printf("size: %d\n\noriginal: %s\ndup: %s\n", all->size, all->original, all->dup);
	// do_last_double(all->dup, all->size);
	// exit (1);
	do_main_loop(all->original, all->dup, all->size);
	end_structure(all, 0);
	write(1, "banan\n", 6);
}
