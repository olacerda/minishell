/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 23:13:23 by otlacerd          #+#    #+#             */
/*   Updated: 2026/03/05 16:30:56 by olacerda         ###   ########.fr       */
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
# include <signal.h>
# include <errno.h>


# define BUFFER_SIZE 25
# define ENV_INCREMENT 10
# define FAIL -1
# define NOT_FOUND NULL
# define FOUND NULL !=
# define BACKUP_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

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
}				t_redir;

typedef struct s_comand
{
	char 			*comand;
	char 			**args;
	t_redir	*redir;
	struct s_comand	*next;
}				t_cmd;

typedef struct s_my_envp
{
	char	**envp;
	int		size;
	int		capacity;
}				t_env;

typedef struct s_fds
{
	int		previous_0;
	int		pipe[2];
	int		redir[2];
	int		here_doc;
	int		std_backup[2];
}				t_fds;

typedef struct s_all
{
	int		argc;
	char 	**argv;
	char	**envp;
	t_cmd 	*head;
	t_env	*my_env;
	t_fds	*fds;
	char	buffer[PATH_MAX];
	int		exit_status;
	int		env_status;
	int		node_number;
	int		lst_size;
	int		father_pid;
	int		*children_pids;
	int		heredoc_last_node;
	int		last_heredoc_redir_node;
}				t_all;

typedef int (func_ptr)(t_all *all, t_cmd *node, t_env *env, char *buffer);

typedef	struct s_origin
{
	func_ptr	*built_in;
	char *		abs_path;
}				t_origin;

#endif