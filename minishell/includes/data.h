/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:41:35 by otlacerd          #+#    #+#             */
/*   Updated: 2026/03/01 15:59:25 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <minishell.h>
# include <core_execution.h>

//-------data.c-----------------------------------------------------------------------------------------------------
t_minishellinfo *init_structures(void);
int				fill_structures(t_minishellinfo *all, int argc, char **argv, char **envp);
int				fill_structs_on_loop(t_minishellinfo *all);
void			end_structures(t_minishellinfo *all, int flag);
int				close_fd(int *fd);
int				destroy_fds(t_minishellinfo *all, int flag);
int				restore_original_fds(t_minishellinfo *all);


//------project_structure.c-----------------------------------------------------------------------------------------
char			**split_line(char *string);
char			**assign_line(char *string, int count, int index2, char **result);
int				count_words(char **args);
void			clean_char_dpointer(char **args);

char			**create_args_buffer(int line, char **all_args);
void			assign_args(int *line, char **all_args, char **comand, char **args);
int				create_n_assign_node_comand(t_comand **lst_head, char *comand, char **args);
t_comand		*create_linked_list(char **all_args, t_minishellinfo *all);

int				create_n_assign_lst_redirection(t_comand *head, t_minishellinfo *all, char **all_args, int string);
int				create_n_assign_node_redirection(t_redirection **head, char **all_args, int string);
int				is_redirection(char *string);

//list_comand.c ----------------------------------------------------------------------------------------------
void			comand_lstadd_back(t_comand **lst, t_comand *new);
void			comand_lstclear(t_comand **lst, void (*del)(void*));
int				comand_lstsize(t_comand *lst);
t_comand		*comand_lstnew(char *comand, char **args);
void			del(void *content);

//list_redir.c ----------------------------------------------------------------------------------------------
void			redir_lstadd_back(t_redirection **lst, t_redirection *new);
void			redir_lstclear(t_redirection **lst, void (*del)(void*));
int				redir_lstsize(t_redirection *lst);
t_redirection	*redir_lstnew(t_redir_type type, char *args);


#endif