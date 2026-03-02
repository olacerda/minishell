/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 02:20:46 by otlacerd          #+#    #+#             */
/*   Updated: 2026/03/01 18:11:34 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <core_execution.h>
#include <data.h>
#include <utils.h>
#include <built-ins.h>

int	main(int argc, char *argv[], char **envp)
{
	t_minishellinfo *all;
	char 			**splitted;
	char 			*line;
	
	all = init_structures();
	if (!all)
		return (1);
	line = NULL;
	fill_structures(all, argc, argv, envp);
	while (1)
	{
		// dprintf(2, "\n\nLoopando\n\n");
		fill_structs_on_loop(all);
		line = readline("minishell> ");
		if (!line)
			break ;
		else if (line && *line)
			add_history(line);
		splitted = split_line(line);
		all->head = create_linked_list(splitted, all);
		create_children_pids_buffer(&all->children_pids, all->node_count);
		execute_all_heredocs(all);
		execute_comands(all, all->head, argv, envp);
		// restore_original_fds(all);
		end_structures(all, 0);
		free(line);
		// dprintf(2, "finale\n");
	}
	// end_structures(all, 1);
	rl_clear_history();
	return (0);
}
