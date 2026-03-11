/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:22:13 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/28 11:56:40 by olacerda         ###   ########.fr       */
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
		return (0);
	if (flag == 1)
	{
		fd = open("/tmp/stdout_storage", O_RDWR | O_CREAT | O_TRUNC, 0600);
		if (fd < 0)
			return (0);
		execute_heredoc(redir->redir_arg, fd);
		close(fd);
	}
	if (flag == 2)
	{
		fd = open("/tmp/stdout_storage", O_RDONLY);
		all->here_doc_fd = dup(fd);
		close(fd);
	}
	if (flag == 3)
	{
		dup2(all->here_doc_fd, fds[0]);
		close(all->here_doc_fd);
	}
	return (1);
}

int	execute_heredoc(char *end_marker, int fd)
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

int	execute_all_heredocs(t_minishellinfo *all)
{
	t_comand	*node;
	t_redirection *redirection;
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
				redir_heredoc(all->redir_fds, 1, all, redirection);
				if (node_nbr == all->heredoc_last_node && redir_nbr == all->last_heredoc_redir_node)
				{
					redir_heredoc(all->redir_fds, 2, all, redirection);
					restore_original_fds(all, 0);
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

int	restore_original_fds(t_minishellinfo *all, int flag)
{
	if (!all)
		return (0);
	all->redir_fds[0] = STDIN_FILENO;
	all->redir_fds[1] = STDOUT_FILENO;
	all->fd[1] = -1;
	all->fd[0] = -1;
	dup2(all->true_fds[0], all->redir_fds[0]);
	dup2(all->true_fds[1], all->redir_fds[1]);
	// dup2(all->true_fds[0], all->previous_fd_0);
	// dup2(all->true_fds[0], all->redir_fds[0]);
	// dup2(all->true_fds[1], all->redir_fds[1]);
	if (flag == 1)
	{
		close(all->true_fds[1]);
		close(all->true_fds[0]);
	}
	return (1);
}