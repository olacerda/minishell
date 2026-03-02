/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 00:56:52 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/24 03:58:57 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built-ins.h>

int	built_exit(char **envp, t_comand *node, t_env *env)
{
	(void)envp;
	(void)node;
	(void)env;
	if (!envp)
		return (0);
	return (exit(1), 1);
}