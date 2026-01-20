/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:22:13 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/20 00:50:33 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core_execution.h>

int	save_original_fds(int true_fds[2])
{
	if (!true_fds)
		return (0);
	true_fds[1] = dup(STDOUT_FILENO);
	true_fds[0] = dup(STDIN_FILENO);
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

int	redir_out(t_redirection *redir, int fds[2])
{
	int	fd;

	if (!redir || !fds)
		return (-1);
	fd = open (redir->redir_arg, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return (-1);
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

int	execute_last_heredoc(t_minishellinfo *all)
{
	t_comand	*node;
	t_redirection *redirection;
	int			comand;
	int			redir;
	int			check;

	if (!all || (!(all->last_heredoc_node) && !(all->last_heredoc_redir_node)))
		return (0);
	comand = 0;
	redir = 0;
	node = all->head;
	while ((comand++ < (all->last_heredoc_node - 1)) && (node != NULL))
		node = node->next;
	redirection = node->redir;
	while ((redir++ < (all->last_heredoc_redir_node - 1)) && (redirection != NULL))
		redirection = redirection->next;
	if (redirection->type == REDIR_HEREDOC)
	{
		check = execute_heredoc(redirection->redir_arg, all->redir_fds);
		if (check == 1)
		{
			close(all->redir_fds[1]);
			restore_original_fds(all, 0);
		}
	}
	return (1);
}

int	execute_heredoc(char *end_marker, int fds[2])
{
	char	*line;
	int		size;

	if (!end_marker)
		return (0);
	line = NULL;
	size = 0;
	redir_heredoc(fds);
	int result = 0;
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

int	redir_heredoc(int fds[2])
{
	int	fd;

	if (!fds)
		return (0);
	fd = open("/tmp/stdout_storage", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return (0);
	dup2(fd, fds[1]);
	close(fd);
	return (1);
}

int	restore_original_fds(t_minishellinfo *all, int flag)
{
	if (!all)
		return (0);
	dup2(all->true_fds[0], STDIN_FILENO);
	dup2(all->true_fds[1], STDOUT_FILENO);
	if (flag == 1)
	{
		close(all->true_fds[1]);
		close(all->true_fds[0]);
	}
	return (1);
}