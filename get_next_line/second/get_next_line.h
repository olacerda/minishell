/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:01:33 by olacerda          #+#    #+#             */
/*   Updated: 2026/01/21 03:34:44 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 7
# endif
# ifndef B
#  define B BUFFER_SIZE	
# endif
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/select.h>

typedef struct s_g
{
	char	*line;
	int		index;
	int		*garbage;
	char	*l2;
	int		allend;
	int		end;
	int		st;
	int		rb;
	char	buff[BUFFER_SIZE + 2];
}			t_g;

typedef struct s_w
{
	char	*line;
	int		index;
	int		garbage;
	char	*l2;
	int		allend;
	int		end;
}			t_w;

typedef struct s_z
{
	char	*s;
	int		index;
}			t_z;

char	*get_next_line(int fd);

#endif