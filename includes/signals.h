/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 06:58:43 by olacerda          #+#    #+#             */
/*   Updated: 2026/03/12 00:31:53 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H
# include "minishell.h"

//-signals.c -------------------------------------------------------------------
void    handler(int sig);
t_proc	*get_process_info(t_all *all);
void	signals(int is_child);


#endif