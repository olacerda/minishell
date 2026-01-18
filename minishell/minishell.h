/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 23:13:23 by otlacerd          #+#    #+#             */
/*   Updated: 2026/01/18 03:19:37 by otlacerd         ###   ########.fr       */
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

typedef struct s_comand
{
	char *comand;
	char **args;
	struct s_comand *next;
}				t_comand;

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
	char 		**argv;
	char		**envp;
	int			argc;
	char 		**args;
	int			node_number;
	int			fd[2];
	int			prev_fd_0;
	t_comand 	*head;
	t_comand	*comand;
}				t_minishellinfo;



// ------------------- Only for faster tests on the main------------
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
// int					execute_comand(t_minishellinfo *all, char *comand, char *argv[], char **envp);
// int					is_comand(char *comand);
// char 			**create_args(char *string);
// void				clean_args(char **args);
// int					count_args(char **args);
// int					get_pipe_position(char **args);
// int					is_builtin_or_external(t_minishellinfo *all, char *comand, char *absolute_path);
// int					execute_in_pipe(t_list *node);
// int					execute_comand(t_minishellinfo *all, char *comand, char *argv[], char **envp);
// int					execute_in_pipe(t_minishellinfo *all, char **args, int pipe_position);
// void				fill_structures(t_minishellinfo *all, int argc, char **argv, char **envp);


#endif