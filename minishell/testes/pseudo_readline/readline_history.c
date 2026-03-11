/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 16:12:55 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/08 16:40:36 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

typedef struct termios t_term;

int	pseudo_readline(char *prompt)
{
	t_term old_terminal;
	t_term new_terminal;
	int	size;
	int	stdin_backup;
	int	content_fd;

	tcgetattr(STDIN_FILENO, &old_terminal);
	new_terminal = old_terminal;
	tcsetattr(STDIN_FILENO, )
	if (!prompt)
		return (0);
	size = 0;
	while (prompt[size])
		size++;
	write(1, prompt, size);
	char buffer[100];
	int	readbytes;
	stdin_backup = dup(STDIN_FILENO);
	content_fd = open("/home/olacerda/work/42-cursus/milestone3/minishell/minishell/testes/pseudo_readline/content.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	dupe2(content_fd, STDIN_FILENO);
	readbytes = read(0, buffer, 99);
	buffer[readbytes] = '\0';
	printf("%s\n", buffer);
	return (1);
}


int	main(void)
{
	char *line = NULL;

	pseudo_readline("Ozama Creuza> ");
	return (1);
	line = readline("Piriripompom> ");
	printf("1: %s\n\n", line);
	
	
	line = readline("Piriripompom> ");
	printf("2: %s\n\n", line);
	
	
	line = readline("Piriripompom> ");
	printf("3: %s\n\n", line);
	
	
	line = readline("Piriripompom> ");
	printf("4: %s\n\n", line);
	
	
	line = readline("Piriripompom> ");
	printf("5: %s\n\n", line);
}