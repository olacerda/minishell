/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_atty.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 04:19:53 by olacerda          #+#    #+#             */
/*   Updated: 2026/02/26 04:25:23 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int	fds[2];

	printf("fds[0]: %d  fds[1]: %d\n\n", fds[0], fds[1]);
	printf("%d\n", isatty(fds[0]));
	printf("%d\n", isatty(fds[1]));
	printf("\n\n");
	printf("%d\n", isatty(-1));
	printf("%d\n", isatty(STDIN_FILENO));
	printf("%d\n", isatty(STDOUT_FILENO));
	pipe(fds);
	printf("fds[0]: %d  fds[1]: %d\n\n", fds[0], fds[1]);
	printf("%d\n", isatty(fds[0]));
	printf("%d\n", isatty(fds[1]));

}