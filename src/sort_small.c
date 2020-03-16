/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboggs <fboggs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 17:40:52 by fboggs            #+#    #+#             */
/*   Updated: 2020/03/16 20:00:34 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int		sorting_two(t_what **storage)
{
	if ((*storage)->stack_b == 2)
	{
		if ((*storage)->head_b->index > (*storage)->tail_b->index)
			s_swap(&(*storage)->head_b, &(*storage), 'b');
		if (is_sorted((*storage)->head_b))
			return (1);
	}
	if ((*storage)->stack_a == 2)
	{
		if ((*storage)->head_a->index > (*storage)->tail_a->index)
			s_swap(&(*storage)->head_a, &(*storage), 'a');
		if (is_sorted((*storage)->head_a))
			return (1);
	}
	return (-1);
}

void	sort_three_case_frst(t_what **strg, t_num **head_tmp, t_num **tail_tmp)
{
	char	c;
	int		head_tmp_next_i;
	int		head_tmp_i;

	c = ((*strg)->curr_stack == 'A') ? 'a' : 'b';
	head_tmp_i = (*head_tmp)->index;
	head_tmp_next_i = (*head_tmp)->next->index;
	if (head_tmp_i > head_tmp_next_i && head_tmp_i < (*tail_tmp)->index)
		s_swap(&(*head_tmp), &(*strg), c);
	else if (head_tmp_i > head_tmp_next_i && head_tmp_i > (*tail_tmp)->index)
	{
		if ((*tail_tmp)->index < (*tail_tmp)->prev->index)
		{
			s_swap(&(*head_tmp), &(*strg), c);
			rr_reverse(&(*head_tmp), &(*tail_tmp), &(*strg));
		}
		else if ((*tail_tmp)->index > (*tail_tmp)->prev->index)
			r_rotate(&(*head_tmp), &(*tail_tmp), &(*strg));
	}
	else if (head_tmp_i < head_tmp_next_i && (*tail_tmp)->index < head_tmp_i)
		rr_reverse(&(*head_tmp), &(*tail_tmp), &(*strg));
	else if (head_tmp_i < head_tmp_next_i && (*tail_tmp)->index > head_tmp_i)
		three_two_one(&(*strg), &(*head_tmp), &(*tail_tmp));
}

int		sorting_three(t_what **storage)
{
	t_num **head_tmp;
	t_num **tail_tmp;

	head_tmp = NULL;
	tail_tmp = NULL;
	if ((*storage)->curr_stack == 'A')
	{
		head_tmp = &(*storage)->head_a;
		tail_tmp = &(*storage)->tail_a;
		if (sort_3_mov(&(*storage), &(*head_tmp), &(*tail_tmp)) == -1)
			return (-1);
	}
	else if ((*storage)->curr_stack == 'B')
	{
		head_tmp = &(*storage)->head_b;
		tail_tmp = &(*storage)->tail_b;
		if (sort_3_mov(&(*storage), &(*head_tmp), &(*tail_tmp)) == -1)
			return (-1);
	}
	return (1);
}

int		sorting_four(t_what **storage)
{
	while ((*storage)->head_a)
	{
		if ((*storage)->head_a->index == 1 || (*storage)->head_a->index == 4)
		{
			push('b', &(*storage));
			break ;
		}
		r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
	}
	if (sorting_three(&(*storage)) == -1)
		return (-1);
	if ((*storage)->head_b->index == 1)
		push('a', &(*storage));
	else if ((*storage)->head_b->index == 4)
	{
		push('a', &(*storage));
		r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
	}
	if (is_sorted((*storage)->head_a) == 1)
		return (1);
	return (-1);
}

int		sorting_five(t_what **storage)
{
	push('b', &(*storage));
	push('b', &(*storage));
	if (sorting_three(&(*storage)) == -1)
		return (-1);
	sorting_alg_five(&(*storage));
	if ((*storage)->tail_a->index < 3)
	{
		while (is_sorted((*storage)->head_a) == -1)
			rr_reverse(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
	}
	else
		while (is_sorted((*storage)->head_a) == -1)
			r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
	if (is_sorted((*storage)->head_a) == 1)
		return (1);
	return (-1);
}
