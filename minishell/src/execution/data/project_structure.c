/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_structure.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:56:45 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/13 22:32:54 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <data.h>

char	**assign_arg(char *string, int count, int index2, char **result)
{
	int index1;
	int line;

	index1 = 0;
	line = 0;
	while (string[index1] != '\0')
	{
		count = 0;
		while ((string[index1] != '\0') && (string[index1] == ' '))
			index1++;
		if ((string[index1] != '\0') && (string[index1] != ' '))
		{
			index2 = index1;
			while ((string[index1] != '\0') && (string[index1++] != ' '))
				count++;
			result[line] = malloc((count + 1) * (sizeof(char)));
			if (!result[line])
				return (NULL);
			count = 0;
			while ((string[index2] != '\0') && (string[index2] != ' '))
				result[line][count++] = string[index2++];
			result[line++][count] = '\0';
		}
	}
	return (result[line] = NULL, result);
}

char **create_args(char *string)
{
	char **result;
	int	index1;
	int	index2;
	int	count;

	if (!string)
		return (NULL);
	index1 = 0;
	count = 0;
	while (string[index1] != '\0')
	{
		if ((string[index1] != '\0') && (string[index1] != ' '))
		{
			count++;
			while ((string[index1] != ' ') && (string[index1] != '\0'))
				index1++;
		}
		else
			index1++;
	}
	result = malloc((count + 1) * (sizeof(char *)));
	if (!result)
		return (NULL);
	index2 = 0;
	return (assign_arg(string, count, index2, result));
}

int	count_args(char **args)
{
	int	line;

	line = 0;
	while (args[line] != NULL)
		line++;
	return (line);
}

void	clean_args(char **args)
{
	int	line;

	line = 0;
	if (!args)
		return ;
	while (args[line] != NULL)
	{
		free(args[line]);
		line++;
	}
	free(args[line]);
}

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

char	**create_args_buffer(int line, char **all_args)
{
	char 	**args;
	int 	string;
	int		count;
	int		size;

	size = 0;
	string = line;
	args = NULL;
	while((all_args[string]) && (all_args[string][0] != '|'))
	{
		if (is_redirection(all_args[string]))
		{
			count = 0;
			while ((count < 2) && (all_args[string++] != NULL))
				count++;
		}
		else if (all_args[string++] != NULL)
			size++;
	}
	args = malloc((size + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	return (args);
}

void	assign_args(int *line, char **all_args, char **comand, char **args)
{
	int	string;
	int	count;

	if (!line || !all_args || !comand || !args)
		return ;
	string = 0;
	*comand = all_args[(*line)];
	if (all_args[*line] == NULL)
		return ;
	while ((all_args[*line] != NULL) && (all_args[*line][0] != '|'))
	{
		if (is_redirection(all_args[*line]) > 0)
		{
			count = 0;
			while ((count < 2) && (all_args[(*line)++] != NULL))
				count++;
		}
		else if (all_args[*line] != NULL)
		{
			args[string] = all_args[(*line)];
			(*line)++;
			string++;
		}
	}
	args[string] = NULL;
}

int	create_n_assign_node_comand(t_comand **lst_head, char *comand, char **args)
{
	t_comand *node;

	if (!lst_head || !comand || !args)
		return (0);
	node = NULL;
	if ((*lst_head) == NULL)
	{
		(*lst_head) = comand_lstnew(comand, args);
		if (!(*lst_head))
			return (0);
		node = (*lst_head);
	}
	else
	{
		node = comand_lstnew(comand, args);
		if (!node)
			return (comand_lstclear(&(*lst_head), del), 0);
		comand_lstadd_back(&(*lst_head), node);
	}
	return (1);
}

int	create_n_assign_node_redirection(t_redirection **head, char **all_args, int string)
{
	int	type;
	t_redirection	*node;
	
	if (!head || !all_args)
		return (0);
	type = is_redirection(all_args[string]);
	node = NULL;
	if ((*head) == NULL)
	{
		(*head) = redir_lstnew(type, all_args[string + 1]);
		if (!(*head))
			return (0);
		node = (*head);
	}
	else
	{
		node = redir_lstnew(type, all_args[string + 1]);
		if (!node)
			return (redir_lstclear(&(*head), del), 0);
		redir_lstadd_back(&(*head), node);
	}
	return (1);
}

int	create_n_assign_lst_redirection(t_comand *head, t_minishellinfo *all, char **all_args, int string)
{
	t_redir_type	type;
	int				node_number;
	t_comand		*node;
	int				redir_nbr;

	if (!head || !all_args)
		return (0);
	node = head;
	node_number = 0;
	redir_nbr = 0;
	while (node_number++ < (all->node_count - 1))
		node = node->next;
	while ((all_args[string] != NULL) && (all_args[string][0] != '|'))
	{
		type = is_redirection(all_args[string]);
		if ((type > 0))
		{
			if (type == REDIR_HEREDOC)
				all->heredoc_last_node = all->node_count;
			if (create_n_assign_node_redirection(&(node->redir), all_args, string)
				&& (type == REDIR_HEREDOC))
				redir_nbr++;
			string += 2;
		}
		else
			string++;
	}
	if (redir_nbr > 0)
		all->last_heredoc_redir_node = redir_nbr;
	return (1);
}

t_comand *create_comand_list(char **all_args, t_minishellinfo *all)
{
	t_comand *lst_head;
	int	line;
	int	line_temp;
	char *comand;
	char **args;

	lst_head = NULL;
	comand = NULL;
	args = NULL;
	line = 0;
	if (!all_args)
		return (NULL);
	while (all_args[line] != NULL)
	{
		args = create_args_buffer(line, all_args);
		line_temp = line;
		assign_args(&line, all_args, &comand, args);
		if (create_n_assign_node_comand(&lst_head, comand, args) == true)
			all->node_count++;
		create_n_assign_lst_redirection(lst_head, all, all_args, line_temp);		
		if((all_args[line]) && (all_args[line][0] == '|'))
			line++;
	}
	return (lst_head);
}
