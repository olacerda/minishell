/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_array_assign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 06:30:26 by olacerda          #+#    #+#             */
/*   Updated: 2026/02/26 06:36:45 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	char	**simbols;

	simbols = (char *[]){".", "..", "-", "~", "/", NULL};
	int	line = 0;
	while (simbols[line])
		printf("%s\n", simbols[line++]);
}