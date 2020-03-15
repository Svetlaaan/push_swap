/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboggs <fboggs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 15:03:18 by fboggs            #+#    #+#             */
/*   Updated: 2020/03/15 15:05:20 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int		find_min(t_num **stack, int i)
{
	t_num	*tmp;
	t_num	*min;
	int		minimum;

	if (NULL == (*stack))
		return (0);
	tmp = (*stack);
	min = (*stack);
	minimum = (*stack)->index;
	while (tmp)
	{
		if (tmp->index < minimum && tmp->sort == 0 && tmp->flag_st_b == i)
		{
			minimum = tmp->index;
			min = tmp;
		}
		tmp = tmp->next;
	}
	return (min->index);
}

int		find_max(t_num **stack, int i)
{
	t_num	*tmp;
	t_num	*max;
	int		maxi;

	if ((*stack) == NULL)
		return (0);
	tmp = (*stack);
	max = (*stack);
	maxi = (*stack)->index;
	while (tmp)
	{
		if (tmp->index > maxi && tmp->sort == 0 && tmp->flag_st_b == i)
		{
			maxi = tmp->index;
			max = tmp;
		}
		tmp = tmp->next;
	}
	return (max->index);
}

void	print_stacks(t_num *head_a, t_num *head_b)
{
	t_num *tmp_a;
	t_num *tmp_b;

	tmp_a = head_a;
	tmp_b = head_b;
	while (tmp_a || tmp_b)
	{
		if (tmp_b == NULL && tmp_a)
		{
			ft_printf("%13i | %7c\n", tmp_a->num, ' ');
			tmp_a = tmp_a->next;
		}
		else if (tmp_a == NULL && tmp_b)
		{
			ft_printf("%13c | %1i\n", ' ', tmp_b->num);
			tmp_b = tmp_b->next;
		}
		else if (tmp_a && tmp_b)
		{
			ft_printf("%13i | %1i\n", tmp_a->num, tmp_b->num);
			tmp_a = tmp_a->next;
			tmp_b = tmp_b->next;
		}
	}
	ft_printf("%13s | %7s\n", "stack A", "stack B");
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
