/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_test.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 07:16:04 by olacerda          #+#    #+#             */
/*   Updated: 2026/02/27 07:39:37 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_TEST_H
# define HEADER_TEST_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum s_test
{
	zero,
	um,
	dois,
	tres
}			t_test;

int	soma(int a, int b);

#endif