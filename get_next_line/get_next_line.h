/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:01:33 by olacerda          #+#    #+#             */
/*   Updated: 2025/12/18 15:10:28 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif
# ifndef BF
#  define BF BUFFER_SIZE
# endif
# define MAX 4000000

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/select.h>

typedef struct s_g
{
	char	*line;
	int		idx;
	int		st; 
	int		end;
	char	*new;
	int		allend;
	int		rb;
	char	buff[BUFFER_SIZE];
}	t_g;

typedef struct s_w
{
	char	*line;
	int		idx;
	int		st; 
	int		end;
	char	*new;
	int		tend;
} t_w;

typedef struct s_z
{
	char	*s;
	int		idx;
} t_z;


char	*get_next_line(int fd);

#endif
