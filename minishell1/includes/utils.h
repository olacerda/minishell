/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:46:06 by otlacerd          #+#    #+#             */
/*   Updated: 2026/03/02 16:37:19 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <minishell.h>

void	put_error(char *problem);

int		clear_string(char *string, int size);
int		print_string(char *string);

int		string_lenght(char *string);
char 	*string_duplicate(char *string);
int		string_compare(char *str1, char *str2);
int		string_copy(char *str1, char *str2);
int		string_cat(char *string1, int size, char *string2);

char 	*get_next_line(int fd);
char 	*liner(t_gnl *gnl, int *total_end, char **line);

int		jump_words(int	quantity, char *string, int *index);
void	*re_allocker(void *pointer, long size, long new_size, long type_size);
int		swap_strings(char **str1, char **str2);

int		is_alphabetical(char xar);
int		is_numerical(char xar);

#endif