#ifndef PERMUTATIONS_H
# define PERMUTATIONS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_all
{
	int size;
	char *original;
	char *dup;
}				t_all;

t_all 	*init_structure();
void	end_structure(t_all *all, int status);
int		stringlenght(char *string);
char 	*string_dup(t_all *all, char *string, int size);
void	fill_struct(t_all *all, char *argv[]);
int		swap_last_characters(char *string, int size);
int		print_string(char *string, int size);
int		do_last_double(char *string, int size);
int		increment_letter(int focused, char *original, char *dup, int size);
int		check_for_doubles_left(char *dup, int focused);
int		check_n_swap_right(char *dup, int focused, char temp);
int		order_right_letters(char *dup, int focused);
int 	do_main_loop(char *original, char *string, int size);

#endif