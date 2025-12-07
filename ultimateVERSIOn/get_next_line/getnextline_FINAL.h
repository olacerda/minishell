/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline_FINAL.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:01:33 by olacerda          #+#    #+#             */
/*   Updated: 2025/12/07 04:59:36 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETNEXTLINE_FINAL_H
# define GETNEXTLINE_FINAL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
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
	char	*nln;
	int		index;
	int		garbage;
	int		allend;
	int		end;
	int		start;
	int		rbts;
	char	buff[BUFFER_SIZE];
	char	*garbage2;
}			t_g;

typedef struct s_w
{
	char	*line;
	char	*nln;
	int		index;
	int		garbage;
	int		allend;
	int		end;
}			t_w;

typedef struct s_z
{
	char	*line;
	char	*nln;
	int		index;
	int		garbage;
}			t_z;

char	*get_next_line(int fd);

#endif