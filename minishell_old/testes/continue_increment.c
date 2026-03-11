/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_increment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:16:54 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/03 16:18:10 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	char *string = "Isso e um teste";
	int	index = -1;

	while (string[++index])
	{
		if (index == 5)
			continue ;
		printf("%c\n", string[index]);
	}
}