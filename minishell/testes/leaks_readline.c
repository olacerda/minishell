/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 10:29:51 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/01 10:33:25 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

void	cleanup_readline(void)
{
	rl_clear_history();
	rl_cleanup_after_signal();
	rl_deprep_terminal();
	rl_free_line_state();
}

int	main(void)
{
	char *line;

	while(1)
	{
		line = readline("Teste: ");
		if (!line)
		{
			cleanup_readline();
			break ;
		}
		printf("%s\n", line);
		free(line);
	}
}