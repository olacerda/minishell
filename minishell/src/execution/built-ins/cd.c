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

// int	cd_tilde(char *argument)
// {
	
// }

// int	cd_dash(char *argument)
// {

// }

int	check_symbol(char *string, int index, char **simbols)
{
	if (!string || !simbols)
		return (-1);
	if (string[index] == *simbols[DOT])
	{
		if (*(short *)&string[index] == *(short *)simbols[DOUBLE_DOT])
			return (DOUBLE_DOT);
		else
			return (DOT);
	}
	else if (string[index] == *simbols[DASH])
		return (DASH);
	else if (string[index] == *simbols[TILDE])
		return (TILDE);
	else if (string[index] == *simbols[SLASH])
		return (SLASH);
	return (0);
}

int	built_cd(char **envp, char **args)
{
	int	line;

	if (!envp || !args)
		return (0);
	line = 0;
	while (args[line] != NULL)
	{
		if (line > 2)
			return (write(1, "cd: too many arguments\n", 23), 0);
		line++;
	}
	line = 1;
	if (!args[line])
		return (chdir(find_environment_variable("HOME", envp)), 0);
	if (access(args[line], F_OK | X_OK) != 0)
		return (perror("access"), 0);
	chdir(args[line]);
	return (1);
}

// int	built_cd(char **envp, char **args)
// {
// 	char	path[PATH_MAX];
	// static char	*symbols[] = {".", "..", "-", "~", "/", NULL};
	// static int	symbols_size[] = {1, 2, 1, 1, 1};
	// int		symbol;
	// int		line;
	// int		index;

	// if (!envp || ! args)
	// 	return (0);
	// line = 0;
	// while (args[line] != NULL);
	// {
	// 	if (line > 2)
	// 		return (write(1, "cd: too many arguments\n", 23), 0);
	// 	line++;
	// }
	// symbols = (char *[]){".", "..", "-", "~", "/", NULL};
	// symbols_size = (int []){1, 2, 1, 1, 1};
	// line = 1;
	// index = 0;
	// while (args[line][index] != '\0')
	// {
	// 	symbol = check_symbol(args[line], index, symbols);
	// }
// }