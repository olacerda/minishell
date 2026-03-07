/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 07:54:47 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/07 17:08:08 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core_execution.h>

int	exec_all_heredocs(t_all *all)
{
	t_cmd	*node;
	t_redir *redirection;
	int		readbytes;
	int		fd;

	if (!all)
		return (0);
	node = all->head;
	while (node != NULL)
	{
		redirection = node->redir;
		while (redirection != NULL)
		{
			if (redirection->type == REDIR_HEREDOC)
			{
				redir_heredoc(all, all->fds->redir, true, redirection);
				fd = open(TEMP_FILE, O_RDONLY);
				readbytes = read(fd, all->buffer, BUFFER_SIZE);
				close(fd);
				if (readbytes != 0)
				{
					realloc_appender(&all->line, "\n");
					add_heredoc_history(all->buffer, all->line, string_length(all->line));
				}
			}
			redirection = redirection->next;
		}
		node = node->next;
	}
	return (0);
}

int	exec_heredoc(t_all *all, int *signal, char *end_marker, int fd)
{
	char	*line;
	int		pid;
	int		size;
	int		stdin_backup;

	if (!end_marker || fd == -1 || !all || !signal)
		return (-1);
	all->process_info->is_heredoc = true;
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		stdin_backup = dup(STDIN_FILENO);
		line = NULL;
		while (1)
		{
			line = readline("ue> ");
			if (((line != NULL) && (string_compare(line, end_marker) == 0))
				|| ((!line) || !(*line) || (*signal == SIGINT)))
			{
				if (*signal == SIGINT)
					dup2(stdin_backup, STDIN_FILENO);
				if (line != NULL)
					free(line);
				dprintf(2, "saiu\n");
				break;
			}
			else if (line && *line)
				add_history(line);
			size = string_length(line);
			if ((line != NULL) && (*line != '\0'))
			{
				write(fd, line, size);
				write(fd, "\n", 1);
				free(line);
			}
		}
		rl_clear_history();
		close(stdin_backup);
		close(fd);
		end_structures(all, 1, 1);
		exit (0);
	}
	else if (pid > 0)
	{
		all->process_info->is_heredoc = false;
		waitpid(pid, NULL, 0);
		return (pid);
	}
	return (1);
}

int	add_heredoc_history(char *buffer, char *user_line, int size)
{
	t_gal x;	

	x = (t_gal){0, 0, 1, size, user_line, NULL, open(TEMP_FILE, O_RDONLY)};
	if (x.fd < 0)
		return (0);
	while (x.readbytes > 0)
	{
		x.readbytes = read(x.fd, buffer, BUFFER_SIZE);
		if (x.readbytes == 0)
			break ;
		x.all_read += x.readbytes;
		(void)((x.readbytes > 0) && (x.new_line = malloc((x.all_read + 1))));
		if (!x.new_line || (x.readbytes == -1))
			return (free(x.line), 0);
		x.index1 = -1;
		while (++x.index1 < (x.all_read + 1) && (x.line) && x.line[x.index1])
			x.new_line[x.index1] = x.line[x.index1];
		free((char *)((long)x.line * (x.index2 > 0)));
		x.index2 = 0;
		while (x.index1 < (x.all_read + 1) && (x.index2 < x.readbytes))
			x.new_line[x.index1++] = buffer[x.index2++];
		x.new_line[x.index1] = '\0';
		x.line = x.new_line;
	}
	return (add_history(x.line), free((char *)((long)x.line * (x.index2 > 0))), close(x.fd), 1);
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

int	exec_redirections(t_all *all, t_cmd *node, int redir_fds[2], int pipe_fds[2])
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
			result = redir_heredoc(all, redir_fds, false, redir);
		if (result != true)
			return (0);
		redir = redir->next;
	}
	return (1);
}