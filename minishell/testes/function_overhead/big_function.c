/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:30:39 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/06 23:29:59 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct { char data[1024]; } t_struct;

int	*big_function(void *str) {
	
	if (!str) return (NULL);

    t_struct a, b, c, d, e;
	a.data[0] = 1;
	b.data[0] = 2;
	c.data[0] = 3;
	d.data[0] = 4;
	e.data[0] = 5;
	printf("%d %d %d %d %d\n", a.data[0], b.data[0], c.data[0], d.data[0], e.data[0]);
	int z = 8;
    printf("%p\n", (void*)&z);
	printf("stack size: %li\n", (long)((long)(&z) - (long)str));
	return (NULL);
}

int main() {
    long *a = NULL;
    printf("%p\n", (void*)&a);
    for (int i = 0; i < 1000; i++) {
		if (i == 500)
			big_function("oi");
        big_function(a);
    }
	free(a);
	char *b;
    // printf("%p\n", (void*)&b);
	static char array[1000];
	(void)array;
    return 0;
}