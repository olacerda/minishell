/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 11:07:25 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/11 11:26:50 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    int fds[2];
    char buffer[100];
    int readbytes;

    while (1)
    {
        readbytes = read(STDIN_FILENO, buffer, 99);
        if (readbytes <= 0) // EOF ou erro
            break;
        buffer[readbytes] = '\0';

        if (buffer[0] == 'z')
        {
            // Cria pipe para simular EOF
            pipe(fds);
            close(fds[1]);              // lado de escrita fechado → EOF
            dup2(fds[0], STDIN_FILENO); // stdin agora lê do pipe fechado
            close(fds[0]);              // fd antigo já não é necessário
        }

        printf("lido: %s", buffer);
    }

    printf("EOF detectado, saindo\n");
    return 0;
}