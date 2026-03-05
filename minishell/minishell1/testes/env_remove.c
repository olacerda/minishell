/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 05:47:11 by otlacerd          #+#    #+#             */
/*   Updated: 2026/02/14 05:47:36 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ---------------------- Teste My_Env--------------
		printf("################  Envp original:###################\n\n");
		int lin = 0;
		while (all->my_env->envp[lin])
			printf("%s\n", all->my_env->envp[lin++]);
		printf("capacity: %d   size: %d\n\n", all->my_env->capacity, all->my_env->size);

		
		printf("################  My personal envp: ###################### \n\n");
		env_add(all->my_env, all->my_env->size, "Primeira->", "Tchutchu belesba?");
		env_add(all->my_env, all->my_env->size, "Segunda->", "Tchutchu belesba?");
		env_add(all->my_env, all->my_env->size, "Terceira->", "Tchutchu belesba?");
		env_add(all->my_env, all->my_env->size, "Quarta->", "Meu jovem");
		env_add(all->my_env, all->my_env->size, "Quinta->", "Meu jovem");
		env_add(all->my_env, all->my_env->size, "Sexta->", "Meu jovem");
		env_add(all->my_env, all->my_env->size, "Setima->", "Abacaxi com limao");
		env_add(all->my_env, all->my_env->size, "Oitava->", "Abacaxi com limao");
		env_add(all->my_env, all->my_env->size, "Nona->", "Abacaxi com limao");
		env_add(all->my_env, all->my_env->size, "Decima->", "Abacaxi com limao");
		env_add(all->my_env, all->my_env->size, "Onze->", "Abacaxi com limao");
		env_add(all->my_env, all->my_env->size, "Doze->", "Abacaxi com limao");
		env_add(all->my_env, all->my_env->size, "Treze->", "Abacaxi com limao");
		env_add(all->my_env, all->my_env->size, "Quatorze->", "Abacaxi com limao");
		env_add(all->my_env, all->my_env->size, "Quinze->", "Abacaxi com limao");
		env_add(all->my_env, all->my_env->size, "Dezesseis->", "Abacaxi com limao");
		env_add(all->my_env, all->my_env->size, "Dezessete->", "Abacaxi com limao");
		env_add(all->my_env, all->my_env->size, "Dezoito->", "Abacaxi com limao");
		env_add(all->my_env, all->my_env->size, "Dezenove->", "Abacaxi com limao");
		env_add(all->my_env, all->my_env->size, "Vinte->", "Abacaxi com limao");
		env_add(all->my_env, all->my_env->size, "Vinteum->", "Abacaxi com limao");
		env_add(all->my_env, all->my_env->size, "Vintedois->", "Abacaxi com limao");
		env_add(all->my_env, all->my_env->size, "Vintetres->", "Abacaxi com limao");
		lin = 0;
		while (all->my_env->envp[lin])
			printf("%s\n", all->my_env->envp[lin++]);	
		printf("capacity: %d   size: %d\n\n", all->my_env->capacity, all->my_env->size);

		env_remove(all->my_env, "Primeira->");
		env_remove(all->my_env, "Segunda->");
		env_remove(all->my_env, "Treze->");
		// printf("After first removal##################\n\n");
		// lin = 0;
		// while (all->my_env->envp[lin])
		// 	printf("%s\n", all->my_env->envp[lin++]);
		// printf("capacity: %d   size: %d\n\n", all->my_env->capacity, all->my_env->size);

		env_remove(all->my_env, "Quatorze->");
		env_remove(all->my_env, "Quinze->");
		env_remove(all->my_env, "Dezesseis->");
		// lin = 0;
		// while (all->my_env->envp[lin])
		// 	printf("%s\n", all->my_env->envp[lin++]);
		// printf("capacity: %d   size: %d\n\n", all->my_env->capacity, all->my_env->size);
		env_remove(all->my_env, "Dezessete->");
		env_remove(all->my_env, "Dezoito->");
		env_remove(all->my_env, "Dezenove->");
		env_remove(all->my_env, "Vinte->");
		env_remove(all->my_env, "Vinteum->");
		env_remove(all->my_env, "Vintedois->");
		env_remove(all->my_env, "Vintetres->");

		printf("########### After Removal ##############\n");
		lin = 0;
		while (all->my_env->envp[lin])
			printf("%s\n", all->my_env->envp[lin++]);
		printf("capacity: %d   size: %d\n\n", all->my_env->capacity, all->my_env->size);
		exit(1);
// // ------------------------------------------------
