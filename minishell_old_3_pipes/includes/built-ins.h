/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 22:17:42 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/16 03:46:34 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "minishell.h"
# include "utils.h"
# include "core_execution.h"

//env.c -------------------------
char	**create_env(char **envp, int *capacity);
int		assign_env_struct(t_minishellinfo *all);

int		env_free(char **buffer, int size);
int		env_add(t_env *st_env, int size, char *key, char *string);
int		env_remove(t_env *env_st, char *key);
int		env_show(char **envp);
int		env_find(char *key, char **envp);
int		env_update(char **envp, char *key, char *new_value);


// int		env(void);

#endif