/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 09:14:01 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/04 23:04:27 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <data.h>

int	is_redirection(char *string)
{
	if (!string)
		return (-1);
	if (string_compare(string, ">") == 0)
		return (REDIR_OUTPUT);
	else if (string_compare(string, "<") == 0)
		return (REDIR_INPUT);
	else if (string_compare(string, ">>") == 0)
		return (REDIR_APPEND);
	else if (string_compare(string, "<<") == 0)
		return (REDIR_HEREDOC);
	return (0);
}

int	create_n_assign_node_redir(t_redir **head, char **splitted, int line)
{
	int	type;
	t_redir	*node;
	
	if (!head || !splitted)
		return (0);
	type = is_redirection(splitted[line]);
	node = NULL;
	if ((*head) == NULL)
	{
		(*head) = redir_lstnew(type, splitted[line + 1]);
		if (!(*head))
			return (0);
		node = (*head);
	}
	else
	{
		node = redir_lstnew(type, splitted[line + 1]);
		if (!node)
			return (redir_lstclear(&(*head), del), 0);
		redir_lstadd_back(&(*head), node);
	}
	return (1);
}

// int	create_lst_redir(t_cmd *head, t_all *all, char **splitted, int *line)
int	create_lst_redir(t_cmd *head, t_all *all, char **splitted, int line)
{
	t_redir_type	type;
	t_cmd			*node;
	int				node_number;
	int				redir_nbr;

	if (!head || !splitted)
		return (0);
	node = head;
	node_number = 0;
	redir_nbr = 0;
	while (node_number++ < (all->lst_size - 1))
		node = node->next;
	while ((splitted[line] != NULL) && (splitted[line][0] != '|'))
	{
		type = is_redirection(splitted[line]);
		if ((type > 0))
		{
			if (type == REDIR_HEREDOC)
				all->heredoc_last_node = all->lst_size;
			if (create_n_assign_node_redir(&(node->redir), splitted, line)
				&& (type == REDIR_HEREDOC))
				redir_nbr++;
			// dprintf(2, "\n\n\n redir type: %s\narg number: %d\n\n\n", splitted[line], line);
			free(splitted[line]);
			line += 2;
		}
		else
			line++;
	}
	if (redir_nbr > 0)
		all->last_heredoc_redir_node = redir_nbr;
	return (line);
}
