#include "push_swap.h"
#include <stdio.h>


void    set_block(t_what **storage)
{
    int     num_block;
    t_num   *tmp;

    num_block = (*storage)->stack_a / 2; // по сколько элементов в блоке?
    tmp = (*storage)->head_a;
    while (tmp)
    {
        if (tmp->index >= 1 && tmp->index < 1 + num_block)
            tmp->block = 1;
        else
            tmp->block = 2;
        tmp = tmp->next;
    }
}

void		sort_by_blocks(t_what **storage)
{
    int 	count;

    count = (*storage)->stack_a;
    while (count--)
    {
        if ((*storage)->head_a->block == 2)
            r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
        else if ((*storage)->head_a->block == 1)
        {
            push('b', storage);
            if ((*storage)->stack_b > 1)
            	r_rotate(&(*storage)->head_b, &(*storage)->tail_b, &(*storage));
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
