/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 01:54:57 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/04 20:23:56 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built-ins.h>

int	built_echo(t_all *all, t_cmd *node, t_env *env, char *buffer)
{
	int	line;
	int	flag;

	if (!node || !node->args)
		return (0);
	(void)env;
	(void)buffer;
	(void)all;
	line = 1;
	flag = 0;
	while (node->args[line] != NULL)
	{
		if ((line == 1) && *(short *)node->args[line] == *(short *)"-n")
		{
			flag = 1;
			line++;
			continue ;
		}
		string_print(node->args[line]);
		line++;
		if (node->args[line] != NULL)
			write(STDOUT_FILENO, " ", 1);
	}
	if (flag == false)
		write(STDOUT_FILENO, "\n", 1);
	return (1);
}
