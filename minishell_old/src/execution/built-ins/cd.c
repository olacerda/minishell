// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   cd.c                                               :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2026/02/26 02:44:14 by olacerda          #+#    #+#             */
// /*   Updated: 2026/02/26 03:20:44 by olacerda         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include <built-ins.h>

int	cd_minus(t_env *env)
{
	char *oldpwd;
	char *value;

	if (!env)
		return (0);
	oldpwd = find_environment_variable("OLDPWD", env->envp);
	value = get_value(oldpwd, 7);
	if (oldpwd == NULL)
	{
		write(1, "cd: OLDPWD not set\n", 19);
		return (0);
	}
	env_add(env, env_find("PWD", env->envp), "PWD", value);
	chdir(find_environment_variable("OLDPWD", env->envp));
	return (1);
}

int	built_cd(char **envp, t_comand *node, t_env *env)
{
	int	line;

	if (!envp || !node || !node->args)
		return (0);
	(void)env;
	line = 0;
	while (node->args[++line] != NULL)
	{
		if (line > 2)
			return (write(1, "cd: too many arguments\n", 23), 0);
		line++;
	}
	line = 1;
	if (!node->args[line])
		return (chdir(find_environment_variable("HOME", envp)), 0);
	if ((node->args[line][0] == '-') && (node->args[line][0] == '\0'))
		cd_minus(env);
	else
	{
		if (access(node->args[line], F_OK | X_OK) != 0)
			return (perror("access"), 0);
		chdir(node->args[line]);
	} 
	return (1);
}
