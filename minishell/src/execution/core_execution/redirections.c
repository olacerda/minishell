/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:22:13 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/22 19:44:55 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core_execution.h>

int	save_original_fds(int true_fds[2])
{
	if (!true_fds)
		return (0);
	true_fds[0] = dup(STDIN_FILENO);
	true_fds[1] = dup(STDOUT_FILENO);
	return (1);
}

int	copy_fds(int fds1[2], int fds2[2])
{
	if (!fds1 || !fds2)
		return (0);
	fds1[0] = fds2[0];
	fds1[1] = fds2[1];
	return (1);
}

int	redir_in(t_redirection *redir, int fds[2])
{
	int	fd;

	if (!redir || !fds)
		return (-1);
	fd = open(redir->redir_arg, O_RDONLY);
	if (fd < 0)
		return (-1);
	dup2(fd, fds[0]);
	close(fd);
	return (1);
}

int	redir_out(t_redirection *redir, int fds[2], t_minishellinfo *all)
{
	int	fd;

	if (!redir || !fds)
		return (-1);
	dprintf(all->true_fds[1], "redir_out\n");
	fd = open (redir->redir_arg, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		dprintf(all->true_fds[1], "Falhou OPEN em redir_out\n");
		return (-1);
	}
	dup2(fd, fds[1]);
	close(fd);
	return (1);
}

int	redir_append(t_redirection *redir, int fds[2])
{
	int	fd;

	if (!redir || !fds)
		return (-1);
	fd = open (redir->redir_arg, O_WRONLY | O_CREAT | O_APPEND, 0600);
	if (fd < 0)
		return (-1);
	dup2(fd, fds[1]);
	close(fd);
	return (1);
}

int	redir_heredoc(int fds[2], int flag, t_minishellinfo *all, t_redirection *redir)
{
	static int	fd;
 
	if (!fds)
	{
		return (0);
	}
	dprintf(all->true_fds[1], "redir_heredoc flag: %d\n", flag);
	if (flag == 1)
	{
		fd = open("/tmp/stdout_storage", O_RDWR | O_CREAT | O_TRUNC, 0600);
		if (fd < 0)
		{
			dprintf(all->true_fds[1], "Open Error\n");
			return (0);
		}
		dup2(fd, fds[1]);
		close(fd);
		execute_heredoc(redir->redir_arg, fds);
	}
	if (flag == 2)
	{
		fd = open("/tmp/stdout_storage", O_RDONLY);
		all->here_doc_fd = dup(fd);
		close(fd);
	}
	if (flag == 0)
	{
		fd = open("/tmp/stdout_storage", O_RDONLY);
		dup2(fd, fds[0]);
		close(fd);
	}
	return (1);
}

int	execute_heredoc(char *end_marker, int fds[2])
{
	char	*line;
	int		size;
	int result = 0;

	if (!end_marker || !fds)
	{
		return (0);
	}
	line = NULL;
	size = 0;
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break;
		result = string_compare(line, end_marker);
		if (result == 0)
		{
			free(line);
			break;
		}
		size = string_lenght(line);
		write(fds[1], line, size);
		free(line);
	}
	return (1);
}

int	execute_all_heredocs(t_minishellinfo *all)
{
	t_comand	*node;
	t_redirection *redirection;
	int			node_nbr;
	int			redir_nbr;
	int			flag;

	if (!all)
		return (0);
	node = all->head;
	node_nbr = 1;
	redir_nbr = 1;
	while (node != NULL)
	{
		dprintf(all->true_fds[1], "loopando node\n");
		redirection = node->redir;
		while (redirection != NULL)
		{
			dprintf(all->true_fds[1], "loopando redir\n");
			if (redirection->type == REDIR_HEREDOC)
			{
				dprintf(all->true_fds[1], "detectou heredoc\n");
				flag = 1;
				redir_heredoc(all->redir_fds, flag, all, redirection);
				dprintf(all->true_fds[1], "node count: %d    redir count: %d\n\n", all->last_heredoc_node, all->last_heredoc_redir_node);
				dprintf(all->true_fds[1], "node number: %d    redir number: %d\n\n", node_nbr, redir_nbr);
				if (node_nbr == all->last_heredoc_node && redir_nbr == all->last_heredoc_redir_node)
				{
					// dprintf(all->true_fds[1], "flag == 2\n\n");
					flag = 2;
					redir_heredoc(all->redir_fds, flag, all, redirection);
					return (1);
				}

			}
			redirection = redirection->next;
			redir_nbr++;
		}
		node = node->next;
		node_nbr++;
	}
	restore_original_fds(all, 0);
	return (1);
}

int	restore_original_fds(t_minishellinfo *all, int flag)
{
	if (!all)
		return (0);
	all->redir_fds[0] = STDIN_FILENO;
	all->redir_fds[1] = STDOUT_FILENO;
	dup2(all->true_fds[0], all->redir_fds[0]);
	dup2(all->true_fds[1], all->redir_fds[1]);
	// dup2(all->true_fds[0], all->redir_fds[0]);
	// dup2(all->true_fds[1], all->redir_fds[1]);
	if (flag == 1)
	{
		close(all->true_fds[1]);
		close(all->true_fds[0]);
	}
	return (1);
}