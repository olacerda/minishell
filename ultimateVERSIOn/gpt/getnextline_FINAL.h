/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline_FINAL.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:01:33 by olacerda          #+#    #+#             */
/*   Updated: 2025/12/07 03:26:22 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETNEXTLINE_FINAL_H
# define GETNEXTLINE_FINAL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
# ifndef MAX
#  define MAX 4000000
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
	int		start;
	int		end;
	char	*nline;
	int		allend;
	int		rbts;
	char	buff[BUFFER_SIZE + 1];
}	t_g;

typedef struct s_w
{
	char	*line;
	int		index;
	int		start;
	int		end;
	char	*nline;
	int		tend;
}			t_w;

typedef struct s_z
{
	char	*s;
	int		index;
}			t_z;

typedef union u_cast
{
	t_g	g;
	t_w	w;
	t_z	z;
}			t_cast;

char	*get_next_line(int fd);

#endif