/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 02:43:11 by otlacerd          #+#    #+#             */
/*   Updated: 2026/03/02 15:58:16 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <data.h>
#include <built-ins.h>

t_minishellinfo *init_structures(void)
{
	t_minishellinfo *all;

	all = malloc(sizeof(t_minishellinfo));
	if (!all)
		return (put_error("Error\nFailed to allocate struct 'ALL'\n"), end_structures(all, 1), NULL);
	*all = (t_minishellinfo){0};
	all->prefx = malloc(sizeof(t_prefix));
	if (!all->prefx)
		return (put_error("Error\nFailed to allocate struct 'prefx'\n"), end_structures(all, 1), NULL);
	*all->prefx = (t_prefix){0};
	all->my_env = malloc(sizeof(t_env));
	if (!all->my_env)
		return (put_error("Error\nFailed to allocate all->my_env in init_structs\n"), end_structures(all, 1), NULL);
	*(all->my_env) = (t_env){0};
	return (all);
}

int	fill_structs_on_loop(t_minishellinfo *all)
{
	if (!all || !all->true_fds)
		return (0);
	all->head = NULL;
	all->comand = NULL;
	all->node_number = 0;
	all->node_count = 0;
	all->father_pid = -1;
	all->children_pids = NULL;
	all->pipe_fd[0] = 0;
	all->pipe_fd[1] = 0;
	if (!restore_original_fds(all))
		return (end_structures(all, 1), exit (1), 0);
	all->redir_fds[0] = STDIN_FILENO;
	all->redir_fds[1] = STDOUT_FILENO;
	all->prev_fd_0 = -1;
	all->heredoc_last_node = 0;
	all->heredoc_last_node = 0;
	all->here_doc_fd = -1;
	return (1);
}

int	fill_structures(t_minishellinfo *all, int argc, char **argv, char **envp)
{
	if (!all || !argc || !argv || !envp)
		return (0);
	// printf("fill_structs\n\n");
	all->father_pid = getpid();
	all->argv = argv;
	all->envp = envp;
	all->argc = argc;
	if (all->prefx != NULL)
	{		
		if (!get_all_prefixs(all->prefx))
			return (end_structures(all, 1), exit (1), 0);
	}
	all->exit_status = -1;
	all->head = NULL;
	all->comand = NULL;
	all->node_number = 0;
	all->node_count = 0;
	all->father_pid = -1;
	all->children_pids = NULL;
	all->pipe_fd[0] = 0;
	all->pipe_fd[1] = 0;
	if (!save_original_fds(all->true_fds))
		return (end_structures(all, 1), exit (1), 0);
	all->redir_fds[0] = STDIN_FILENO;
	all->redir_fds[1] = STDOUT_FILENO;
	all->prev_fd_0 = -1;
	all->heredoc_last_node = 0;
	all->heredoc_last_node = 0;
	all->here_doc_fd = -1;
	if (!assign_env_struct(all))
		return (end_structures(all, 1), exit (1), 0);
	return (1);
}

void	end_structures(t_minishellinfo *all, int flag)
{
	if (!all)
		return ;
	unlink("/tmp/minishell_std_storage");
	// if (!!unlink("/tmp/minishell_std_storage"))
	// 	perror("unlink");
	destroy_fds(all, 0);
	if (all->head)
		comand_lstclear(&all->head, del);
	if (all->children_pids)
		free(all->children_pids);
	if (flag == 1)
	{
		destroy_fds(all, 1);
		if (all->prefx)
			free(all->prefx);
		if ((all->my_env) && (all->my_env->envp))
		{
			env_free(all->my_env->envp, 0);
			free(all->my_env);
		}
		free(all);
	}
}

int	close_fd(int *fd)
{
	if (!fd)
		return (0);
	if (*fd >= 0)
		close (*fd);
	*fd = -1;
	return (1);
}

int	destroy_fds(t_minishellinfo *all, int flag)
{
	if (!all)
		return (0);
	close_fd(&all->here_doc_fd);
	close_fd(&all->pipe_fd[0]);
	close_fd(&all->pipe_fd[1]);
	close_fd(&all->redir_fds[0]);
	close_fd(&all->redir_fds[1]);
	if (flag == 1)
	{
		close_fd(&all->true_fds[0]);
		close_fd(&all->true_fds[1]);
	}
	return (1);
}

int	restore_original_fds(t_minishellinfo *all)
{
	if (!all)
		return (0);
	// printf("restore_original_fds\n\n");
	all->redir_fds[0] = STDIN_FILENO;
	all->redir_fds[1] = STDOUT_FILENO;
	all->pipe_fd[1] = -1;
	all->pipe_fd[0] = -1;
	dup2(all->true_fds[0], all->redir_fds[0]);
	dup2(all->true_fds[1], all->redir_fds[1]);
	return (1);
}
