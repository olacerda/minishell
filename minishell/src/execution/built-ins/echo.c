/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 01:54:57 by olacerda          #+#    #+#             */
/*   Updated: 2026/02/26 02:44:04 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built-ins.h>

int	built_echo(char **envp, char **args)
{
	int	line;
	int	flag;

	if (!envp || !args)
		return (0);
	line = 1;
	flag = 0;
	while (args[line] != NULL)
	{
		if ((line == 1) && *(short *)args[line] == *(short *)"-n")
		{
			flag = 1;
			line++;
			continue ;
		}
		put_string(args[line]);
		line++;
		if (args[line] != NULL)
			write(STDOUT_FILENO, " ", 1);
	}
	if (flag == false)
		write(STDOUT_FILENO, "\n", 1);
	return (1);
}
