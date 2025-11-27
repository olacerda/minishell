/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 07:24:07 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/29 07:29:42 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <varargs.h>
#include <stdarg.h>

int	teste(int a, ...)
{
	va_list teste;

	va_start(teste, a);
	va_arg(teste, a);
	
}

int	main(void)
{
	int a;

	a = 0;
	printf("a: %d\n", a);	
}