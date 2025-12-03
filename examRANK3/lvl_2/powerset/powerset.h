/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 22:50:50 by olacerda          #+#    #+#             */
/*   Updated: 2025/12/03 02:56:24 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef POWERSET_H
# define POWERSET_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

void	print_number(int number);
int		*create_dup(int size);
int		*create_array(char *argv[], int argc, int size);

int		add_number(int *dup, int *array, int size, int *pos, int *focused);
int		increment_number(int *dup, int *focused, int *array, int size, int *pos);
int		print_array(int *array, int size);
int		remove_number(int *dup, int *focused);
int		check_result(int *array, int target, int focused);

#endif