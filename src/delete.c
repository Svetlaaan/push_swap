/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboggs <fboggs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 14:48:57 by fboggs            #+#    #+#             */
/*   Updated: 2020/03/15 14:49:40 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_num(t_num *tmp, t_num *tmp_prev)
{
	while (tmp)
	{
		(tmp_prev) = (tmp)->prev;
		(tmp)->sign = 0;
		(tmp)->num = 0;
		(tmp)->index = 0;
		(tmp)->flag = 0;
		(tmp)->sort = 0;
		(tmp)->flag_st_b = 0;
		if ((tmp)->next)
			(tmp)->next = NULL;
		(tmp)->prev = NULL;
		free(tmp);
		(tmp) = (tmp_prev);
	}
	free(tmp);
	free(tmp_prev);
}

void	free_stack_a(t_what **storage)
{
	t_num *tmp;
	t_num *tmp_prev;

	tmp = NULL;
	tmp_prev = NULL;
	if ((*storage)->head_a)
	{
		if ((*storage)->tail_a && (*storage)->tail_a->next &&
			(*storage)->tail_a->next->num == -1)
		{
			(*storage)->tail_a->next->num = 0;
			(*storage)->tail_a->next->index = 0;
			(*storage)->tail_a->next->prev = NULL;
			free((*storage)->tail_a->next);
			(*storage)->tail_a->next = NULL;
		}
		if ((*storage)->tail_a)
			tmp = (*storage)->tail_a;
		else
			tmp = (*storage)->head_a;
		free_num(tmp, tmp_prev);
	}
}

void	free_stack_b(t_what **storage)
{
	t_num *tmp;
	t_num *tmp_prev;

	tmp = NULL;
	tmp_prev = NULL;
	if ((*storage)->head_b)
	{
		if ((*storage)->tail_b)
			tmp = (*storage)->tail_b;
		else
			tmp = (*storage)->head_b;
		free_num(tmp, tmp_prev);
	}
}

void	final_free(t_what **storage, t_num **num)
{
	if ((*storage)->head_a)
		free_stack_a(&(*storage));
	if ((*storage)->head_b)
		free_stack_b(&(*storage));
	else if ((*storage)->head_a == NULL && (*storage)->head_b == NULL)
		free(*num);
	(*storage)->flag_v = 0;
	(*storage)->flag_kol_op = 0;
	(*storage)->stack_a = 0;
	(*storage)->stack_b = 0;
	(*storage)->curr_stack = 0;
	(*storage)->next = 0;
	(*storage)->max = 0;
	(*storage)->mid = 0;
	(*storage)->flag = 0;
	(*storage)->argc = 0;
	free(*storage);
}
