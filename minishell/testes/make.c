/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 11:13:24 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/05 19:10:59 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(void)
{
	int	fds[2];
	
	pipe(fds);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	write(fds[1], "make re\n", 8);
	write(STDOUT_FILENO, "qualquer merda\n", 15);
	close(fds[1]);
}
