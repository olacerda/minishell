/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 02:20:46 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/28 06:34:09 by olacerda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <core_execution.h>
#include <data.h>
#include <utils.h>
#include <built-ins.h>

int	main(int argc, char *argv[], char **envp)
{
	t_minishellinfo *all;
	t_comand		*node;
	char 			**args;
	char 			*line;
	int				pid;
	
	all = init_structures();
	if (!all)
		return (1);
	line = NULL;
	pid = getpid();
	all->father_pid = pid;
	all->my_env->envp = NULL;
	while (1)
	{		
		fill_structures(all, argc, argv, envp);

		
// --------------------------- Teste ENV -------------------------------------------------

// // // --------------------- ADD/REMOVE ------------------------------------------------
// 		printf("\n\n################  My personal ENV:###################\n\n");
// 		int lin = 0;
// 		while (all->my_env->envp[lin])
// 			printf("%s\n", all->my_env->envp[lin++]);
// 		printf("capacity: %d   size: %d\n\n", all->my_env->capacity, all->my_env->size);
		
// 		env_add(all->my_env, all->my_env->size, "Primeira->", "Tchutchu belesba?");
// 		env_add(all->my_env, all->my_env->size, "Segunda->", "Meu jovem");
// 		env_add(all->my_env, all->my_env->size, "Terceira->", "Abacaxi com limao");
// 		env_add(all->my_env, all->my_env->size, "um->", "Abacaxi com limao");
// 		env_add(all->my_env, all->my_env->size, "dois->", "Abacaxi com limao");
// 		env_add(all->my_env, all->my_env->size, "tres->", "Abacaxi com limao");
// 		env_add(all->my_env, all->my_env->size, "quatro->", "Abacaxi com limao");
// 		env_add(all->my_env, all->my_env->size, "cinco->", "Abacaxi com limao");
// 		env_add(all->my_env, all->my_env->size, "Agora deu um carai memo->", "PiririPompom");
// 		env_add(all->my_env, all->my_env->size, "Agora deu um carai memo->", "PiririPompom");
// 		env_add(all->my_env, all->my_env->size, "Agora deu um carai memo->", "PiririPompom");

// 		printf("\n\n################### After addition ###############\n\n");
// 		// lin = 87;
// 		lin = 0;
// 		while (all->my_env->envp[lin])
// 			printf("%s\n", all->my_env->envp[lin++]);
// 		printf("capacity: %d   size: %d\n\n", all->my_env->capacity, all->my_env->size);
		
// 		env_remove(all->my_env, "Agora deu um carai memo->");
// 		env_remove(all->my_env, "Agora deu um carai memo->");
// 		env_remove(all->my_env, "Agora deu um carai memo->");
// 		env_remove(all->my_env, "Primeira->");
// 		env_remove(all->my_env, "cinco->");
// 		env_remove(all->my_env, "Segunda->");
// 		// env_remove(all->my_env, "Terceira->");
// 		env_remove(all->my_env, "um->");
// 		env_remove(all->my_env, "dois->");
// 		env_remove(all->my_env, "tres->");
// 		env_remove(all->my_env, "quatro->");
		

// 		printf("\n\n########### After Removal ##############\n\n");
// 		// lin = 87;
// 		lin = 0;
// 		while (all->my_env->envp[lin])
// 			printf("%s\n", all->my_env->envp[lin++]);
// 		printf("capacity: %d   size: %d\n\n", all->my_env->capacity, all->my_env->size);
// 		exit(1);
// // // ----------------------------------------------------------------------------------------

// //// --------------------------------- SHOW -----------------------------------------------
// 		env_show(all->my_env->envp);
// 		exit(1);
// // // ---------------------------------------------------------------------------------------

// // -----------------------------------FIND --------------------------------------------------
// 		int	env_line;
// 		env_line = env_find("PATH=", all->my_env->envp);
// 		if (env_line == -1)
// 			return (put_error("Error\nFailed to get envp line with env_find\n\n"), 1);
// 		printf("%s\n", all->my_env->envp[env_line]);
// 		exit(1);
// // -------------------------------------------------------------------------------------------

// //  --------------------------------  UPDATE --------------------------------------------------
// 		env_update(all->my_env->envp, "PATH=", "PIRIRIPOMPOM ################################");
// 		env_update(all->my_env->envp, "TERM_PROGRAM=", "HUMMMM HUMM Huu HUUU #####");
// 		if (!env_update(all->my_env->envp, "e pra falhar", "_______________________________________________"))
// 			printf("\nfaiou\n\n");
// 		env_show(all->my_env->envp);
// 		exit(1);
// //----------------------------------------------------------------------------------------------------

// // ---------------------------------------- FREE --------------------------------------------------

// 		if (!env_show(all->my_env->envp))
// 			return (1);
// 		printf("\nPrintou com sucesso\n\n");
// 		env_free(all->my_env->envp, 0);
		
// // --------------------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------------------

		line = readline("minishell> ");
		if (!line)
			break ;
		args = create_args(line);
		
// //-------------------Imprime o SPLIT-------------------------------------
		// int line2 = 0;
		// printf("*****split*****: \n");
		// while (args[line2] != NULL)
		// 	printf("%s\n", args[line2++]);
		// write(1, "\n\n\n", 3);
// 		exit(1);
// //---------------123---------------------------------------------------------



		all->head = create_comand_list(args, all);

		// printf("last node: %d     last redir: %d\n\n", all->heredoc_last_node, all->last_heredoc_redir_node);
		// exit(1);

// //------------------------Imprime a LINKED-LIST----------------------------		
		// printf("*****linked-list: ***** \n");
		// int	node_nbr = 1;
		// int	redir_nbr = 1;
		// while (all->head != NULL)
		// {
		// 	printf("####NODE#### %d\n", node_nbr++);
		// 	printf("COMAND: %s\n", all->head->comand);
		// 	int line2;
		// 	line2 = 0;
		// 	while (all->head->args[line2])
		// 		printf("args:----%s\n", all->head->args[line2++]);
		// 	printf("\nREDIRECOES:\n");
		// 	if (all->head->redir == NULL)
		// 		printf("NULL\n");
		// 	while (all->head->redir != NULL)
		// 	{
		// 		printf("%d\n", redir_nbr++);
		// 		printf("type: %d\narg: %s\n\n", all->head->redir->type, all->head->redir->redir_arg);
		// 		all->head->redir = all->head->redir->next;
		// 	}
		// 	printf("\n\n");
		// 	all->head = all->head->next;
		// }
		// write(1, "\n\n", 2);
		// exit(1);
// //-------------------------------------------------------------------------		

		create_buffer_children_pids(&all->children_pids, all->node_count);
		node = all->head;
		all->node_number = 0;
		execute_all_heredocs(all);
		execute_comands(all, node, argv, envp);
		if (all->children_pids)
			free(all->children_pids);
		restore_original_fds(all, 1);
		if (all->here_doc_fd != -1)
			close(all->here_doc_fd);
		free(line);
	}
	return (0);
}
