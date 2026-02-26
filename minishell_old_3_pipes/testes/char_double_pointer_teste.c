/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_double_pointer_teste.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 00:18:45 by otlacerd          #+#    #+#             */
/*   Updated: 2025/11/15 00:22:33 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(void)
{
	char **references;
	int line = 0;
	// int index = 0;
	references = (char *[3]){"ls", "wc", NULL};
	while (references[line] != NULL)
	{
		printf("%s\n", references[line]);
		line++;
	}
}