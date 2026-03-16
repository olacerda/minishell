/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 13:10:09 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/13 03:02:31 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built-ins.h>

int	built_pwd(t_all *all, t_cmd *node, t_env *env, char *buffer)
{
	char *pwd_pointer;
	
	(void)env;
	(void)node;
	(void)env;
	(void)all;
	pwd_pointer = getcwd(buffer, PATH_MAX);
	if (!pwd_pointer)
		return (0);
	string_print(pwd_pointer);
	write(STDOUT_FILENO, "\n", 1);
	return (1);
}