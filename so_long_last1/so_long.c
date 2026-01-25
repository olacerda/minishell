/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:04:33 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/21 02:01:39 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "modules/data/data.h"
#include "modules/core_game/core_game.h"
#include "modules/parsing/parsing.h"

int	main(int argc, char *argv[])
{
	t_all	*all;

	if (argc != 2)
	{
		write(2, "Error\nIncorret amount of arguments!\n", 36);
		return (1);
	}
	all = malloc(sizeof(t_all));
	if (!all)
	{
		write(2, "Error\nFailed struct \"ALL\" allocation\n", 37);
		return (1);
	}
	init_structures(all);
	general_settings(all);
	if (!(parcing(argv[1], all)))
	{
		write(2, "Error\nFailed due to wrong parsing\n\n\n\n", 37);
		end_game(all);
	}
	game_initializer(all);
	return (0);
}
