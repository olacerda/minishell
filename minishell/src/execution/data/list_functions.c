/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 22:45:35 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/18 05:41:17 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <data.h>

void	ft_lstadd_back(t_comand **lst, t_comand *new)
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

// void	ft_lstadd_front(t_comand **lst, t_comand *new)
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

void	ft_lstclear(t_comand **lst, void (*del)(void*))
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

t_comand	*ft_lstnew(char *comand, char **args)
{
	t_comand	*new;

	new = (t_comand *) malloc(sizeof(t_comand));
	if (!new)
		return (NULL);
	new->comand = comand;
	new->args = args;
	new->next = NULL;
	return (new);
}

int	ft_lstsize(t_comand *lst)
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