#include "push_swap.h"
#include <stdio.h>

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboggs <fboggs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 18:15:34 by fboggs            #+#    #+#             */
/*   Updated: 2020/03/10 18:15:34 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int 	new_num_storage(t_num **num, t_what **storage)
{
	if (!((*num) = new_num()))
		return (-1);
	if (!((*storage) = new_what()))
		return (-1);
	return (1);
}

int		sort(t_what **storage)
{
	if (is_sorted(((*storage))->head_a) == -1)
	{
		if (sorting_al(&(*storage)) == -1)
			return (-1);
	}
	if (is_sorted_final((*storage)) == 1)
		printf("\n<3 OK <3\n");
	else
		printf("\n!!! NOOOOO !!!\n");
	print_stacks((*storage)->head_a, (*storage)->head_b);
	return (1);
}

int main(int argc, char **argv)
{
    t_num	*num;
    t_what	*storage;
    int		i;

	i = 1;
    if (argc < 2)
    {
        ft_putstr("need more arguments!\n");
        return (0);
    }
    else
        {
			if (new_num_storage(&num, &storage) == -1)
			{
				final_free(&(storage), &(num));
				return (-1);
			}
			while (argc > 1)
			{
				if (save_argv(argv[i], &num, &storage) == -1)
				{
					if (storage->head_a)
						final_free(&storage, &num);
					return (-1);
				}
				argc--;
				i++;
			}
			if (index_array(&storage->head_a) == -1 || sort(&storage) == -1)
			{
				final_free(&storage, &num);
				return (-1);
			}
    	}
	printf("\nfinal operations: %d\n", storage->flag_kol_op);
	final_free(&storage, &num);
    return (0);
}

