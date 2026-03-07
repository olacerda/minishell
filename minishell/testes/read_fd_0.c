/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 05:47:38 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/06 17:23:44 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <string.h>m

#define MAX_HISTORY 100
#define MAX_LINE 1024

char *history[MAX_HISTORY];
int hist_count = 0;

void clear_line(int len)
{
    write(1, "\r", 1); // volta para início da linha
    for (int i = 0; i < len; i++)
        write(1, " ", 1); // sobrescreve com espaços
    write(1, "\r", 1); // volta de novo para início
}

int main(void)
{
    char line[MAX_LINE];
    int len = 0;
    int hist_index = -1;

    while (1)
    {
        write(1, "> ", 2);
        len = 0;
        hist_index = hist_count;

        while (1)
        {
            char c[3];
            int n = read(0, c, 1);
            if (n <= 0) exit(0);

            if (c[0] == '\n')
            {
                line[len] = '\0';
                write(1, "\n", 1);
                if (len > 0 && hist_count < MAX_HISTORY)
                    history[hist_count++] = strdup(line);
                break;
            }
            else if (c[0] == 127) // backspace
            {
                if (len > 0)
                {
                    len--;
                    write(1, "\b \b", 3);
                }
            }
            else if (c[0] == 27) // escape sequence
            {
                int n2 = read(0, c+1, 2); // lê os próximos dois bytes
                if (n2 == 2 && c[1] == '[')
                {
                    if (c[2] == 'A') // seta cima
                    {
                        if (hist_index > 0)
                        {
                            hist_index--;
                            clear_line(len+2);
                            write(1, "> ", 2);
                            write(1, history[hist_index], strlen(history[hist_index]));
                            strcpy(line, history[hist_index]);
                            len = strlen(line);
                        }
                    }
                    else if (c[2] == 'B') // seta baixo
                    {
                        if (hist_index < hist_count-1)
                        {
                            hist_index++;
                            clear_line(len+2);
                            write(1, "> ", 2);
                            write(1, history[hist_index], strlen(history[hist_index]));
                            strcpy(line, history[hist_index]);
                            len = strlen(line);
                        }
                        else if (hist_index == hist_count-1) // limpa linha se chega ao final
                        {
                            hist_index++;
                            clear_line(len+2);
                            write(1, "> ", 2);
                            len = 0;
                        }
                    }
                }
            }
            else
            {
                line[len++] = c[0];
                write(1, c, 1);
            }
        }

        // Aqui você teria a linha final em `line`
        printf("Você digitou: %s\n", line);
    }
}