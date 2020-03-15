/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboggs <fboggs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 17:59:01 by fboggs            #+#    #+#             */
/*   Updated: 2020/03/15 17:21:57 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "ft_printf.h"

typedef struct		s_num{
	int				num;
	int				index;
	int				sign;
	int				flag;
	int				sort;
	int				flag_st_b;

	struct s_num	*next;
	struct s_num	*prev;
}					t_num;

typedef struct		s_what{
	t_num			*head_a;
	t_num			*head_b;
	t_num			*tail_a;
	t_num			*tail_b;

	char			curr_stack;

	int				flag_kol_op;
	int				stack_a;
	int				stack_b;
	int				flag_v;
	int				next;
	int				max;
	int				mid;
	int				flag;
	int				argc;
	int				push_swap;
}					t_what;

int					save_argv(const char *argv, t_num **num, t_what **storage);
t_what				*new_what();
t_num				*new_num(void);
void				print_stacks(t_num *head_a, t_num *head_b);
void				final_free(t_what **storage, t_num **num);
void				free_stack_a(t_what **storage);
void				free_num(t_num *tmp, t_num *tmp_prev);
void				free_stack_b(t_what **storage);
int					index_array(t_num **head);
int					indexing(t_num **tmp, t_num **head, int *index,
		long long *tmp_min);
int					check_dup(long long *min, long long *t_mn,
		t_num **n_mn, int *i);
int					check_char(char c, const char **av);
void				split_stack(t_what **storage);
int					save_correct_av(t_what **strg, t_num **n, const char **av,
		int f);
int					save_if_not_empty(t_num **n, const char **av, int *f,
		t_what **sg);
int					save_av_if_empty(t_what **sg, const char **av, int *f,
		t_num **n);
int					what_do_to_save_av(t_what **sg, t_num **n, const char **a,
		int f);

int					s_swap(t_num **head, t_what **storage, char c);
int					r_rotate(t_num **head, t_num **tail, t_what **storage);
int					push(char c, t_what **storage);
void				push_alg(t_num **to, t_num **from, t_num *tmp_next,
		t_num *tmp);
void				push_alg2(char c, t_what **storage);
int					rr_reverse(t_num **head, t_num **tail, t_what **storage);

int					is_sorted_final(t_what *storage);
int					is_sorted(t_num *head);

int					sorting_three(t_what **storage);
void				sort_three_case_frst(t_what **stg, t_num **hd_tmp,
		t_num **tl_tmp);
void				three_two_one(t_what **storage, t_num **head_tmp,
		t_num **tail_tmp);
int					sorting_five(t_what **storage);
int					sort_3_mov(t_what **storage, t_num **head_tmp,
		t_num **tail_tmp);
int					sorting_two(t_what **storage);
int					sorting_four(t_what **storage);

int					find_min(t_num **stack, int i);
int					find_max(t_num **stack, int i);

int					how_much_nonsort(t_what **storage, int i);
int					push_from_b_if_sort(t_what **storage);

int					sorting_al(t_what **storage);
void				what_curr_and_max_min(t_what **strg, int *i);

int					new_num_storage(t_num **num, t_what **storage);
int					sort(t_what **storage);
int					sort_al_small(t_what **storage);

void				rotate_while_heada_next(t_what **storage);
void				rotate_if_next(t_what **storage, t_num **tmp);
void				if_small_block_in_a(t_what **storage, int count,
		t_num *tmp);
void				usual_split_stack(t_what **strg, int count, t_num *tmp);
int					argv_save(t_what **storage, char **argv, int i,
		t_num **num);
void				if_small_index_in_usual_alg_split(t_what **strg,
		t_num **tmp);

int					parse_args_if_swap(char **line, t_what **storage);
int					parse_args_if_rotate(char **line, t_what **strg);
int					parse_args_if_rev_rotate(char **line, t_what **strg);
int					parse_args(t_what *strg, char *line);
int					valid_and_parse_args(t_what *storage);
int					argv_save_checker(t_what **storage, char **argv, int i,
		t_num **new);
int					main_alg_checker(t_what **storage, t_num **num, int argc,
		char **argv);
int					ps_atoi(const char *str, int minus);
void				save_if_minus(const char **av, int *flag, int *minus);

#endif
