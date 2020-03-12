#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H
#include "ft_printf.h"

typedef struct 		s_num{
    int             num;
    int             index;
    int				sign; // случай когда число -1
    int             flag; // если отрицательное
    int 			sort;
    int 			flag_st_b; // сколько раз число было в стеке В

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
    int 			next;
    int 			max;
    int 			mid;
    int				flag; // сколько раз стэк В делился
    int				argc;
}                   t_what;

/* all */
int         save_argv(const char *argv, t_num **num, t_what **storage);
t_what      *new_what();
t_num		*new_num(void);
void	    print_stacks(t_num *head_a, t_num *head_b);
void 		final_free(t_what **storage, t_num **num);
void		free_stack_a(t_what **storage);
void		free_num(t_num *tmp, t_num *tmp_prev);
void		free_stack_b(t_what **storage);
int 		index_array(t_num **head);
int     	check_char(char c);
void    	split_stack(t_what **storage);
int			save_correct_av(t_what **strg, t_num **num, const char **av, int flag);
int			save_if_not_empty(t_num **n, const char **av, int *flag, t_what **strg);
int			save_av_if_empty(t_what **strg, const char **av, int *flag, t_num **num);
int			what_do_to_save_av(t_what **strg, t_num **n, const char **av, int flag);

/* operations */
int 		s_swap(t_num **head, t_what **storage, char c);
int         r_rotate(t_num **head, t_num **tail, t_what **storage);
int         push(char c, t_what **storage);
void		push_alg(t_num **to, t_num **from, t_num *tmp_next, t_num *tmp);
void		push_alg2(char c, t_what **storage);
int 		rr_reverse(t_num **head, t_num **tail, t_what **storage);

/* check sort */
int			is_sorted_final(t_what *storage);
int 		is_sorted(t_num *head);

/* push swap */

/* sort small */
int 		sorting_three(t_what **storage);
int 		sorting_five(t_what **storage);
int 		sorting_two(t_what **storage);
int 		sorting_four(t_what **storage);

int			find_min(t_num **stack, int i);
int			find_max(t_num **stack, int i);

int			how_much_nonsort(t_what **storage, int i);
int			push_from_b_if_sort(t_what **storage);

int 		sorting_al(t_what **storage);
void    	what_curr_and_max_min(t_what **strg, int *i);//, int *mid);

int 		new_num_storage(t_num **num, t_what **storage);
int			sort(t_what **storage);
int 		sort_al_small(t_what **storage);

void 		rotate_while_heada_next(t_what **storage);
void		rotate_if_next(t_what **storage, t_num **tmp);
void		if_small_block_in_a(t_what **storage, int count, t_num *tmp);
void		usual_split_stack(t_what **strg, int count, t_num *tmp);
int 		argv_save(t_what **storage, char **argv, int i, t_num **num);
void		if_small_index_in_usual_alg_split(t_what **strg, t_num **tmp);

#endif
