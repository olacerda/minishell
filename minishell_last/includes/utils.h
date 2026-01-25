/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:46:06 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/19 18:41:34 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <minishell.h>

int		clear_buffer(char *string, int size);
int		string_lenght(char *string);
char 	*string_copy(char *string);
int		string_compare(char *str1, char *str2);
int		jump_words(int	quantity, char *string, int *index);
char 	*get_next_line(int fd);
char 	*liner(t_gnl *gnl, int *total_end, char **line);

#endif