/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:46:06 by otlacerd          #+#    #+#             */
/*   Updated: 2026/03/04 21:59:16 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <minishell.h>

//-allocation.c ----------------------------------------------------------------
char 	*string_duplicate(char *string);
void	*re_allocker(void *pointer, long size, long new_size, long type_size);
char	**split_line(char *string);
int		free_array_string(char **array, int size);

//-char.c ----------------------------------------------------------------------
int		is_alphanumerical_or_underline(char xar);
int		is_numerical(char xar);

//-conversion.c ----------------------------------------------------------------
int		ascii_to_int(char *string);
char	*int_to_ascii(int nbr);

//-error.c ---------------------------------------------------------------------
void	put_error(char *problem);
void	put_comand_error(char *comand, char *problem);

//-get_next_line.c -------------------------------------------------------------
char 	*get_next_line(int fd);

//-string_advanced.c -----------------------------------------------------------
int		string_compare(char *str1, char *str2);
int		string_cat(char *string1, int size, char *string2);
int		string_jump_words(int	quantity, char *string, int *index);
int		string_swap(char **str1, char **str2);
int		array_string_lenght(char **args);

//-string_basic.c --------------------------------------------------------------
int		string_zero(char *string, int size);
int		string_print(char *string);
int		string_lenght(char *string);
int		string_copy(char *str1, char *str2);
int		string_have_equal(char *string);

#endif