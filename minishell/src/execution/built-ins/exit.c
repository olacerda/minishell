/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 00:56:52 by otlacerd          #+#    #+#             */
/*   Updated: 2026/03/04 23:49:24 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built-ins.h>

int	built_exit(t_all *all, t_cmd *node, t_env *env, char *buffer)
{
	(void)env;
	(void)node;
	(void)buffer;
	write(STDOUT_FILENO, "exit\n", 5); // ???
	end_structures(all, 1, 0);
	exit (1);
	return (1);
}