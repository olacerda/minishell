/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:43:11 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/21 09:21:10 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <data.h>

void	put_error(char *problem)
{
	int	index;

	index = 0;
	if (!problem)
		return ;
	while (problem[index])
		index++;
	write(2, problem, index);
}

t_minishellinfo *init_structures(void)
{
	t_minishellinfo *all;

	all = malloc(sizeof(t_minishellinfo));
	if (!all)
	{
		put_error("Error\nFailed to allocate struct 'ALL'\n");
		end_structures(all);
		return (NULL);
	}
	*all = (t_minishellinfo){0};
	all->prefx = malloc(sizeof(t_prefix));
	if (!all->prefx)
	{
		put_error("Error\nFaile to allocate struct 'prefx'\n");
		end_structures(all);
		return (NULL);
	}
	all->states = malloc(sizeof(t_states));
	if (!all->states)
	{
		put_error("Error\nFailed allocation in init_structures -> all.states\n");
		end_structures(all);
		return (NULL);
	}
	return (all);
}

void	fill_structures(t_minishellinfo *all, int argc, char **argv, char **envp)
{
	if (!all || !argc || !argv || !envp)
		return ;
	all->argv = argv;
	all->envp = envp;
	all->argc = argc;
	if (!get_all_prefixs(all->prefx))
	{
		end_structures(all);
		exit (1);
	}
	all->head = NULL;
	all->comand = NULL;
	if (all->states == NULL)
	*all->states = (t_states){0};
	all->node_number = 0;
	all->node_count = 0;
	all->father_pid = -1;
	all->children_pids = NULL;
	all->fd[0] = 0;
	all->fd[1] = 0;
	save_original_fds(all->true_fds);
	all->redir_fds[0] = STDIN_FILENO;
	all->redir_fds[1] = STDOUT_FILENO;
	all->previous_fd_0 = -1;
	all->last_heredoc_node = 0;
	all->last_heredoc_node = 0;
	all->here_doc_fd = -1;
}

void	end_structures(t_minishellinfo *all)
{
	if (!all)
		return ;
	if (all->prefx)
		free(all->prefx);
	if (all)
		free(all);
}
