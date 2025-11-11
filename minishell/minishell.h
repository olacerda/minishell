/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 23:13:23 by otlacerd          #+#    #+#             */
/*   Updated: 2025/11/11 05:14:21 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

// typedef struct s_process
// {
// 	char **arg;
// 	t_comands *comands;
// 	t_process *child;
// 	t_process *next;
// }

typedef struct s_prefix
{
	char *path;
	char *home;
	char *pwd;
	char *oldpwd;
	char *user;
}				t_prefix;

typedef struct s_minishellinfo
{
	t_prefix 	*prefx;
	char 		*enviroment_variable_path;
	int			father_pid;
}				t_minishellinfo;

// int				compare_prefix(char *string1, char *string2);
// char				*find_environment_variable(char *prefix, char **envp);
// int				string_lenght(char *string);
// int				clear_buffer(char *string, int size);
// int				get_next_path(char *path, char *environment_variable, int env_idx, int path_buffer_size);
// int				is_accessible(char *path, char *comand);
// char 			*find_absolute_path(char *environment_variable, char *comand, int prefix_size);
// char 			*get_absolute_path(char *prefix, char *comand, char **envp);
// t_minishellinfo *init_structures(void);
// void				put_error(char *problem);
// void				end_structures(t_minishellinfo *all);
// int				get_all_prefixs(t_prefix *prefix);
// int				append_comand_to_path(char *path, char *comand, int path_idx, int path_buffer_size);


#endif