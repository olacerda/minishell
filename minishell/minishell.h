/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 23:13:23 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/28 06:01:14 by olacerda         ###   ########.fr       */
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
# include <stdbool.h>
# include <sys/select.h>


# define BUFFER_SIZE 25
# define ENV_INCREMENT 10
# define DOT 0
# define DOUBLE_DOT 1
# define DASH 2
# define TILDE 3
# define SLASH 4

typedef struct	s_gnl
{
	int		start;
	int		end;
	int		readbytes;
	char	buffer[BUFFER_SIZE + 1];
}				t_gnl;

typedef enum e_redir_type
{
    REDIR_INPUT = 1,
    REDIR_OUTPUT = 2,
    REDIR_APPEND = 3,
    REDIR_HEREDOC = 4
} 			t_redir_type;

typedef	struct s_redirection
{
	t_redir_type	type;
	char 			*redir_arg;
	struct s_redirection	*next;
}				t_redirection;

typedef struct s_comand
{
	char 			*comand;
	char 			**args;
	t_redirection	*redir;
	struct s_comand	*next;
}				t_comand;

typedef struct s_prefix
{
	char *path;
	char *home;
	char *pwd;
	char *oldpwd;
	char *user;
}				t_prefix;


// typedef	struct	s_states
// {
// 	int	changed_fds;
// 	int	redir_out_append;
// }				t_states;

// typedef struct	s_pipeinfo
// {
// 	int	in;
// 	int	out;
// }				t_pipeinfo;

// typedef struct s_comand_origin
// {
// 	char *absolute_path;
	
// }				t_comand_origin;

typedef struct s_my_envp
{
	char **envp;
	int	size;
	int	capacity;
}				t_env;


typedef int (func_pointer)(char **envp, t_comand *node, t_env *env);

typedef	struct s_comand_origin
{
	func_pointer 	*built_in;
	char *			absolute_path;
}				t_comand_origin;


typedef struct s_minishellinfo
{
	int			argc;
	char 		**argv;
	char		**envp;
	t_prefix 	*prefx;
	t_comand 	*head;
	t_comand	*comand;
	// t_states	*states;
	t_env		*my_env;
	int			node_number;
	int			node_count;
	int			father_pid;
	int			*children_pids;
	int			fd[2];
	int			previous_fd_0;
	int			true_fds[2];
	int			redir_fds[2];
	int			here_doc_fd;
	int			heredoc_last_node;
	int			last_heredoc_redir_node;
}				t_minishellinfo;



// ------------------- Only for faster tests on the main------------
// int				compare_prefix(char *string1, char *string2);
// char				*find_environment_variable(char *prefix, char **envp);
// int				string_lenght(char *string);
// int				clear_string(char *string, int size);
// int				get_next_path(char *path, char *environment_variable, int env_idx, int path_buffer_size);
// int				is_accessible(char *path, char *comand);
// char 			*find_absolute_path(char *environment_variable, char *comand, int prefix_size);
// char 			*get_absolute_path(char *prefix, char *comand, char **envp);
// t_minishellinfo *init_structures(void);
// void				put_error(char *problem);
// void				end_structures(t_minishellinfo *all);
// int				get_all_prefixs(t_prefix *prefix);
// int				append_comand_to_path(char *path, char *comand, int path_idx, int path_buffer_size);
// int					execute_comands(t_minishellinfo *all, char *comand, char *argv[], char **envp);
// int					is_comand(char *comand);
// char 			**create_args(char *string);
// void				clean_args(char **args);
// int					count_args(char **args);
// int					get_pipe_position(char **args);
// int					is_builtin_or_external(t_minishellinfo *all, char *comand, char *absolute_path);
// int					execute_in_pipe(t_list *node);
// int					execute_comands(t_minishellinfo *all, char *comand, char *argv[], char **envp);
// int					execute_in_pipe(t_minishellinfo *all, char **args, int pipe_position);
// void				fill_structures(t_minishellinfo *all, int argc, char **argv, char **envp);


#endif