/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prefix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:53:08 by otlacerd          #+#    #+#             */
/*   Updated: 2026/03/01 18:02:31 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core_execution.h>

int	get_all_prefixs(t_prefix *prefix)
{
	// printf("get_all_prefixs\n\n");
	if (!prefix)
	{
		put_error("Error\nNULL pointer in argument of 'get_all_prefixs'\n");
		return (0);
	}
	prefix->path = "PATH=";
	prefix->home = "HOME=";
	prefix->oldpwd = "PWD=";
	prefix->oldpwd = "OLDPWD=";
	prefix->user = "USER=";
	return (1);
}

int	compare_prefix(char *prefix, char *string)
{
	int	index;

	index = 0;
	if (!prefix || !string)
		return (0);
	while ((prefix[index]) && (string[index]) && prefix[index] == string[index])
	{
		index++;
	}
	if (prefix[index] == '\0')
	{
		return (1);
	}
	return (0);
}
