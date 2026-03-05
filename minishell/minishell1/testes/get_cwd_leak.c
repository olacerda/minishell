/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cwd_leak.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 16:13:29 by olacerda          #+#    #+#             */
/*   Updated: 2026/02/28 16:17:42 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <linux/limits.h>

int	main(void)
{
	char	buffer[PATH_MAX];
	char	*path;

	path = getcwd(buffer, PATH_MAX);
	int index = 0;
	write(1, "\n\n\n", 3);
	while (path[index])
		write(1, &path[index++], 1);
	write(1, "\n\n\n", 3);
	return (0);
}