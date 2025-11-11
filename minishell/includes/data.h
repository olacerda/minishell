/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:41:35 by otlacerd          #+#    #+#             */
/*   Updated: 2025/11/11 02:47:09 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <minishell.h>

void			put_error(char *problem);
t_minishellinfo *init_structures(void);
void			end_structures(t_minishellinfo *all);



#endif