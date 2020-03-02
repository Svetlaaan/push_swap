#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

//# include "libft.h"

#include "../printf/inc/ft_printf.h"

typedef struct 		s_num{
    int             num;
    int             index;
    int             block;
    int 			podblock;
    int				sign;

    struct s_num	*next;
    struct s_num	*prev;
}               	t_num;

typedef struct 		s_what{
    t_num 			*head_a;
    t_num 			*head_b;
    t_num 			*tail_a;
    t_num 			*tail_b;

    char			curr_stack;

    int 			flag_kol_op;
    int             stack_a;
    int             stack_b;
    int 			flag_v;
//    int 			max_index_stack_a;
//    int 			min_index_stack_a;
  //  int 			third_step_width; // кол-во чисел в 3 блоке - самых больших  чисел
}                   t_what;

int         save_argv(const char *argv, t_num **num, t_what **storage);
t_what      *new_what();
t_num		*new_num(void);

void	    print_stacks(t_num *head_a, t_num *head_b);
void 		final_free(t_what **storage, t_num **num);
int 		index_array(t_num **head);
int     	check_char(char c);

int 		s_swap(t_num **head, t_what **storage, char c);
int         r_rotate(t_num **head, t_num **tail, t_what **storage);
int         push(char c, t_what **storage);
int 		rr_reverse(t_num **head, t_num **tail, t_what **storage);
void		sort_by_blocks(t_what **storage);
void    	set_block(t_what **storage);
int			is_sorted_final(t_what *storage);
int 	is_sorted_rev(t_num *head);
int 	sort_3_mov_rev(t_what **storage, t_num **head_tmp, t_num **tail_tmp);

int 		sorting(t_what **storage);
int 	main_sort(t_what **storage);
int 		is_sorted(t_num *head);
int 		sorting_three(t_what **storage);
int 		sorting_five(t_what **storage);
int 		sorting_two(t_what **storage);
int 		sorting_four(t_what **storage);

int len_of_block(t_what **storage, int num);

#endif //PUSH_SWAP_PUSH_SWAP_H
