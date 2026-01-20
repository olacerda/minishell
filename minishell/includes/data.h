/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:41:35 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/19 18:18:04 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <minishell.h>
# include <core_execution.h>

//-------data.c-----------------------------------------------------------------------------------------------------
void			put_error(char *problem);
t_minishellinfo *init_structures(void);
void			fill_structures(t_minishellinfo *all, int argc, char **argv, char **envp);
void			end_structures(t_minishellinfo *all);


//------project_structure.c-----------------------------------------------------------------------------------------
char			**assign_arg(char *string, int count, int index2, char **result);
char			**create_args(char *string);
int				count_args(char **args);
void			clean_args(char **args);

char			**create_args_buffer(int line, char **all_args);
void			assign_args(int *line, char **all_args, char **comand, char **args);
int				create_n_assign_node_comand(t_comand **lst_head, char *comand, char **args);
t_comand		*create_comand_list(char **all_args, t_minishellinfo *all);

int				create_n_assign_lst_redirection(t_comand *head, t_minishellinfo *all, char **all_args, int string);
int				create_n_assign_node_redirection(t_redirection **head, char **all_args, int string);
int				is_redirection(char *string);


//-----data.c---------------------------------------------------------------------------------------------------------
void			del(void *content);

void			comand_lstadd_back(t_comand **lst, t_comand *new);
void			comand_lstclear(t_comand **lst, void (*del)(void*));
int				comand_lstsize(t_comand *lst);
t_comand		*comand_lstnew(char *comand, char **args);

void			redir_lstadd_back(t_redirection **lst, t_redirection *new);
void			redir_lstclear(t_redirection **lst, void (*del)(void*));
int				redir_lstsize(t_redirection *lst);
t_redirection	*redir_lstnew(t_redir_type type, char *args);


#endif