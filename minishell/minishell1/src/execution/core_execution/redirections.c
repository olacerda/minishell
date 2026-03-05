/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:22:13 by otlacerd          #+#    #+#             */
/*   Updated: 2026/03/02 12:14:58 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core_execution.h>

int	save_original_fds(int true_fds[2])
{
	// dprintf(true_fds[1], "save_original_fds antes protecao\n\n");
	if (!true_fds)
		return (0);
	// dprintf(true_fds[1], "save_original_fds depois protecao\n\n");
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
		return (perror(redir->redir_arg), 0);
	dup2(fd, fds[0]);
	close(fd);
	return (1);
}

int	redir_out(t_redirection *redir, int fds[2], t_minishellinfo *all)
{
	int	fd;

	if (!redir || !fds)
		return (-1);
	(void)all;
	fd = open (redir->redir_arg, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return (perror(redir->redir_arg), 0);
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
		return (perror(redir->redir_arg), 0);
	dup2(fd, fds[1]);
	close(fd);
	return (1);
}

int	redir_heredoc(int fds[2], int flag, t_minishellinfo *all, t_redirection *redir)
{
	static int	fd;
 
	if (!fds || !all || !redir)
		return (-1);
	(void)all;
	if (flag == 1)
	{
		fd = open("/tmp/minishell_std_storage", O_RDWR | O_CREAT | O_TRUNC, 0600);
		if (fd < 0)
			return (0);
		execute_heredoc(redir->redir_arg, fd);
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
			return (perror("/tmp/stdout_storage"), 0);
		dup2(fd, fds[0]);
		close(fd);
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
					restore_original_fds(all);
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
