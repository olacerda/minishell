/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_comand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 22:45:35 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/19 06:52:48 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <data.h>

void	comand_lstadd_back(t_comand **lst, t_comand *new)
{
	t_comand	*temp;

	// printf("estou no addback\n\n");
	temp = *lst;
	if (!new)
	{
		printf("erro na protecao");
		return ;
	}
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->next = NULL;
	}
}

// void	comand_lstadd_front(t_comand **lst, t_comand *new)
// {
// 	if (!lst || !new)
// 		return ;
// 	new->next = *lst;
// 	*lst = new;
// }

void	del(void *content)
{
	if (!content)
		return ;
	free(content);
}

void	comand_lstclear(t_comand **lst, void (*del)(void*))
{
	t_comand	*temp;
	t_comand	*nexttemp;

	temp = *lst;
	while (temp != NULL)
	{
		nexttemp = temp->next;
		del(temp->comand);
		del(temp->args);
		free(temp);
		temp = nexttemp;
	}
	*lst = NULL;
}

t_comand	*comand_lstnew(char *comand, char **args)
{
	t_comand	*new;

	new = (t_comand *) malloc(sizeof(t_comand));
	if (!new)
		return (NULL);
	new->comand = comand;
	new->args = args;
	new->redir = NULL;
	new->next = NULL;
	return (new);
}

int	comand_lstsize(t_comand *lst)
{
	if (!lst)
		return (0);
	int	count;

	count = 1;
	while (lst->next != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}