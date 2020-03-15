/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_and_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboggs <fboggs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:16:14 by fboggs            #+#    #+#             */
/*   Updated: 2020/03/15 14:52:41 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

t_num	*new_num(void)
{
	t_num *new;

	if (!(new = (t_num *)malloc(sizeof(t_num))))
		return (NULL);
	new->num = -1;
	new->sign = 0;
	new->index = -1;
	new->next = NULL;
	new->prev = NULL;
	new->sort = 0;
	new->flag = 0;
	new->flag_st_b = 0;
	return (new);
}

t_what	*new_what(void)
{
	t_what *storage;

	if (!(storage = (t_what*)malloc(sizeof(t_what))))
		return (NULL);
	storage->head_a = NULL;
	storage->head_b = NULL;
	storage->tail_a = NULL;
	storage->tail_b = NULL;
	storage->curr_stack = 0;
	storage->stack_a = 0;
	storage->stack_b = 0;
	storage->flag_v = 0;
	storage->flag_kol_op = 0;
	storage->max = 0;
	storage->mid = 0;
	storage->next = 1;
	storage->flag = 0;
	storage->argc = 0;
	storage->push_swap = 0;
	return (storage);
}

int		new_num_storage(t_num **num, t_what **storage)
{
	if (!((*num) = new_num()))
		return (-1);
	if (!((*storage) = new_what()))
		return (-1);
	return (1);
}

void	save_if_minus(const char **av, int *flag, int *minus)
{
	if (**av == '-')
	{
		*flag += 1;
		*minus *= -1;
		*av += 1;
	}
}
