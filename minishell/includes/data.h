/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:41:35 by otlacerd          #+#    #+#             */
/*   Updated: 2026/03/04 23:47:43 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <minishell.h>
# include <core_execution.h>

//-data.c-----------------------------------------------------------------------
t_all	*init_structures(void);
int		fill_structures(t_all *all, int argc, char **argv, char **envp);
int		fill_structs_on_loop(t_all *all);
void	end_structures(t_all *all, int finish, int is_children);

//-create_comand_lst.c----------------------------------------------------------

char	**create_args_buffer(int line, char **all_args);
void	assign_args(int *line, char **splitted, char **comand, char **args);
int		create_n_assign_node_comand(t_cmd **lst_head, char *cmd, char **args);
t_cmd	*create_linked_list(char **all_args, t_all *all);

//-create_redir_lst.c ----------------------------------------------------------
// int		create_lst_redir(t_cmd *head, t_all *all, char **arg, int *line);
int		create_lst_redir(t_cmd *head, t_all *all, char **splitted, int line);
int		create_n_assign_node_redir(t_redir **head, char **splitted, int line);
int		is_redirection(char *string);

//-list_comand.c ---------------------------------------------------------------
void	comand_lstadd_back(t_cmd **lst, t_cmd *new);
void	comand_lstclear(t_cmd **lst, void (*del)(void*));
int		comand_lstsize(t_cmd *lst);
t_cmd	*comand_lstnew(char *comand, char **args);
void	del(void *content);

//-list_redir.c ----------------------------------------------------------------
void	redir_lstadd_back(t_redir **lst, t_redir *new);
void	redir_lstclear(t_redir **lst, void (*del)(void*));
int		redir_lstsize(t_redir *lst);
t_redir	*redir_lstnew(t_redir_type type, char *args);

#endif