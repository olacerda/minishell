/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:41:35 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/13 22:05:37 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <minishell.h>
# include <core_execution.h>

//-------data.c
void			put_error(char *problem);
t_minishellinfo *init_structures(void);
void			end_structures(t_minishellinfo *all);
void			fill_structures(t_minishellinfo *all, int argc, char **argv, char **envp);
void			clean_args(char **args);

//------structure.c
char 			**create_args(char *string);
int				count_args(char **args);
void			del(void *content);
t_comand 		*create_comand_list(char **all_args);


//-----data.c
void		ft_lstadd_back(t_comand **lst, t_comand *new);
void		del(void *content);
void		ft_lstclear(t_comand **lst, void (*del)(void*));
int			ft_lstsize(t_comand *lst);
t_comand	*ft_lstnew(char *comand, char **args);



#endif