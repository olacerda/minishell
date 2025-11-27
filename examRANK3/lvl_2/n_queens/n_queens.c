/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 09:04:49 by olacerda          #+#    #+#             */
/*   Updated: 2025/11/01 14:03:19 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "n_queens.h"

// void	put_string(char *string)
// {
// 	int	index;

// 	index = 0;
// 	while (string[index] != '\0')
// 	{
// 		write(1, &string[index], 1);
// 		index++;
// 	}
// }

void	print_map2(t_all_structures *all)
{
	int	index;

	index = 0;
	while (index < all->size)
	{
		write(1, &(char){all->queens[index].column + 48}, 1);
		if (index < (all->size - 1))
			write(1, " ", 1);
		index++;
	}
}

void	print_map(t_all_structures *all)
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
				write(1, &(char){column + 48}, 1);
				if ()
				write(1, " ", 1);
				break ;
			}
			column++;
		}
		line++;
	}
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
	// printf("size: %d\n", all->size);
	// exit (1);
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
		free(all);
		write(2, "Failed to alocate queens\n", 25);
		exit(1);
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
	// write_map_test(map);
	// printf("line: %d    column_tmp: %d\n\n", line, column_tmp);
	while (map[line][column_tmp] != '\0')
	{
		// write(1, "teste\n", 6);
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
	// printf("linetmp: %d    columntmp: %d    element: %c\n\n", line_tmp, column_tmp, element);
	while ((map[line_tmp] != NULL) && (map[line_tmp][column_tmp] != '\0'))
	{
		// write(1, "oi?\n", 4);
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

// int	fill_diagonal_range(char **map, int line, int column, int size, char element)
// {
// 	int line2;
// 	int column2;

// 	if (line >= column)
// 	{
// 		line2 = line - column;
// 		column2 = 0;
// 	}
// 	else if (column >= line)
// 	{
// 		line2 = 0;
// 		column2 = column - line;
// 	}
// 	while ((map[line2] != NULL) && map[line2][column2] != '\0')
// 	{
// 		if ((map[line2][column2] == 'Q'))
// 			return (0);
// 		map[line2][column2] = element;
// 		line2++;
// 		column2++;
// 	}
// 	if (line + column >= (size - 1))
// 	{
// 		line = (size - 1);
// 		column = (line + column) - (size - 1);
// 	}
// 	else if (line + column <= (size - 1))
// 	{
// 		line = line + column;
// 		column = 0;
// 	}
// 	while ((map[line] != NULL) && (line >= 0) && map[line][column] != '\0')
// 	{
// 		if (map[line][column] == 'Q')
// 			return (0);
// 		map[line][column] = element;
// 		line--;
// 		column++;
// 	}
// 	// write(1, "teste\n", 6);
// 	return (1);
// }

// int	change_queen_range(char **map, int line, int column, int size, char element)
// {
// 	int	result;
// 	int line2;
// 	int column2;

// 	result = 0;
// 	line2 = 0;
// 	column2 = 0;
// 	while (map[line2] != NULL)
// 	{
// 		if (map[line2][column] == 'Q')
// 			return (0);
// 		map[line2][column] = element;
// 		line2++;
// 	}
// 	while (map[line][column2] != '\0')
// 	{
// 		if (map[line][column2] == 'Q')
// 			return (0);
// 		map[line][column2] = element;
// 		column2++;
// 	}
// 	if (!fill_diagonal_range(map, line, column, size, element))
// 		return (0);
// 	return (1);
// }

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
				change_queen_range(all->map, line, column, 'A');
			}
			column++;
		}
		line++;
	}
}

int	fill_queen(t_all_structures *all, char **map, int line, int column)
{
	// write(1, "teste\n", 6);
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

int	clean_queen(t_all_structures *all, int *line, int *column)
{
	all->queen_count--;
	// printf("queen count: %d\n", all->queen_count);
	if (all->queen_count < 0)
		return (0);
	all->map[all->queens[all->queen_count].line][all->queens[all->queen_count].column] = '0';
	change_queen_range(all->map, all->queens[all->queen_count].line, all->queens[all->queen_count].column, '0');
	if (all->queen_count > 0)
		rebuild_current_map(all);
	(*line) = all->queens[all->queen_count].line;
	(*column) = all->queens[all->queen_count].column + 1;
	if ((*line) == 0 && (all->map[*line][*column] == '\0'))
		return (0);
	if (all->map[*line][*column] == '\0')
	{
		*column = 0;
		*line++;
	}
	return (1);
}

t_process 
{ 
	char **arguments; // se houver;
	t_comands *next_comand; //se houver;
	t_process *next_process; //se houver;
	t_process *child_process; //se houver; 
}

int	check_if_line_have_queen(char **map, int line)
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
			// write(1, &map[line][column], 1);
			if (map[line][column] != 'A')
			{
				fill_queen(all, map, line, column);
				write_map_test(map);
				static int count = 0;
				write(1, &(char){count++ + 48}, 1);
				write(1, "\n\n", 2);
				if (all->queen_count == all->size)
				{
					print_map(all);
					if (!clean_queen(all, &line, &column))
						return ;
				}
				else
					break ;
			}
			column++;
		}
		queen_in_line = check_if_line_have_queen(map, line);
		if (!queen_in_line)
		{
			// write(1, "teste2\n", 7);
			if (!clean_queen(all, &line, &column))
				return ;
		}
		else
			line++;
		// write_map_test(map);
		write(1, "\n\n", 2);
	}
}

void	write_map_test(char **map)
{
	int	line;
	int column;

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
	write(1, "\n", 1);
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
	// printf("size: %d\n", all->size);
	// return (1);
	all->map = create_map(all);
	if (!all->map)
		return (1);
	// write_map_test(all->map);
	// return (1);
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