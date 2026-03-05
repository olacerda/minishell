/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_teste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 21:09:06 by otlacerd          #+#    #+#             */
/*   Updated: 2025/11/12 22:13:03 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_random_things(char *string)
{
	int	size;

	size = 0;
	if (!string)
		return ;
	while (string[size])
	{
		size++;
	}
	write(1, string, size);
	// fflush(stdout);
}

// int	main(void)
// {

// 	int	pid;
// 	int	alter_pid;
// 	// int	result;
// 	int fd[2];
// 	char buffer[100];
	
// 	// result = pipe(fd);
// 	// write(fd[1], "oioii", 4);
// 	// close(fd[1]);
// 	// dup2(fd[1], 1);
// 	// read(fd[0], buffer, 10);
// 	// write(2, buffer, 4);
// 	// (void)result;
// 	// printf("argv: %s - %i\n", argv[0], argc);
// 	pid = getpid();
// 	alter_pid = fork();
// 	if (alter_pid == 0)
// 	{
// 		printf("alter pid: %d\n\n", alter_pid);
// 		// fflush(stdout);
// 		exit(1);
// 	}
// 	else if (alter_pid > 0)
// 	{
// 		printf("father pid: %d\n\n", pid);
// 		// fflush(stdout);
// 		int status;
// 		wait(&status);
// 		printf("status:%d\n", status);
// 	}
// 	write_random_things("Hello this is a random test lalalala\n");
// 	return (0);
// 	// write(1, "oi", 2);
// }

int	main(void)
{
	int	pid;
	int	alter_pid;
	// int fd[2];
	// char buffer[100];

	pid = getpid();
	alter_pid = fork();
	if (alter_pid == 0)
	{
		printf("alter pid: %d\n\n", alter_pid);
		// fflush(stdout);
		// exit(1);
	}
	else if (alter_pid > 0)
	{
		printf("father pid: %d\n\n", pid);
		// fflush(stdout);
		// int status;
		// wait(&status);
		write_random_things("Hello this is a random test lalalala\n");
		// printf("status:%d\n", status);
	}
	// write_random_things("Hello this is a random test lalalala\n");
	write(1, "teste\n", 6);
	return (0);
}