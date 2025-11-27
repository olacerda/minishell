/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 09:05:08 by olacerda          #+#    #+#             */
/*   Updated: 2025/11/01 11:50:10 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef N_QUEENS_H
# define N_QUEENS_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_positioninfo
{
	int	line;
	int	column;
}			t_positioninfo;

typedef struct s_all_structures
{
	int				size;
	char 			**map;
	int				queen_count;
	t_positioninfo *queens;
}			t_all_structures;

t_all_structures	*init_structures(int n);
// void				free_map(char **map);
void				end_all(t_all_structures *all);
char 				**create_map(t_all_structures *all);
void				clean_buffer(char *string, int size);
void				n_queens(t_all_structures *all);

void				print_map(t_all_structures *all);
void				print_map2(t_all_structures *all);

int					change_queen_range(char **map, int line, int column, char element);
// int					change_queen_range(char **map, int line, int column, int size, char element);
// int					fill_diagonal_range(char **map, int line, int column, int size, char element);
void				rebuild_current_map(t_all_structures *all);
int					fill_queen(t_all_structures *all, char **map, int line, int column);
int					clean_queen(t_all_structures *all, int *line, int *column);
int					check_if_line_have_queen(char **map, int line);
void				write_map_test(char **map);

int					ascii_to_int(char *string);
// void				put_string(char *string);


#endif