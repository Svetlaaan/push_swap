#include "push_swap.h"
#include <stdio.h>

int		find_mid(t_num **stack)
{
	int		mid;
	int		count;
	t_num	*tmp;
	int		block;

	mid = 0;
	count = 0;
	if (!(*stack))
		return (0);
	tmp = (*stack);
	//block = (*stack)->block;
	while (tmp) //&& tmp->block == block)
	{
		count++;
		mid = mid + tmp->index;
		tmp = tmp->next;
	}
	return (mid / count);
}

int		find_min(t_num **stack, t_what **storage)
{
	t_num	*tmp;
	t_num	*min;
	int		block;
	int		minimum;

	if (NULL == (*stack))
		return (0);
	tmp = (*stack);
	min = (*stack);
	//block = (*stack)->block;
	minimum = (*stack)->index;
	if ((*storage)->flag == 0)
	{
		while (tmp)// && tmp->block == block)
		{
			if (tmp->index < minimum)
			{
				minimum = tmp->index;
				min = tmp;
			}
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp)// && tmp->flag_st_b <= (*storage)->flag)
		{
			if (tmp->index < minimum && tmp->sort == 0)
			{
				minimum = tmp->index;
				min = tmp;
			}
			tmp = tmp->next;
		}
	}
	return (min->index);
}

int		find_max(t_num **stack, t_what **storage)
{
	t_num	*tmp;
	t_num	*max;
	//int		block;
	int		maximum;

	if (NULL == (*stack))
		return (0);
	tmp = (*stack);
	max = (*stack);
	maximum = (*stack)->index;
	if ((*storage)->flag == 0)
	{
		while (tmp)// && tmp->flag_st_b < (*storage)->flag)
		{
			if (tmp->index > maximum)
			{
				maximum = tmp->index;
				max = tmp;
			}
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp)// && tmp->flag_st_b <= (*storage)->flag)
		{
			if (tmp->index > maximum && tmp->sort == 0)
			{
				maximum = tmp->index;
				max = tmp;
			}
			tmp = tmp->next;
		}
	}

	return (max->index);
}

int main(int argc, char **argv)
{
    t_num *num;
    t_what *storage;
    int i;

	i = 1;
    if (argc < 2)
    {
        ft_putstr("need more arguments!");
        return (0);
    }
    else
        {
        if (!(num = new_num()))
		{
			final_free(&storage, &num);
			return (-1);
		}
        if (!(storage = new_what()))
		{
			final_free(&storage, &num);
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
        if (index_array(&storage->head_a) == -1)
        {
        	final_free(&storage, &num);
        	return (-1);
        }
        //set_block(&storage); /// делим на 2 части
        if (is_sorted((&(*storage))->head_a) == -1)
		{
			if (sorting_al(&storage) == -1)
			{
				final_free(&storage, &num);
				return (-1);
			}
		}
        if (is_sorted_final(storage) == 1)
        {
        	printf("\n<3 OK <3\n");
        	print_stacks(storage->head_a, storage->head_b);
        }
        else
        	{
        	printf("\n!!! NOOOOO !!!\n");
        	print_stacks(storage->head_a, storage->head_b);
        	}
    }
	printf("\nfinal operations: %d\n", storage->flag_kol_op);
	final_free(&storage, &num);
    return (0);
}
