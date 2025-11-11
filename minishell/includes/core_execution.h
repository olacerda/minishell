/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_execution.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:54:14 by otlacerd          #+#    #+#             */
/*   Updated: 2025/11/11 03:41:15 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_EXECUTION_H
# define CORE_EXECUTION_H
# include <minishell.h>
# include <utils.h>
# include <data.h>

//envp_path.c
char 	*get_absolute_path(char *prefix, char *comand, char **envp);
char 	*find_absolute_path(char *environment_variable, char *comand, int prefix_size);
int		is_accessible(char *path, char *comand);
int		append_comand_to_path(char *path, char *comand, int path_idx, int path_buffer_size);
int		get_next_path(char *path, char *environment_variable, int env_idx, int path_buffer_size);
char	*find_environment_variable(char *prefix, char **envp);

//envp.prefix.c
int		get_all_prefixs(t_prefix *prefix);
int		compare_prefix(char *string1, char *string2);



#endif