/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboggs <fboggs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 20:04:29 by fboggs            #+#    #+#             */
/*   Updated: 2020/03/16 20:06:32 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	sorting_alg_five(t_what **storage)
{
	while ((*storage)->stack_b > 0)
	{
		if ((*storage)->head_b->index == (*storage)->head_a->index - 1)
			push('a', &(*storage));
		else if ((*storage)->head_b->next && (*storage)->head_b->next->index ==
			(*storage)->head_a->index - 1)
		{
			s_swap(&(*storage)->head_b, &(*storage), 'b');
			push('a', &(*storage));
		}
		else if ((*storage)->head_b->index == (*storage)->tail_a->index + 1)
		{
			push('a', &(*storage));
			r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
		}
		else if ((*storage)->head_b->next && (*storage)->head_b->next->index ==
			(*storage)->tail_a->index + 1)
		{
			s_swap(&(*storage)->head_b, &(*storage), 'b');
			push('a', &(*storage));
			r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
		}
		else
			r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
	}
}

int		sort_3_mov(t_what **storage, t_num **head_tmp, t_num **tail_tmp)
{
	if ((*storage)->curr_stack == 'A')
	{
		if (is_sorted((*storage)->head_a) == 1)
			return (1);
	}
	else if ((*storage)->curr_stack == 'B')
	{
		if (is_sorted((*storage)->head_b) == 1)
			return (1);
	}
	sort_three_case_frst(&(*storage), &(*head_tmp), &(*tail_tmp));
	if (is_sorted(*head_tmp) == 1)
		return (1);
	return (-1);
}

void	push_alg(t_num **to, t_num **from, t_num *tmp_next, t_num *tmp)
{
	if (*to == NULL)
	{
		*to = *from;
		if (tmp_next)
			tmp_next->prev = NULL;
		(*to)->prev = NULL;
		(*to)->next = NULL;
		*from = tmp_next;
	}
	else
	{
		if (tmp_next)
			tmp_next->prev = NULL;
		tmp->prev = NULL;
		tmp->next = *to;
		(*to)->prev = tmp;
		*to = tmp;
		*from = tmp_next;
	}
}
