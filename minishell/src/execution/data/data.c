/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:43:11 by otlacerd          #+#    #+#             */
/*   Updated: 2025/11/11 02:44:21 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <data.h>

void	put_error(char *problem)
{
	int	index;

	index = 0;
	if (!problem)
		return ;
	while (problem[index])
		index++;
	write(2, problem, index);
}

t_minishellinfo *init_structures(void)
{
	t_minishellinfo *all;
	t_prefix *prefx;

	all = malloc(sizeof(t_minishellinfo));
	if (!all)
	{
		put_error("Error\nFailed to allocate struct 'ALL'\n");
		end_structures(all);
		return (NULL);
	}
	*all = (t_minishellinfo){0};
	prefx = malloc(sizeof(t_prefix));
	if (!prefx)
	{
		put_error("Error\nFaile to allocate struct 'prefx'\n");
		end_structures(all);
		return (NULL);
	}
	*prefx = (t_prefix){0};
	all->prefx = prefx;
	return (all);
}

void	end_structures(t_minishellinfo *all)
{
	if (!all)
		return ;
	if (all->prefx)
		free(all->prefx);
	if (all)
		free(all);
}