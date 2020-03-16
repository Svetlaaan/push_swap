/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboggs <fboggs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 19:49:06 by fboggs            #+#    #+#             */
/*   Updated: 2020/03/16 20:00:34 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	push_alg2(char c, t_what **storage)
{
	if (c == 'a')
	{
		(*storage)->stack_a += 1;
		(*storage)->stack_b -= 1;
		if ((*storage)->stack_b == 0)
			(*storage)->tail_b = NULL;
		((*storage)->push_swap == 1) ? ft_printf("pa\n") : 0;
	}
	else if (c == 'b')
	{
		(*storage)->stack_a -= 1;
		(*storage)->stack_b += 1;
		if ((*storage)->stack_a == 0)
			(*storage)->tail_a = NULL;
		((*storage)->push_swap == 1) ? ft_printf("pb\n") : 0;
	}
}

int		push(char c, t_what **storage)
{
	t_num **from;
	t_num **to;
	t_num *tmp;
	t_num *tmp_next;

	from = ((c == 'a') ? (&(*storage)->head_b) : &(*storage)->head_a);
	to = ((c == 'a') ? (&(*storage)->head_a) : &(*storage)->head_b);
	if (*from)
	{
		tmp = *from;
		tmp_next = (*from)->next;
		push_alg(&(*to), &(*from), tmp_next, tmp);
		push_alg2(c, &(*storage));
		if ((*storage)->stack_b == 1)
			(*storage)->tail_b = (*storage)->head_b;
		if ((*storage)->stack_a == 1)
			(*storage)->tail_a = (*storage)->head_a;
		(*storage)->flag_kol_op += 1;
	}
	if ((*storage)->flag_v == 1)
		output_stacks(&(*storage));
	return (1);
}

int		s_swap(t_num **head, t_what **storage, char c)
{
	t_num	*tmp;
	t_num	*tmp_next;

	if ((*head) && (*head)->next)
	{
		tmp = *head;
		tmp_next = (*head)->next->next;
		*head = (*head)->next;
		(*head)->prev = NULL;
		tmp->next = (*head)->next;
		(*head)->next = tmp;
		tmp->prev = (*head);
		if (tmp_next)
			tmp_next->prev = (*head)->next;
		if ((*storage)->stack_a == 2 && c == 'a')
			(*storage)->tail_a = (*head)->next;
		else if ((*storage)->stack_b == 2 && c == 'b')
			(*storage)->tail_b = (*head)->next;
		(*storage)->flag_kol_op += 1;
		if ((*storage)->push_swap == 1)
			(c == 'a') ? (ft_printf("sa\n")) : (ft_printf("sb\n"));
	}
	if ((*storage)->flag_v == 1)
		output_stacks(&(*storage));
	return (1);
}

int		r_rotate(t_num **head, t_num **tail, t_what **storage)
{
	t_num	*tmp;
	int		curr;

	tmp = *head;
	if ((*storage)->curr_stack == 0)
		(*storage)->curr_stack = 'A';
	if ((*head) && (*head)->next)
	{
		curr = ((*storage)->head_a->index == (*head)->index &&
				(*storage)->tail_a->index == (*tail)->index) ? 1 : 2;
		*head = (*head)->next;
		(*head)->prev = NULL;
		(*tail)->next = tmp;
		tmp->prev = *tail;
		tmp->next = NULL;
		*tail = tmp;
		(*storage)->flag_kol_op += 1;
		if ((*storage)->push_swap == 1)
			(curr == 1) ? (ft_printf("ra\n")) :
			(ft_printf("rb\n"));
	}
	if ((*storage)->flag_v == 1)
		output_stacks(&(*storage));
	return (1);
}

int		rr_reverse(t_num **head, t_num **tail, t_what **storage)
{
	t_num	*tmp;
	int		curr;

	if ((*head) && (*head)->next)
	{
		curr = ((*storage)->head_a->index == (*head)->index &&
				(*storage)->tail_a->index == (*tail)->index) ? 1 : 2;
		tmp = (*tail);
		*tail = (*tail)->prev;
		(*tail)->next = NULL;
		(*head)->prev = tmp;
		tmp->prev = NULL;
		tmp->next = *head;
		*head = tmp;
		(*storage)->flag_kol_op += 1;
		if ((*storage)->push_swap == 1)
			(curr == 1) ? (ft_printf("rra\n")) :
			(ft_printf("rrb\n"));
	}
	if ((*storage)->flag_v == 1)
		output_stacks(&(*storage));
	return (1);
}
