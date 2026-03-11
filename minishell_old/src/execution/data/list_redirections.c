/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 05:09:11 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/19 08:26:50 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <data.h>

void	redir_lstadd_back(t_redirection **lst, t_redirection *new)
{
	t_redirection	*temp;

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

void	redir_lstclear(t_redirection **lst, void (*del)(void*))
{
	t_redirection	*temp;
	t_redirection	*nexttemp;

	temp = *lst;
	while (temp != NULL)
	{
		nexttemp = temp->next;
		del(temp->redir_arg);
		free(temp);
		temp = nexttemp;
	}
	*lst = NULL;
}

t_redirection	*redir_lstnew(t_redir_type type, char *arg)
{
	t_redirection	*new;

	new = (t_redirection *) malloc(sizeof(t_redirection));
	if (!new)
		return (NULL);
	new->type = type;
	new->redir_arg = arg;
	new->next = NULL;
	return (new);
}

int	redir_lstsize(t_redirection *lst)
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