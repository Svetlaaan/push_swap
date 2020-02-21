#include "push_swap.h"
#include <stdio.h>

void    set_block(t_what **storage)
{
    int     num_block;
    t_num   *tmp;

    num_block = (*storage)->stack_a / 3; // по сколько элементов в блоке?
    tmp = (*storage)->head_a;
    while (tmp)
    {
        if (tmp->index >= 1 && tmp->index < 1 + num_block) /// ?
            tmp->block = 1;
        else if (tmp->index >= 1 + num_block && tmp->index < 1 + num_block * 2)
            tmp->block = 2;
        else
            tmp->block = 3;
            //(*storage)->third_step_width += 1;
        tmp = tmp->next;
    }
}

int		sort_by_blocks(t_what **storage)
{
    int 	count;

    count = (*storage)->stack_a;
    while (count--)
    {
        if ((*storage)->head_a->block == 3)
            r_rotate(&(*storage)->head_a, &(*storage)->tail_a);
        else if ((*storage)->head_a->block == 2)
        {
            push('b', storage);
            (*storage)->stack_a -= 1;
        }
        else if ((*storage)->head_a->block == 1)
        {
            push('b', storage);
            r_rotate(&(*storage)->head_b, &(*storage)->tail_b);
            (*storage)->stack_a -= 1;
        }
    }
    return (0);
}

int main(int argc, char **argv)
{
    t_num *num = NULL;
    t_what *storage = NULL;
    int i = 1;
	t_num *head = num;

    if (argc < 2)
    {
        ft_putstr("need more arguments!");
        return (0);
    }
    else
        {
        if (!(num = new_num()))
            return (-1);
        if (!(storage = new_what()))
            return (-1);
        while (argc > 1)
        {
            if (save_argv(argv[i], &num, &storage) == -1)
            {
                free_num(&num);
                return (-1);
            }
            argc--;
            i++;
        }
        index_array(&storage->head_a);
        set_block(&storage);
        sort_by_blocks(&storage);
        print_stacks(storage->head_a, storage->head_b);
    }
    if (num)
    	free_num(&num);
    if (storage)
    	free_storage(&storage);
    return (0);
}
