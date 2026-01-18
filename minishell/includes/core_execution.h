/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_execution.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:54:14 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/18 05:13:57 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_EXECUTION_H
# define CORE_EXECUTION_H
# include <minishell.h>
# include <utils.h>
# include <data.h>

//---------envp_path.c
char 	*get_absolute_path(char *prefix, char *comand, char **envp);
char 	*find_absolute_path(char *environment_variable, char *comand, int prefix_size);
int		is_accessible(char *path, char *comand);
int		append_comand_to_path(char *path, char *comand, int path_idx, int path_buffer_size);
int		get_next_path(char *path, char *environment_variable, int env_idx, int path_buffer_size);
char	*find_environment_variable(char *prefix, char **envp);

//---------envp.prefix.c
int		get_all_prefixs(t_prefix *prefix);
int		compare_prefix(char *string1, char *string2);

//---------core_execution.c
int	execute_comand(t_minishellinfo *all, t_comand *node, char *argv[], char **envp, int *fds);
int	normal_execution(t_minishellinfo *all, t_comand *node, char *argv[], char **envp);
int	pipe_execution(t_minishellinfo *all, t_comand *node, char *argv[], char **envp);
int	execute_last_pipe(char *absolute_path, char *argv[], char **envp, int prev_fd_0);
int	execute_middle_pipe(char *absolute_path, char *argv[], char **envp, int *fds, int prev_fd_0);
int	execute_first_pipe(char *absolute_path, char *argv[], char **envp, int *fds);

int	execute_in_pipe(t_minishellinfo *all, char **args, int pipe_position);
int	is_comand(char *comand);
int	get_pipe_position(char **args);

#endif