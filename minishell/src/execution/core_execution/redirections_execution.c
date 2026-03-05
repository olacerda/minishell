/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_execution.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 07:54:47 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/04 22:24:45 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core_execution.h>

int	exec_heredoc(char *end_marker, int fd)
{
	char	*line;
	int		size;
	int result = 0;

	if (!end_marker || fd == -1)
		return (0);
	line = NULL;
	size = 0;
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break;
		result = string_compare(line, end_marker);
		if (result == 0)
		{
			free(line);
			break;
		}
		size = string_lenght(line);
		write(fd, line, size);
		free(line);
	}
	return (1);
}

int	exec_all_heredocs(t_all *all)
{
	t_cmd	*node;
	t_redir *redirection;
	int			node_nbr;
	int			redir_nbr;

	if (!all)
		return (0);
	node = all->head;
	node_nbr = 1;
	redir_nbr = 1;
	while (node != NULL)
	{
		redirection = node->redir;
		while (redirection != NULL)
		{
			if (redirection->type == REDIR_HEREDOC)
			{
				redir_heredoc(all->fds->redir, 1, redirection);
				if (node_nbr == all->heredoc_last_node && redir_nbr == all->last_heredoc_redir_node)
				{
					redir_heredoc(all->fds->redir, 2, redirection);
					restore_original_fds(all->fds);
					return (1);
				}
			}
			redirection = redirection->next;
			redir_nbr++;
		}
		node = node->next;
		node_nbr++;
	}
	return (0);
}

int	sync_redir_n_pipe(t_cmd *node, t_redir *redir, int *red_fd, int *pp_fd)
{
	if (!node || !red_fd || !pp_fd || !redir)
		return (0);
	if ((node->next != NULL) && (redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND))
		red_fd[1] = pp_fd[1];
	if ((pp_fd[0] != -1) && (redir->type == REDIR_HEREDOC || redir->type == REDIR_INPUT))
		red_fd[0] = pp_fd[0];
	return (1);
}

int	exec_redirections(t_cmd *node, int redir_fds[2], int pipe_fds[2])
{
	t_redir	*redir;
	int	result;
	
	if (!node || !pipe_fds || !redir_fds)
		return (0);
	redir = node->redir;
	result = 0;
	while (redir != NULL)
	{
		sync_redir_n_pipe(node, redir, redir_fds, pipe_fds);
		if (redir->type == REDIR_OUTPUT)
			result = redir_out(redir, redir_fds);
		else if (redir->type == REDIR_INPUT)
			result = redir_in(redir, redir_fds);
		else if (redir->type == REDIR_APPEND)
			result = redir_append(redir, redir_fds);
		else if (redir->type == REDIR_HEREDOC)
			result = redir_heredoc(redir_fds, 3, redir);
		if (result != true)
			return (0);
		redir = redir->next;
	}
	return (1);
}