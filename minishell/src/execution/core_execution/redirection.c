/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:22:13 by otlacerd          #+#    #+#             */
/*   Updated: 2026/03/07 15:32:54 by olacerda         ###   ########.fr       */
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

int	add_break_line(char **string)
{
	int	size;
	
	if (!string || !(*string))
		return (FAIL);
	size = string_length(*string);
	*string = re_allocker(*string, size, size + 1, sizeof(char));
	if (!(*string))
		return (0);
	*string[size] = '\n';
	*string[size + 1] = '\0';
	return (1);
}

int	redir_heredoc(t_all *all, int fds[2], int is_execution, t_redir *redir)
{
	static int	fd;
	int			pid;
 
	if (!fds || !redir)
		return (-1);
	if (is_execution == true)
	{
		fd = open(TEMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (0);
		pid = exec_heredoc(all, &(all->process_info->signal), redir->redir_arg, fd);
		close (fd);
		return (pid);
	}
	else if (is_execution == false)
	{
		fd = open(TEMP_FILE, O_RDONLY);
		if (fd < 0)
			return (perror(TEMP_FILE), 0);
		dup2(fd, fds[0]);
		close(fd);
	}
	return (true);
}
