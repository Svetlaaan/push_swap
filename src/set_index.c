/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_index.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboggs <fboggs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 15:49:48 by fboggs            #+#    #+#             */
/*   Updated: 2020/03/16 20:22:42 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int		check_dup(long long *min, long long *tmp_min, t_num **num_min, int *i)
{
	if ((*min) == (*tmp_min))
	{
		write(2, "Error\n", 6);
		return (-1);
	}
	(*num_min)->index = *i;
	*i += 1;
	(*tmp_min) = (*num_min)->num;
	return (1);
}

int		indexing(t_num **tmp, t_num **head, int *index, long long *tmp_min)
{
	long long	min;
	t_num		*num_min;

	num_min = NULL;
	min = 0;
	(*tmp) = *head;
	((*tmp)->index == -1) ? (min = (*tmp)->num) : 0;
	if ((*tmp)->index != -1)
	{
		while ((*tmp)->index != -1)
			(*tmp) = (*tmp)->next;
		min = (*tmp)->num;
	}
	while ((*tmp))
	{
		if ((*tmp)->index == -1 && (*tmp)->num <= min)
		{
			min = (*tmp)->num;
			num_min = (*tmp);
		}
		(*tmp) = (*tmp)->next;
	}
	if (check_dup(&min, tmp_min, &(num_min), index) == -1)
		return (-1);
	return (1);
}

int		index_array(t_num **head)
{
	t_num		*tmp;
	int			num_amount;
	int			index;
	long long	tmp_min;

	tmp_min = 2147483649;
	tmp = *head;
	num_amount = 0;
	index = 1;
	while (tmp)
	{
		num_amount++;
		tmp = tmp->next;
	}
	while (index != num_amount + 1)
	{
		if (indexing(&(tmp), &(*head), &index, &tmp_min) == -1)
			return (-1);
	}
	return (1);
}
