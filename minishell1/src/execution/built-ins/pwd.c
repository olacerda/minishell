/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 13:10:09 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/01 10:21:58 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built-ins.h>

int	built_pwd(char **envp, t_comand *node, t_env *env)
{
	char	buffer[PATH_MAX];
	char *pwd_pointer;
	// static int size;
	
	(void)envp;
	(void)node;
	(void)env;
	pwd_pointer = getcwd(buffer, PATH_MAX);
	print_string(pwd_pointer);
	write(1, "\n", 1);
	return (1);
}