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
	block = (*stack)->block;
	while (tmp && tmp->block == block)
	{
		count++;
		mid = mid + tmp->index;
		tmp = tmp->next;
	}
	return (mid / count);
}

void    set_block(t_what **storage)
{
    int     num_block;
    t_num   *tmp;
    int mid = 0;

    if ((*storage)->curr_stack == 0)
		(*storage)->curr_stack = 'A';
    else if ((*storage)->curr_stack != 0)
		(*storage)->curr_stack = 'B';
	if ((*storage)->curr_stack == 'A')
		mid = find_mid((&(*storage)->head_a));
	else if ((*storage)->curr_stack == 'B')
		mid = find_mid((&(*storage)->head_b));
	num_block = (((*storage)->curr_stack == 'A') ? (*storage)->stack_a / 2 : (*storage)->stack_b / 2); // по сколько элементов в блоке?
    tmp = ((*storage)->curr_stack == 'A') ? ((*storage)->head_a) : ((*storage)->head_b);
    while (tmp)
    {
        if (tmp->index <= mid) // 1 && tmp->index < 1 + num_block)
		{
        	if (tmp->block == 0)
				tmp->block = 1;
        	else
        		tmp->podblock = 1;
		}
        else
		{
			if (tmp->block == 0)
				tmp->block = 2;
			else
				tmp->podblock = 2;
		}
        tmp = tmp->next;
    }
}

/* не ставятся подблоки когда работаю со вторым блоком*/

void 		sort_by_subblocks(t_what **storage, t_num **head_tmp, t_num **tail_tmp)
{
	/*t_num **head_tmp = NULL;
	t_num **tail_tmp = NULL;
	t_num **head_where = NULL;
	t_num **tail_where = NULL;
	int count;

	count = ((*storage)->curr_stack == 'A') ? (*storage)->stack_a : (*storage)->stack_b;
	if ((*storage)->stack_b == 0)
		(*storage)->curr_stack = 'A';
	if ((*storage)->curr_stack == 'A')
	{
		head_tmp = &(*storage)->head_a;
		tail_tmp = &(*storage)->tail_a;
		head_where = &(*storage)->head_b;
		tail_where = &(*storage)->tail_b;
	}
	else if ((*storage)->curr_stack == 'B')
	{
		head_tmp = &(*storage)->head_b;
		tail_tmp = &(*storage)->tail_b;
		head_where = &(*storage)->head_a;
		tail_where = &(*storage)->tail_a;
	}
	while (count--)
	{*/
		if ((*head_tmp)->podblock == 2)
			((*storage)->curr_stack == 'A') ? push('b', storage) : push('a', storage);
		else if ((*head_tmp)->podblock == 1)
			r_rotate(&(*head_tmp), &(*tail_tmp), &(*storage));
}

void		sort_by_blocks(t_what **storage)
{
    int 	count;
	t_num **head_tmp = NULL;
	t_num **tail_tmp = NULL;
	t_num **head_where = NULL;
	t_num **tail_where = NULL;

	/*if ((*storage)->sort_block_1 == 1)
		(*storage)->curr_block = ((*storage)->curr_block < 2) ? (*storage)->curr_block + 1 : (*storage)->curr_block - 1;*/
	if ((*storage)->stack_b == 0)
		(*storage)->curr_stack = 'A';
	if ((*storage)->curr_stack == 'A')
	{
		head_tmp = &(*storage)->head_a;
		tail_tmp = &(*storage)->tail_a;
		head_where = &(*storage)->head_b;
		tail_where = &(*storage)->tail_b;
	}
	else if ((*storage)->curr_stack == 'B')
	{
		head_tmp = &(*storage)->head_b;
		tail_tmp = &(*storage)->tail_b;
		head_where = &(*storage)->head_a;
		tail_where = &(*storage)->tail_a;
	}
	count = ((*storage)->curr_stack == 'A') ? (*storage)->stack_a : (*storage)->stack_b;
    while (count--)
    {
		if ((*head_tmp) && (*head_tmp)->podblock > 0)
			sort_by_subblocks(&(*storage), &(*head_tmp), &(*tail_tmp));
        if ((*head_tmp)->block != (*storage)->curr_block && (*head_tmp)->podblock == 0)// || (*head_tmp)->podblock == 2)
            r_rotate(&(*head_tmp), &(*tail_tmp), &(*storage));
        else if ((*head_tmp)->block == (*storage)->curr_block && (*head_tmp)->podblock == 0) //|| ((*head_tmp)->podblock == 1))
        {
			((*storage)->curr_stack == 'A') ? push('b', storage) : push('a', storage);
			if ((*storage)->curr_stack == 'B')
				r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
			/*if ((*head_tmp)->podblock == 0)
			{
				if ((*storage)->curr_stack == 'A')
				{
					if ((*storage)->stack_b > 1)
						r_rotate(&(*storage)->head_b, &(*storage)->tail_b, &(*storage));
				}
				else if ((*storage)->curr_stack == 'B')
				{
					if ((*storage)->stack_a > 1)
						r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
				}
			}*/
        }
    }
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
        set_block(&storage); /// делим на 2 части
        if (is_sorted((&(*storage))->head_a) == -1)
		{
			if (sorting(&storage) == -1)
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
