/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_comand_lst.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 09:13:47 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/04 23:04:31 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <data.h>

char	**create_args_buffer(int line, char **all_args)
{
	char 	**args;
	int		count;
	int		size;

	size = 0;
	args = NULL;
	while((all_args[line]) && (all_args[line][0] != '|'))
	{
		if (is_redirection(all_args[line]))
		{
			count = 0;
			while ((count < 2) && (all_args[line] != NULL))
			{
				count++;
				line++;
			}
		}
		else if (all_args[line++] != NULL)
			size++;
	}
	args = malloc((size + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	return (args);
}

void	assign_args(int *line, char **splitted, char **comand, char **args)
{
	int	string;
	int	count;

	if (!line || !splitted || !comand || !args)
		return ;
	string = 0;
	*comand = splitted[(*line)];
	if (splitted[*line] == NULL)
		return ;
	while ((splitted[*line] != NULL) && (splitted[*line][0] != '|'))
	{
		if (is_redirection(splitted[*line]) > 0)
		{
			count = 0;
			while ((count < 2) && (splitted[(*line)++] != NULL))
				count++;
		}
		else if (splitted[*line] != NULL)
		{
			args[string] = splitted[(*line)];
			(*line)++;
			string++;
		}
	}
	args[string] = NULL;
}

int	create_n_assign_node_comand(t_cmd **lst_head, char *cmd, char **args)
{
	t_cmd *node;

	if (!lst_head || !cmd || !args)
		return (0);
	node = NULL;
	if ((*lst_head) == NULL)
	{
		(*lst_head) = comand_lstnew(cmd, args);
		if (!(*lst_head))
			return (0);
		node = (*lst_head);
	}
	else
	{
		node = comand_lstnew(cmd, args);
		if (!node)
			return (comand_lstclear(&(*lst_head), del), 0);
		comand_lstadd_back(&(*lst_head), node);
	}
	return (1);
}

t_cmd *create_linked_list(char **splitted, t_all *all)
{
	t_cmd *lst_head;
	int	line;
	int	line_temp;
	char *comand;
	char **args;

	lst_head = NULL;
	comand = NULL;
	args = NULL;
	line = 0;
	if (!all || !splitted || !(*splitted))
		return (NULL);
	while (splitted[line] != NULL)
	{
		args = create_args_buffer(line, splitted);
		line_temp = line;
		assign_args(&line, splitted, &comand, args);
		if (create_n_assign_node_comand(&lst_head, comand, args) == true)
			all->lst_size++;
		line = create_lst_redir(lst_head, all, splitted, line_temp);		
		// dprintf(2, "\n\nline: %d\n\n", line);
		// create_lst_redir(lst_head, all, splitted, &line);		
		if((splitted[line]) && (splitted[line][0] == '|'))
			free(splitted[line++]);
	}
	free(splitted);
	return (all->node_number = 0, lst_head);
}
