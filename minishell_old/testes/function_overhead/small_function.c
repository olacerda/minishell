/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:30:15 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/06 23:10:50 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void small_function(void *str) {
	
	if (!str) return;
	
    int a = 1;
    int b = 2;
    int c = 3;
	printf("%d %d %d\n", a, b, c);
    printf("%p\n", (void*)&a);
	int	z = 3;
	printf("stack size: %li\n", (long)((long)(&z) - (long)str));
}

int main() {
    char *a = NULL;
    printf("%p\n", (void*)&a);

    for (int i = 0; i < 1000; i++) {
		if (i == 500)
			small_function("oi");
        small_function(a);
    }
	char *b;
    printf("%p\n", (void*)&b);

    return 0;
}