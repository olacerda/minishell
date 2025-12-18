/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 09:04:49 by olacerda          #+#    #+#             */
/*   Updated: 2025/12/18 07:48:43 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_queens.h"

void	put_number(long number)
{
	if (number < 0)
	{
		write(1, "-", 1);
		number = -number;
	}
	if (number > 9)
		put_number(number / 10);
	write(1, &(char){number % 10 + 48}, 1);
}

void	print_map(t_all_structures *all)
{
	int	index;

	index = 0;
	while (index < all->size)
	{
		put_number(all->queens[index].column);
		if (index < (all->size - 1))
			write(1, " ", 1);
		index++;
	}
	write(1, "\n", 1);
}

void	clean_buffer(char *string, int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		string[index] = '0';
		index++;
	}
	string[index] = '\0';
}

char **create_map(t_all_structures *all)
{
	char **map;
	int	line;

	line = 0;
	map = malloc((all->size + 1) * sizeof(char *));
	if (!map)
	{
		write(2, "Failled to allocate map\n", 24);
		end_all(all);
		return (NULL);
	}
	while (line < all->size)
	{
		map[line] = malloc((all->size + 1) * sizeof(char));
		if (!map[line])
		{
			write(2, "Failed to allocate map[line]\n", 28);
			end_all(all);
			return (NULL);
		}
		clean_buffer(map[line], (all->size));
		line++;
	}
	map[line] = NULL;
	return (map);
}

void	end_all(t_all_structures *all)
{
	int	line;

	line = 0;
	if (!all)
		return ;
	if (all->queens)
		free(all->queens);
	if (all->map)
	{
		while (all->map[line] != NULL)
		{
			free(all->map[line]);
			line++;
		}
		free(all->map[line]);
		free(all->map);
	}
	free(all);
	exit (1);
}

t_all_structures	*init_structures(int size)
{
	int	index;

	index = 0;
	t_positioninfo *queens;
	t_all_structures *all;

	all = malloc(sizeof(t_all_structures));
	if (!all)
		return (write(2, "Failed to alocate map\n", 22), exit(1), NULL);
	*all = (t_all_structures){size, 0, 0, 0};
	queens = malloc(size * sizeof(t_positioninfo));
	if (!queens)
	{
		write(2, "Failed to alocate queens\n", 25);
		end_all(all);
	}
	while (index < size)
	{
		queens[index] = (t_positioninfo){0, 0};
		index++;
	}
	all->queens = queens;
	return (all);
}

int	ascii_to_int(char *string)
{
	long result;
	int	index;
	int	minus;

	index = 0;
	minus = 0;
	result = 0;
	while ((string[index] >= 9 && string[index] <= 13) || string[index] == 32)
		index++;
	if (string[index] == '+' || string[index] == '-')
		if (string[index++] == '-')
			minus = 1;
	while (string[index] >= '0' && string[index] <= '9')
	{
		result = (result * 10) + (string[index] - 48);
		index++;
	}
	if (minus == 1)
		result = -result;
	if ((result <= (1 << 31)) || result >= ((1L << 31) - 1))
	{
		write(2, "Error\narv[1] causes int_overflow\n", 33);
		exit (1);
	}
	return (result);
}

int	change_queen_range(char **map, int line, int column, char element)
{
	int line_tmp;
	int column_tmp;

	line_tmp = 0;
	column_tmp = 0;
	while (map[line][column_tmp] != '\0')
	{
		if (map[line][column_tmp] == 'Q')
		{
			if (element == 'A')
				return (0);
			else
				break;
		}
		map[line][column_tmp] = element;
		column_tmp++;
	}
	column_tmp = 0;
	while (map[line_tmp] != NULL)
	{
		if (map[line_tmp][column] == 'Q')
		{
			if (element == 'A')
				return (0);
			else
				break;
		}
		map[line_tmp][column] = element;
		line_tmp++;
	}
	line_tmp = line;
	column_tmp = column;
	while ((line_tmp >= 0) && (column_tmp >= 0))
	{
		if (map[line_tmp][column_tmp] == 'Q')
		{
			if (element == 'A')
				return (0);
			else
				break;
		}
		map[line_tmp][column_tmp] = element;
		line_tmp--;
		column_tmp--;
	}
	line_tmp = line;
	column_tmp = column;
	while ((map[line_tmp] != NULL) && (column_tmp >= 0))
	{
		if (map[line_tmp][column_tmp] == 'Q')
		{
			if (element == 'A')
				return (0);
			else
				break;
		}
		map[line_tmp][column_tmp] = element;
		line_tmp++;
		column_tmp--;
	}
	line_tmp = line;
	column_tmp = column;
	while ((line_tmp >= 0) && (map[line_tmp][column_tmp] != '\0'))
	{
		if (map[line_tmp][column_tmp] == 'Q')
		{
			if (element == 'A')
				return (0);
			else
				break;
		}
		map[line_tmp][column_tmp] = element;
		line_tmp--;
		column_tmp++;
	}
	line_tmp = line;
	column_tmp = column;
	while ((map[line_tmp] != NULL) && (map[line_tmp][column_tmp] != '\0'))
	{
		if (map[line_tmp][column_tmp] == 'Q')
		{
			if (element == 'A')
				return (0);
			else
				break;
		}
		map[line_tmp][column_tmp] = element;
		line_tmp++;
		column_tmp++;
	}
	return (1);
}

void	rebuild_current_map(t_all_structures *all)
{
	int	line;
	int	column;

	line = 0;
	column = 0;
	while (all->map[line] != NULL)
	{
		column = 0;
		while (all->map[line][column] != '\0')
		{
			if (all->map[line][column] == 'Q')
			{
				all->map[line][column] = '0';
				change_queen_range(all->map, line, column, 'A');
				all->map[line][column] = 'Q';
			}
			column++;
		}
		line++;
	}
}

int	add_queen(t_all_structures *all, char **map, int line, int column)
{
	if (!all || !map)
		return (-1);
	if (!change_queen_range(map, line, column, 'A'))
	{
		change_queen_range(map, line, column, '0');
		return (0);
	}
	all->queens[all->queen_count].column = column;
	all->queens[all->queen_count].line = line;
	map[line][column] = 'Q';
	all->queen_count++;
	return (1);
}

int	remove_queen(t_all_structures *all, int *line, int *column)
{
	if (!all || !line || !column)
		return (-1);
	all->queen_count--;
	if (all->queen_count < 0)
		return (0);
	all->map[all->queens[all->queen_count].line][all->queens[all->queen_count].column] = '0';
	change_queen_range(all->map, all->queens[all->queen_count].line, all->queens[all->queen_count].column, '0');
	if (all->queen_count > 0)
		rebuild_current_map(all);
	(*line) = all->queens[all->queen_count].line;
	(*column) = all->queens[all->queen_count].column + 1;
	all->queens[all->queen_count].column = 0;
	all->queens[all->queen_count].line = 0;
	if ((*line) == 0 && (all->map[*line][*column] == '\0'))
		return (0);
	return (1);
}

int	check_queen_in_line(char **map, int line)
{
	int	column;

	column = 0;
	while (map[line][column] != '\0')
	{
		if (map[line][column] == 'Q')
			return (1);
		column++;
	}
	return (0);
}

void	n_queens(t_all_structures *all)
{
	char **map;
	int	line;
	int	column;
	int	queen_in_line;

	line = 0;
	column = 0;
	map = all->map;
	queen_in_line = 0;
	while (map[line] != NULL)
	{
		if (queen_in_line)
		{
			column = 0;
			queen_in_line = 0;
		}
		while (map[line][column] != '\0')
		{
			if (map[line][column] != 'A')
			{
				add_queen(all, map, line, column);
				if (all->queen_count == all->size)
				{
					print_map(all);
					if (!remove_queen(all, &line, &column))
						return ;
				}
				else
					break ;
			}
			column++;
		}
		queen_in_line = check_queen_in_line(map, line);
		if (!queen_in_line)
		{
			if (!remove_queen(all, &line, &column))
				return ;
		}
		else
			line++;
	}
}

int	write_map_test(char **map)
{
	int	line;
	int column;

	if (!map)
		return (0);
	line = 0;
	column = 0;
	while (map[line] != NULL)
	{
		column = 0;
		while (map[line][column] != '\0')
		{
			write(1, &map[line][column], 1);
			column++;
		}
		write(1, "\n", 1);
		line++;
	}
	write(1, "\n\n\n", 3);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_all_structures *all;
	int	size;

	if (argc != 2)
	{
		write(2, "Error\nWrong number of arguments on standard input\n", 50);
		return (1);
	}
	size = ascii_to_int(argv[1]);
	all = init_structures(size);
	all->map = create_map(all);
	if (!all->map)
		return (1);
	n_queens(all);
	end_all(all);
}

// int	main(void)
// {
// 	char **map;
// 	int line = 0;
// 	int column = 0;
// 	int size = 3;

// 	map = malloc((size + 1) * sizeof(char *));
// 	if (!map)	
// 	{
// 		return (1);
// 	}
// 	while (line < size)
// 	{
// 		map[line] = malloc((size + 1) * sizeof(char));
// 		if (!map[line])
// 		{
// 			return (1);
// 		}
// 		clean_buffer(map[line], size);
// 		line++;
// 	}
// 	map[0][0] = '0';
// 	map[0][1] = '0';
// 	map[0][2] = '0';
// 	map[0][3] = 0;
	
// 	map[1][0] = '0';
// 	map[1][1] = '0';
// 	map[1][2] = '0';
// 	map[1][3] = 0;
	
// 	map[2][0] = '0';
// 	map[2][1] = '0';
// 	map[2][2] = '0';
// 	map[2][3] = 0;
	
// 	map[3] = NULL;
// 	write_map_test(map);
// 	line = 0;
// 	column = 0;
// 	if (!change_queen_range(map, line, column, 'A'))
// 	{
// 		write_map_test(map);
// 		change_queen_range(map, line, column, '0');
// 		write_map_test(map);
// 	}
// 	else
// 		map[line][column] = 'Q';
// 	// write(1, "teste\n", 6);
// 	write_map_test(map);
// }