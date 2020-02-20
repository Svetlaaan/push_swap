#include "push_swap.h"
#include <stdio.h>

void 		free_num(t_num **head)
{

    while (*head)
    {
        (*head)->num = 0;
        (*head)->index = 0;
        (*head)->block = 0;
        (*head)->next = NULL;
        (*head)->prev = NULL;
        (*head) = (*head)->prev;
        *head = NULL;
    }
    free(*head);

}

void	free_storage(t_what **storage)
{
		(*storage)->head_a = NULL;
		(*storage)->head_b = NULL;
		(*storage)->tail_a = NULL;
		(*storage)->tail_b = NULL;
		(*storage)->stack_a = 0;
		(*storage)->stack_b = 0;
		(*storage)->max_index_stack_a = 0;
		(*storage)->min_index_stack_a = 0;
//		(*storage)->third_step_width = 0;
	free(*storage);
	*storage = NULL;
}

t_num		*new_num(void)
{
    t_num *new;

    if (!(new = (t_num *)malloc(sizeof(t_num))))
        return (NULL);
    new->num = -1;
    new->index = -1;
    new->block = 0;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

t_what *new_what()
{
    t_what *storage;

    if(!(storage = (t_what*)malloc(sizeof(t_what))))
        return(NULL);
    storage->head_a = NULL;
    storage->head_b = NULL;
    storage->tail_a = NULL;
    storage->tail_b = NULL;
    storage->stack_a = 0;
    storage->stack_b = 0;
    storage->max_index_stack_a = 0;
    storage->min_index_stack_a = 0;
   // storage->third_step_width = 0;
    return (storage);
}

int     check_char(char c)
{
    if ((c >= '0' && c <= '9') || c == '-')
        return (1);
    return (0);
}

int save_argv(const char *argv, t_num **num, t_what **storage)
{
    t_num *tmp;
    int flag = 0;

    if (argv == NULL || *num == NULL)
        return (-1);
    while (*argv != '\0')
    {
        while (*argv == ' ' || *argv == '\t')
            argv += 1;
        if (check_char(*argv)) //нужна ли проверка на пробелы и тд?
        {
            if ((*storage)->head_a == NULL)
                (*storage)->head_a = *num;
            if ((*num)->num == -1)
            {
                if(((*num)->num = ft_atoi(argv)) == -1) /// выделить память?
                {
                    printf("incorrect number: MIN_INT > || MAX_INT < "); //
                    return (-1);
                }
                if ((*num)->num < 0)
                	flag = 1;
            }
            else
                {
                    if (!((*num)->next = new_num()))
                        return (-1);
                    tmp = *num;
                    *num = (*num)->next;
                    (*num)->prev = tmp;
                    if(((*num)->num = ft_atoi(argv)) == -1) /// выделить память?
                    {
                        printf("incorrect number: MIN_INT > || MAX_INT < "); //
                        return (-1);
                    }
					if ((*num)->num < 0)
						flag = 1;
                }
            printf("save num = %d\n", (*num)->num);
            argv += (ft_len_of_number((*num)->num) + flag); // добавила условие в функцию для чисел > 0
            (*storage)->stack_a += 1;
            while (ft_iswhitespace(*argv))
                argv += 1;
            if (*argv == '\0')
            {
                (*storage)->tail_a = *num;
                break ;
            }
        }
        else
            {
                write(1, "Incorrect data\n", 15);
                    return (-1);
            }
    }
    return(0); ///
}

void     index_array(t_num **head)
{
    int     min;
    t_num   *num_min;
    t_num   *tmp;
    int 	num_amount;
    int		index;

    min = 0;
    num_min = NULL;
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
        tmp = *head;
        if (tmp->index == -1)
            min = tmp->num;
        else
            {
            while (tmp->index != -1)
                tmp = tmp->next;
            min = tmp->num;
        }
        while (tmp)
        {
            if (tmp->index == -1 && tmp->num <= min)
            {
                min = tmp->num;
                num_min = tmp;
            }
            tmp = tmp->next;
        }
        num_min->index = index;
        printf("save num = %d  index = %d\n", num_min->num, num_min->index);
        index++;
    }
}

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
