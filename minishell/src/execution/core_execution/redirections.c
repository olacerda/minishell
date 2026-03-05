/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:22:13 by otlacerd          #+#    #+#             */
/*   Updated: 2026/03/04 23:43:02 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core_execution.h>

int	redir_in(t_redir *redir, int fds[2])
{
	int	fd;

	if (!redir || !fds)
		return (-1);
	fd = open(redir->redir_arg, O_RDONLY);
	if (fd < 0)
		return (perror(redir->redir_arg), 0);
	dup2(fd, fds[0]);
	close(fd);
	return (1);
}

int	redir_out(t_redir *redir, int fds[2])
{
	int	fd;

	if (!redir || !fds)
		return (-1);
	fd = open (redir->redir_arg, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return (perror(redir->redir_arg), 0);
	dup2(fd, fds[1]);
	close(fd);
	return (1);
}

int	redir_append(t_redir *redir, int fds[2])
{
	int	fd;

	if (!redir || !fds)
		return (-1);
	fd = open (redir->redir_arg, O_WRONLY | O_CREAT | O_APPEND, 0600);
	if (fd < 0)
		return (perror(redir->redir_arg), 0);
	dup2(fd, fds[1]);
	close(fd);
	return (1);
}

int	redir_heredoc(int fds[2], int flag, t_redir *redir)
{
	static int	fd;
 
	if (!fds || !redir)
		return (-1);
	if (flag == 1)
	{
		fd = open("/tmp/minishell_std_storage", O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (0);
		exec_heredoc(redir->redir_arg, fd);
		close(fd);
	}
	if (flag == 2)
	{
		// fd = open("/tmp/stdout_storage", O_RDONLY);
		// all->here_doc_fd = dup(fd);
		// close(fd);
	}
	if (flag == 3)
	{
		fd = open("/tmp/minishell_std_storage", O_RDONLY);
		if (fd < 0)
			return (perror("/tmp/minishell_std_storage"), 0);
		dup2(fd, fds[0]);
		close(fd);
	}
	return (1);
}
