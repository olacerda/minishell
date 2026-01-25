/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_prefix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:53:08 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/19 12:16:50 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core_execution.h>

int	get_all_prefixs(t_prefix *prefix)
{
	if (!prefix)
	{
		put_error("Error\nNULL pointer in argument of 'get_all_prefixs'");
		return (0);
	}
	prefix->path = "PATH=";
	prefix->home = "HOME=";
	prefix->oldpwd = "PWD=";
	prefix->oldpwd = "OLDPWD=";
	prefix->user = "USER=";
	return (1);
}

int	compare_prefix(char *string1, char *string2)
{
	int	index;

	index = 0;
	if (!string1 || !string2)
		return (0);
	while ((string1[index]) && (string2[index]) && string1[index] == string2[index])
	{
		index++;
	}
	if (string1[index] == '\0')
	{
		return (1);
	}
	return (0);
}
