/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_char_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 04:24:03 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/24 05:10:16 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	string_compare(char *str1, char *str2)
{
	int	i;

	if (!str1 || !str2)
		return (0);
	i = 0;
	while ((str1[i] && str2[i]) && (str1[i] == str2[i]))
		i++;
	if ((str1[i] == '\n'))
		return ('\0' - str2[i]);
	return (str1[i] - str2[i]);
}

int	swap_strings(char **str1, char **str2)
{
	char *temp;

	if (!str1 || !str2)
		return (0);
	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
	return (1);
}

int	sort_env(char **env)
{
	int	line;
	int	smallest;
	int	finder;

	if (!env)
		return (0);
	line = 0;
	smallest = 0;
	finder = 0;
	while (env[line])
	{
		smallest = line;
		finder = line + 1;
		while (env[finder])
		{
			if (string_compare(env[smallest], env[finder]) > 0)
				smallest = finder;
			finder++;
		}
		if (line != smallest)
			swap_strings(&(env[line]), &(env[smallest]));
		line++;
	}
	return (1);
}


int	main(void)
{
	char **string = (char **)((char *[]){"bcd", "cdea", "ajk", "abdz", "cdef", NULL});
	int	line = 0;
	while (((char **)string)[line])
		printf("%s\n", ((char **)string)[line++]);

	sort_env(string);

	printf("\n\nafter:\n\n");
	line = 0;
	while (((char **)string)[line])
		printf("%s\n", ((char **)string)[line++]);
	
}