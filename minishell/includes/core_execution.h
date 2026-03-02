/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_execution.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:54:14 by otlacerd          #+#    #+#             */
/*   Updated: 2026/03/02 16:36:49 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_EXECUTION_H
# define CORE_EXECUTION_H
# include <minishell.h>
# include <utils.h>
# include <data.h>
# include <built-ins.h>

//---------envp_path.c ---------------------------------------------------------------------------------------
char 			*get_absolute_path(char *prefix, char *comand, char **envp);
char 			*find_absolute_path(char *environment_variable, char *comand, int prefix_size);
int				is_accessible(char *path, char *comand);
int				append_comand_to_path(char *path, char *comand, int path_idx, int path_buffer_size);
int				get_next_path(char *path, char *environment_variable, int env_idx, int path_buffer_size);
char			*find_environment_variable(char *prefix, char **envp);

//---------envp.prefix.c ---------------------------------------------------------------------------------------
int				get_all_prefixs(t_prefix *prefix);
int				compare_prefix(char *prefix, char *string);

//---------core_execution.c ---------------------------------------------------------------------------------------
int				execute_comands(t_minishellinfo *all, t_comand *node, char *argv[], char **envp);
int				normal_execution(t_minishellinfo *all, t_comand *node, char *argv[], char **envp);
int				node_execution(t_minishellinfo *all, t_comand *node, char *argv[], char **envp);
int				get_comand_origin(char *prefix, char *comand, char **envp, t_comand_origin *origin);
func_pointer 	*get_built_in(char *comand);
int				execute_external_comand(char *absolute_path, char **args, char **envp, int *fds);
int				execute_built_in(t_comand_origin *origin, t_comand *node, t_env *env);
int				execute_redirections(t_comand *node, int redir_fds[2], int pipe_fds[2], t_minishellinfo *all);
int				sync_redirection_and_pipe(t_comand *node, t_redirection *redir, int *redir_fd, int *pipe_fd);

//--------pipes.c ---------------------------------------------------------------------------------------
int				execute_pipes(int *fds);
int				execute_last_node(char *absolute_path, char **args, char **envp, int prev_fd_0);
int				execute_middle_node(char *absolute_path, char **args, char **envp, int *fds, int prev_fd_0);
int				execute_first_node(char *absolute_path, char **args, char **envp, int *fds);

//--------pid_manegement.c ---------------------------------------------------------------------------------------
int				wait_all_children(int *children_pids, int size, int *exit_status);
int				create_children_pids_buffer(int **children_pids, int size);
int				update_exit_status(int *exit_status, int status);

//-------redirections.c ---------------------------------------------------------------------------------------
int				execute_redirections(t_comand *node, int redir_fds[2], int pipe_fds[2], t_minishellinfo *all);
int				save_original_fds(int true_fds[2]);
int				copy_fds(int fds1[2], int fds2[2]);
int				redir_in(t_redirection *redir, int fds[2]);
int				redir_out(t_redirection *redir, int fds[2], t_minishellinfo *all);
int				redir_append(t_redirection *redir, int fds[2]);
int				redir_heredoc(int	fds[2], int flag, t_minishellinfo *all, t_redirection *redir);
int				execute_all_heredocs(t_minishellinfo *all);
int				execute_heredoc(char *end_marker, int fd);

#endif