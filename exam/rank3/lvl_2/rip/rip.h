/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 08:39:54 by olacerda          #+#    #+#             */
/*   Updated: 2025/12/17 06:05:42 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RIP_H
# define RIP_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int					string_lenght(char *string);

int					calculate_gap(char *string);
long unsigned int	calculate_permutator(int gap);
int					calculate_number_size(long unsigned int number);
int					calculate_final_number(int number, int strlen);


int					remove_parenteses(char *string, long unsigned int permutator);
int					check_result(char *string);
int					refresh_string(char *string);
int					print_string(char *string);
int					permutate_once(long unsigned int *permutator, int gap, int strlen);

int					do_main_loop(char *string, long unsigned int permutator, int limit, int size, int strlen);



#endif