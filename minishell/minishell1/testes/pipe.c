/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_teste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:50:22 by otlacerd          #+#    #+#             */
/*   Updated: 2025/11/14 22:34:55 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*create_pipe(void)
{
	static int fd_child[2];
	int	result;

	result = pipe(fd_child);


	// int	index = 0;
	// while (index < 2)
	// 	printf("%d\n", fd_child[index++]);

	
	if (result == -1)
		return (NULL);
	return (fd_child);
}

//------------------ primeiros testes da funcao pipe()  com gustavo -----------
 int	main(void)
{
	char buffer[100000];
	int	bytes;
	int pid;
	int	fd_new = 1;
	int fd_new2 = 20;
	int *fd_1;

	write(1, "teste", 5);
	pid = getpid();
	fd_1 = create_pipe();
	dup2(1, 19);
	dup2(fd_1[1], 1);
	// dup2(fd_1[1], fd_new2);
	dup2(1, fd_new2);
	
	printf("fd_1[1]: %d    fd_new: %d    fd_new2: %d\n\n", fd_1[1], fd_new, fd_new2);
	fflush(stdout);
	write(1, "maca\n", 5);
	// int	index = 0;
	// while (index < 2)
	// 	printf("%d\n", fd_1[index++]);
	write(fd_new2, "banana\n", 7);
	write(fd_1[1], "teste\n", 6);
	write(1, "teses\n", 6);
	// fflush(stdout);

	bytes = read(fd_1[0], buffer, 10000);
	buffer[bytes] = '\0';
	write(2, buffer, bytes);
	printf("hello");
	// while(1);
	printf("stdout size: %d\n\n", sizeof(stdout));
	printf("STDOUT_FILENO size: %d\n\n", sizeof(STDOUT_FILENO));
	fprintf(stdout, "Ihh deu boro\n");
}