/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 05:29:14 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/24 07:18:36 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built-ins.h>

int	built_unset(char **envp, t_comand *node, t_env *env)
{
	int	line;

	if (!envp || !node || !env)
		return (0);
	line = 0;
	while (node->args[line])
	{
		env_remove(env, node->args[line]);
		line++;
	}
	return (1);
}
