/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_if.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboggs <fboggs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 15:12:14 by fboggs            #+#    #+#             */
/*   Updated: 2020/03/15 15:13:34 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	rotate_if_next(t_what **storage, t_num **tmp)
{
	if ((*tmp)->index == (*storage)->next)
		rotate_while_heada_next(&(*storage));
	else
		push('b', &(*storage));
}

void	rotate_while_heada_next(t_what **storage)
{
	r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
	(*storage)->tail_a->sort = 1;
	(*storage)->next += 1;
}

void	if_small_index_in_usual_alg_split(t_what **strg, t_num **tmp)
{
	if ((*strg)->curr_stack == 'A')
		push('b', &(*strg));
	else
	{
		if ((*tmp)->index == (*strg)->next)
		{
			push('a', &(*strg));
			rotate_while_heada_next(&(*strg));
		}
		else
			r_rotate(&(*strg)->head_b, &(*strg)->tail_b, &(*strg));
	}
}

void	if_small_block_in_a(t_what **storage, int count, t_num *tmp)
{
	while (count-- && tmp)
	{
		rotate_if_next(&(*storage), &(tmp));
		tmp = ((*storage)->curr_stack == 'A') ? ((*storage)->head_a) :
			((*storage)->head_b);
	}
}
