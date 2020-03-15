/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboggs <fboggs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 15:08:30 by fboggs            #+#    #+#             */
/*   Updated: 2020/03/15 15:10:41 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	three_two_one(t_what **storage, t_num **head_tmp, t_num **tail_tmp)
{
	if ((*storage)->curr_stack == 'A')
		s_swap(&(*head_tmp), &(*storage), 'a');
	else if ((*storage)->curr_stack == 'B')
		s_swap(&(*head_tmp), &(*storage), 'b');
	r_rotate(&(*head_tmp), &(*tail_tmp), &(*storage));
}

int		is_sorted_final(t_what *storage)
{
	t_num	*tmp;
	int		prev_index;

	if (storage->head_b != NULL)
		return (-1);
	else if (storage->head_a == NULL)
		return (-1);
	tmp = storage->head_a->next;
	prev_index = storage->head_a->index;
	while (tmp)
	{
		if (prev_index > tmp->index)
			return (-1);
		prev_index = tmp->index;
		tmp = tmp->next;
	}
	return (1);
}

int		is_sorted(t_num *head)
{
	t_num	*tmp;
	int		prev_index;

	tmp = head->next;
	prev_index = head->index;
	while (tmp)
	{
		if (prev_index > tmp->index)
			return (-1);
		prev_index = tmp->index;
		tmp = tmp->next;
	}
	return (1);
}

int		how_much_nonsort(t_what **storage, int i)
{
	t_num	*tmp;
	int		len;

	len = 0;
	tmp = (*storage)->curr_stack == 'A' ? (*storage)->head_a :
		(*storage)->head_b;
	while (tmp)
	{
		if (tmp->sort == 0 && tmp->flag_st_b == i)
			len += 1;
		tmp = tmp->next;
	}
	return (len);
}

void	what_curr_and_max_min(t_what **strg, int *i)
{
	if ((*strg)->curr_stack == 0 || (*strg)->stack_b == 0)
	{
		(*strg)->curr_stack = 'A';
		if ((*strg)->flag > 0)
			(*i) = (*strg)->head_a->flag_st_b;
		(*strg)->next = find_min(&(*strg)->head_a, *i);
		(*strg)->max = find_max(&(*strg)->head_a, *i);
		if ((*strg)->flag == 0)
			(*strg)->mid = ((*strg)->max / 2) + (*strg)->next;
		else
			(*strg)->mid = ((*strg)->max - (*strg)->next) / 2 + (*strg)->next;
	}
	else if ((*strg)->curr_stack != 0)
	{
		(*strg)->curr_stack = 'B';
		(*i) = (*strg)->head_b->flag_st_b;
		(*strg)->next = find_min(&(*strg)->head_b, *i);
		(*strg)->max = find_max(&(*strg)->head_b, *i);
		if ((*strg)->flag > 0)
			(*strg)->mid = ((*strg)->max - (*strg)->next) / 2 + (*strg)->next;
		else
			(*strg)->mid = ((*strg)->max / 2) + (*strg)->next;
		(*strg)->flag += 1;
	}
}
