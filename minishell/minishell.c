/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 02:20:46 by otlacerd          #+#    #+#             */
/*   Updated: 2026/03/07 17:24:08 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <core_execution.h>
#include <data.h>
#include <utils.h>
#include <built-ins.h>

int	main(int argc, char *argv[], char **envp)
{
	t_all	*all;

	all = init_structures();
	if (!all)
		return (1);
	fill_structures(all, argc, argv, envp);
	signals(false);
	while (1)
	{
		fill_structs_on_loop(all);
		if (get_line(&(all->line)) == false)
			break ;
		all->splitted = split_line(all->line);
		all->head = create_linked_list(all->splitted, all);
		create_children_pids_buffer(&all->children_pids, all->lst_size);
		exec_all_heredocs(all);
		exec_comands(all, all->head, all->my_env->envp);
		end_structures(all, 0, 0);
		free(all->line);
	}
	rl_clear_history();
	end_structures(all, 1, 0);
	return (0);
}
