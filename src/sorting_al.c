/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_al.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboggs <fboggs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 19:35:03 by fboggs            #+#    #+#             */
/*   Updated: 2020/03/15 15:10:59 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	usual_split_stack(t_what **strg, int count, t_num *tmp)
{
	while (count--)
	{
		if ((tmp)->index <= (*strg)->mid && (tmp)->index >= (*strg)->next)
			if_small_index_in_usual_alg_split(&(*strg), &(tmp));
		else
		{
			if ((*strg)->curr_stack == 'A')
				r_rotate(&(*strg)->head_a, &(*strg)->tail_a, &(*strg));
			else
			{
				push('a', &(*strg));
				(*strg)->head_a->flag_st_b = (*strg)->flag;
				while ((*strg)->head_a->index == (*strg)->next)
					rotate_while_heada_next(&(*strg));
			}
		}
		(tmp) = ((*strg)->curr_stack == 'A') ? ((*strg)->head_a) :
				((*strg)->head_b);
	}
}

void	split_stack(t_what **storage)
{
	t_num	*tmp;
	int		i;
	int		count;

	i = 0;
	what_curr_and_max_min(&(*storage), &i);
	tmp = ((*storage)->curr_stack == 'A') ? ((*storage)->head_a) :
			((*storage)->head_b);
	count = how_much_nonsort(&(*storage), i);
	if (count <= 4 && (*storage)->curr_stack == 'A')
		if_small_block_in_a(&(*storage), count, tmp);
	else if ((*storage)->stack_b == 0 && (*storage)->flag > 0)
	{
		while (count-- && tmp)
		{
			if ((tmp->flag_st_b == i || tmp->flag_st_b == 0) && tmp->sort == 0)
				rotate_if_next(&(*storage), &(tmp));
			tmp = ((*storage)->curr_stack == 'A') ? ((*storage)->head_a) :
				((*storage)->head_b);
		}
		while ((*storage)->head_a->index == (*storage)->next)
			rotate_while_heada_next(&(*storage));
	}
	else
		usual_split_stack(&(*storage), count, tmp);
}

int		push_from_b_if_sort(t_what **storage)
{
	t_num *tmp;

	if (is_sorted((*storage)->head_b) == 1)
	{
		while ((*storage)->stack_b > 0)
		{
			push('a', &(*storage));
			(*storage)->head_a->flag_st_b = (*storage)->flag;
			tmp = (*storage)->head_a;
			while (tmp->index == (*storage)->next)
			{
				rotate_while_heada_next(&(*storage));
				tmp = (*storage)->head_a;
			}
		}
	}
	else
		return (-1);
	return (1);
}

int		sort_al_small(t_what **storage)
{
	if ((*storage)->stack_b == 3)
	{
		(*storage)->curr_stack = 'B';
		sorting_three(&(*storage));
		if (push_from_b_if_sort(&(*storage)) == -1)
			return (-1);
	}
	else if ((*storage)->stack_b == 2)
	{
		sorting_two(&(*storage));
		if (push_from_b_if_sort(&(*storage)) == -1)
			return (-1);
	}
	else if ((*storage)->stack_b == 1)
	{
		if (push_from_b_if_sort(&(*storage)) == -1)
			return (-1);
	}
	return (1);
}

int		sorting_al(t_what **storage)
{
	if ((*storage)->stack_a <= 5)
	{
		(*storage)->curr_stack = 'A';
		if ((*storage)->stack_a == 5)
			sorting_five(&(*storage));
		else if ((*storage)->stack_a == 4)
			sorting_four(&(*storage));
		else if ((*storage)->stack_a == 3)
			sorting_three(&(*storage));
		else if ((*storage)->stack_a == 2)
			sorting_two(&(*storage));
		return (1);
	}
	while (is_sorted_final(*storage) == -1)
	{
		split_stack(&(*storage));
		while ((*storage)->stack_b > 3)
			split_stack(&(*storage));
		if ((*storage)->stack_b <= 3)
		{
			if (sort_al_small(&(*storage)) == -1)
				return (-1);
		}
	}
	return (1);
}
