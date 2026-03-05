/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_pointer_test.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 21:50:15 by olacerda          #+#    #+#             */
/*   Updated: 2026/02/26 21:53:13 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	char	**buffer = {"oi", "tudo", "bem", NULL};

	int	line = 0;
	while (buffer[line])
		printf("%s\n", buffer[line++]);
}