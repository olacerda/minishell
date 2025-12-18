/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maracutaia.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 09:25:10 by olacerda          #+#    #+#             */
/*   Updated: 2025/12/18 09:26:00 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MARACUTAIA_H
# define MARACUTAIA_H

#include <unistd.h>

#define FAZ (void)((n < 0) && write(1, "-", 1) && (n = -n)),
#define O  n > 9 && pnb(n / 10),
#define NUMERO write(1, &(char){n % 10 + 48}, 1),
#define AI  1

int	pnb(long n);

#endif