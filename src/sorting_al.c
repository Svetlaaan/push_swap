/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_al.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboggs <fboggs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 19:35:03 by fboggs            #+#    #+#             */
/*   Updated: 2020/03/11 19:35:03 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int		is_sorted_final(t_what *storage)
{
	t_num	*tmp;
	int 	prev_index;

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

int 	is_sorted(t_num *head)
{
	t_num	*tmp;
	int 	prev_index;

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

int how_much_nonsort(t_what **storage, int i)
{
	t_num 	*tmp;
	int 	len;

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

void    what_curr_and_max_min(t_what **strg, int *i)
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
        (*strg)->next = find_min(&(*strg)->head_b, *i);////
        (*strg)->max = find_max(&(*strg)->head_b, *i);
        if ((*strg)->flag > 0)
			(*strg)->mid = ((*strg)->max - (*strg)->next) / 2 + (*strg)->next;
        else
			(*strg)->mid = ((*strg)->max / 2) + (*strg)->next;
        (*strg)->flag += 1;
    }
}

void	rotate_if_next(t_what **storage, t_num **tmp)
{
	if ((*tmp)->index == (*storage)->next)
		rotate_while_heada_next(&(*storage));
	else
		push('b', &(*storage));
}

void 	rotate_while_heada_next(t_what **storage)
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

void	if_small_block_in_a(t_what **storage, int count, t_num *tmp)
{
	while (count-- && tmp)
	{
		rotate_if_next(&(*storage), &(tmp));
		tmp = ((*storage)->curr_stack == 'A') ? ((*storage)->head_a) :
				((*storage)->head_b);
	}
}

void    split_stack(t_what **storage)
{
	t_num   *tmp;
	int     i;
	int     count;

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

int	push_from_b_if_sort(t_what **storage)
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

int 	sort_al_small(t_what **storage)
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

int 	sorting_al(t_what **storage)
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
