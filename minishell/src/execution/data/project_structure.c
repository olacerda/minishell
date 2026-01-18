/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_structure.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:56:45 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/18 05:44:15 by otlacerd         ###   ########.fr       */
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

char	**create_substring_buffer(int line, char **all_args, int *size)
{
	int 	string;
	char 	**args;

	(*size) = 0;
	string = line;
	while((all_args[string]) && (all_args[string][0] != '|'))
	{
		string++;
		(*size)++;
	}
	args = malloc(((*size)) * sizeof(char *));
	if (!args)
		return (NULL);
	return (args);
}

void	assign_substrings(int *line, char **all_args, int *size, char **comand, char **args)
{
	int	string;

	string = 1;
	*comand = all_args[(*line++)];
	(void)comand;
	if (all_args[*line] == NULL)
		return ;
	while (string < ((*size) - 1))
	{
		args[string] = all_args[(*line)];
		(*line)++;
		string++;
	}
	args[string] = NULL;
}

void	create_n_assign_node(t_comand **lst_head, char *comand, char **args)
{
	t_comand *node;

	node = NULL;
	if ((*lst_head) == NULL)
	{
		(*lst_head) = ft_lstnew(comand, args);
		if (!(*lst_head))
		{
			ft_lstclear(&(*lst_head), del);
			return ;
		}
		node = (*lst_head);			
	}
	else
	{
		node = ft_lstnew(comand, args);
		if (!node)
		{
			ft_lstclear(&(*lst_head), del);
			return ;
		}
		ft_lstadd_back(&(*lst_head), node);
	}
}

t_comand *create_comand_list(char **all_args)
{
	t_comand *lst_head;
	int	line;
	int	size;
	char *comand;
	char **args;

	size = 0;
	lst_head = NULL;
	comand = NULL;
	args = NULL;
	line = 0;
	if (!all_args)
		return (NULL);
	while (all_args[line] != NULL)
	{
		args = create_substring_buffer(line, all_args, &size);
		assign_substrings(&line, all_args, &size, &comand, args);
		create_n_assign_node(&lst_head, comand, args);
		if((all_args[line]) && (all_args[line][0] == '|'))
			line++;
		int	line2;
		t_comand *temp;
		temp = lst_head;
		while (temp != NULL)
		{
			line2 = 0;
			printf("%s\n", temp->comand);
			if (temp->args[line2] == NULL)
				printf("e null, line2 = %d\n", line2);
			else
			{
				while(temp->args[line2])
					printf("%s\n", temp->args[line2++]);
			}
			temp = temp->next;
		}
		write(1, "imprimiu uma vez \n", 18);
		write(1, "\n\n\n", 3);
	}
	return (lst_head);
}
