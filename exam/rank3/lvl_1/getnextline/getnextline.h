/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 07:04:12 by olacerda          #+#    #+#             */
/*   Updated: 2025/11/27 17:51:16 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef GETNEXTLINE_H
# define GETNEXTLINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_gnl
{
	int	start;
	int	end;
	int	readbytes;	
}		t_gnl;

char *getnextline(int fd);

#endif