/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:17:42 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/28 11:59:00 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "minishell.h"
# include "utils.h"
# include "core_execution.h"

//env.c ------------------------------------------------------------------------
int		built_env(char **envp, t_comand *node, t_env *env);
char	**create_env(char **envp, int *capacity);
int		assign_env_struct(t_minishellinfo *all);

int		env_free(char **buffer, int size);
int		env_add(t_env *env_st, int line, char *key, char *string);
int		env_remove(t_env *env_st, char *key);
int		env_show(char **envp, int is_export);
int		env_find(char *key, char **envp);
int		env_update(t_env *env_st, char *key, char *new_value1, char *new_value2);

//cd.c-------------------------------------------------------------------------
int		cd_minus(t_env *env);
int		built_cd(char **envp, t_comand *node, t_env *env);

//echo.c-------------------------------------------------------------------------
int		built_echo(char **envp, t_comand *node, t_env *env);

//export.c ------------------------
int		built_export(char **envp, t_comand *node, t_env *env);
int		identifie_case(t_env *env, char *string);
char	*get_key(char *string, int	delimiter);
char	*get_value(char *string, int beginning);
char	**duplicate_envp(t_env *env_st);
int		sort_env(char **env);

//unset.c ------------------------------
int		built_unset(char **envp, t_comand *node, t_env *env);

//exit.c --------------------------
int		built_exit(char **envp, t_comand *node, t_env *env);

#endif