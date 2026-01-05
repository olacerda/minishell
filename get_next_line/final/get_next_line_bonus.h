/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:01:33 by olacerda          #+#    #+#             */
/*   Updated: 2026/01/04 21:48:01 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
# define F fd
# ifndef B
#  define B BUFFER_SIZE
# endif
# define MAX 4000000

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/select.h>

typedef struct s_g
{
	char	*l;
	int		i;
	int		garbage;
	char	*n;
	int		a;
	int		e;
	int		s;
	int		rb;
	char	b[BUFFER_SIZE + 1];
}				t_g;

typedef struct s_w
{
	char	*line;
	int		idx;
	int		garbage;
	char	*new;
	int		allend;
	int		end;
}				t_w;

typedef struct s_z
{
	char	*s;
	int		idx;
}				t_z;

char	*get_next_line(int fd);

#endif