/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 01:54:57 by olacerda          #+#    #+#             */
/*   Updated: 2026/02/28 06:24:17 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built-ins.h>

int	built_echo(char **envp, t_comand *node, t_env *env)
{
	int	line;
	int	flag;

	if (!envp || !node || !node->args)
		return (0);
	(void)env;
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
		print_string(node->args[line]);
		line++;
		if (node->args[line] != NULL)
			write(STDOUT_FILENO, " ", 1);
	}
	if (flag == false)
		write(STDOUT_FILENO, "\n", 1);
	return (1);
}
