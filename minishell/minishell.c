/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 02:20:46 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/28 12:52:04 by olacerda         ###   ########.fr       */
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
	t_comand		*node;
	char 			**args;
	char 			*line;
	int				pid;
	
	all = init_structures();
	if (!all)
		return (1);
	line = NULL;
	pid = getpid();
	all->father_pid = pid;
	all->my_env->envp = NULL;
	while (1)
	{		
		fill_structures(all, argc, argv, envp);
		line = readline("minishell> ");
		if (!line)
			break ;
		args = create_args(line);
		all->head = create_comand_list(args, all);
		create_buffer_children_pids(&all->children_pids, all->node_count);
		node = all->head;
		all->node_number = 0;
		execute_all_heredocs(all);
		execute_comands(all, node, argv, envp);
		if (all->children_pids)
			free(all->children_pids);
		restore_original_fds(all, 1);
		if (all->here_doc_fd != -1)
			close(all->here_doc_fd);
		free(line);
	}
	return (0);
}
